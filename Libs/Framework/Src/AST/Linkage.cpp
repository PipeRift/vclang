// Copyright 2015-2020 Piperift - All rights reserved
#include "AST/Components/CChild.h"
#include "AST/Components/CParent.h"
#include "AST/Components/CClassDecl.h"
#include "AST/Components/CFunctionDecl.h"
#include "AST/Components/CIdentifier.h"
#include "AST/Components/CStructDecl.h"
#include "AST/Components/CVariableDecl.h"
#include "AST/Linkage.h"
#include "Misc/Checks.h"


namespace Rift::AST
{
	void RemoveChildFromCParent(Tree& ast, Id parent, Id child)
	{
		if (CParent* cParent = GetCParent(ast, parent))
		{
			cParent->children.Remove(child);
			if (cParent->children.IsEmpty())
			{
				ast.Remove<CParent>(parent);
			}
		}
	}


	Id CreateClass(Tree& ast, Name name)
	{
		Id id = ast.Create();
		ast.Add<CIdentifier>(id, name);
		ast.Add<CStructDecl, CParent>(id);
		return id;
	}

	Id CreateStruct(Tree& ast, Name name)
	{
		Id id = ast.Create();
		ast.Add<CIdentifier>(id, name);
		ast.Add<CStructDecl, CParent>(id);
		return id;
	}

	Id CreateVariable(Tree& ast, Name name)
	{
		Id id = ast.Create();
		ast.Add<CIdentifier>(id, name);
		ast.Add<CVariableDecl, CParent>(id);
		return id;
	}

	Id CreateFunction(Tree& ast, Name name)
	{
		Id id = ast.Create();
		ast.Add<CIdentifier>(id, name);
		ast.Add<CFunctionDecl, CParent>(id);
		return id;
	}


	void Link(Tree& ast, Id node, TArrayView<Id> children)
	{
		children.Each([&ast, node](Id child) {
			if (CChild* cChild = GetCChild(ast, child))
			{
				if (EnsureMsg(IsNone(cChild->parent),
				        "A node trying to be linked already has a parent. Consider using "
				        "TransferLinks()"))
				{
					cChild->parent = node;
				}
			}
			else
			{
				ast.Add<CChild>(child).parent = node;
			}
		});
		ast.GetOrAdd<CParent>(node).children.Append(children);
	}

	void TransferLinks(Tree& ast, TArrayView<Id> children, Id destination)
	{
		Unlink(ast, children, true);
		Link(ast, destination, children);
	}

	void TransferAllLinks(Tree& ast, Id origin, Id destination) {}

	void TransferLinks(Tree& ast, Id node, Id child) {}

	void Unlink(Tree& ast, TArrayView<Id> children, bool keepComponents)
	{
		TArray<Id> parents;
		parents.Reserve(children.Size());

		children.Each([&ast, &parents](Id child) {
			CChild* cChild = GetCChild(ast, child);
			if (cChild)
			{
				parents.Add(cChild->parent);
				cChild->parent = AST::NoId;
			}
		});

		if (!keepComponents)
		{
			children.Each([&ast](Id child) {
				ast.Remove<CChild>(child);
			});
		}

		// Sort to iterate avoiding duplicated parents
		parents.Sort();
		Id lastParent = AST::NoId;

		if (keepComponents)
		{
			for (Id parent : parents)
			{
				if (parent == lastParent)
				{
					continue;
				}
				lastParent = parent;

				if (CParent* cParent = GetCParent(ast, parent))
				{
					cParent->children.RemoveMany(children);
				}
			}
		}
		else
		{
			for (Id parent : parents)
			{
				if (parent == lastParent)
				{
					continue;
				}
				lastParent = parent;

				if (CParent* cParent = GetCParent(ast, parent))
				{
					cParent->children.RemoveMany(children);
					if (cParent->children.IsEmpty())
					{
						ast.Remove<CParent>(parent);
					}
				}
			}
		}
	}

	void UnlinkAllChildren(Tree& ast, TArrayView<Id> parents, bool keepComponents)
	{
		if (keepComponents)
		{
			parents.Each([&ast](Id parent) {
				if (CParent* cParent = GetCParent(ast, parent))
				{
					for (Id child : cParent->children)
					{
						CChild* cChild = GetCChild(ast, child);
						Ensure(cChild);
						cChild->parent = AST::NoId;
					}
					cParent->children.Empty();
				}
			});
		}
		else
		{
			parents.Each([&ast](Id parent) {
				if (CParent* cParent = GetCParent(ast, parent))
				{
					for (Id child : cParent->children)
					{
						ast.Remove<CChild>(child);
					}
					ast.Remove<CParent>(parent);
				}
			});
		}
	}

	TArray<Id>* GetLinked(Tree& ast, Id node)
	{
		CParent* const parent = GetCParent(ast, node);
		return parent ? &parent->children : nullptr;
	}

	void GetLinked(Tree& ast, TArrayView<const Id> nodes, TArray<Id>& outLinkedNodes)
	{
		nodes.Each([&ast, &outLinkedNodes](Id node) {
			if (CParent* const parent = GetCParent(ast, node))
			{
				outLinkedNodes.Append(parent->children);
			}
		});
	}

	void GetLinkedDeep(const Tree& ast, TArrayView<const Id> roots, TArray<Id>& outLinkedNodes)
	{
		TArray<AST::Id> pendingInspection;
		pendingInspection.Append(roots);
		TArray<AST::Id> currentLinked{};
		while (pendingInspection.Size() > 0)
		{
			for (AST::Id parent : pendingInspection)
			{
				if (const CParent* childrenComp = GetCParent(ast, parent))
				{
					currentLinked.Append(childrenComp->children);
				}
			}
			outLinkedNodes.Append(currentLinked);
			pendingInspection = Move(currentLinked);
		}
	}

	void Remove(Tree& ast, TArrayView<Id> nodes)
	{
		Unlink(ast, nodes, true);

		UnlinkAllChildren(ast, nodes);
		ast.Destroy(nodes.begin(), nodes.end());
	}

	void RemoveDeep(Tree& ast, TArrayView<Id> nodes)
	{
		Unlink(ast, nodes, true);

		TArray<Id> allNodes;
		allNodes.Append(nodes);
		GetLinkedDeep(ast, nodes, allNodes);
		ast.Destroy(allNodes.begin(), allNodes.end());
	}


	CChild* GetCChild(Tree& ast, Id node)
	{
		return reinterpret_cast<CChild*>(ast.GetChildPool()->get(node));
	}

	const CChild* GetCChild(const Tree& ast, Id node)
	{
		return reinterpret_cast<const CChild*>(ast.GetChildPool()->get(node));
	}

	CParent* GetCParent(Tree& ast, Id node)
	{
		return reinterpret_cast<CParent*>(ast.GetParentPool()->get(node));
	}

	const CParent* GetCParent(const Tree& ast, Id node)
	{
		return reinterpret_cast<const CParent*>(ast.GetParentPool()->get(node));
	}
}    // namespace Rift::AST
