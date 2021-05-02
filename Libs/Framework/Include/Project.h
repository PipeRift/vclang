// Copyright 2015-2020 Piperift - All rights reserved

#pragma once

#include "Assets/ProjectAsset.h"
#include "Assets/TypeAsset.h"
#include "Lang/AST.h"
#include "Log.h"
#include "Strings/String.h"

#include <Assets/AssetManager.h>
#include <Assets/AssetPtr.h>
#include <CoreObject.h>
#include <Files/Files.h>


namespace Rift
{
	enum class EProjectTargetType : u8
	{
		Executable,
		SharedLibrary,
		StaticLibrary
	};
	ENUM(EProjectTargetType)

	enum class EOther : u8
	{
		Executable,
		SharedLibrary,
		StaticLibrary
	};

	/**
	 * A project represents a group of classes, structs and other features of the lenguage that can
	 * be edited or compiled
	 */
	class Project : public Object
	{
		CLASS(Project, Object)

		static constexpr StringView projectFile{"Project.rf"};

		PROP(Name, name);
		Name name;

		Path projectPath;

		TAssetPtr<ProjectAsset> projectAsset;
		TArray<AssetInfo> allTypes;
		AST::AbstractSyntaxTree ast;


	public:
		Project() : Super()
		{
			auto testClass    = ast.CreateClass("AClass");            // Test
			auto testFunction = ast.CreateFunction("DoSomething");    // Test
			ast.AddChild(testClass, testFunction);
		}

		void Init(const Path& path);

		void ScanAssets();
		void LoadAllAssets();

		Path ToProjectPath(const Path& path) const;

		Path GetPath() const
		{
			return projectPath;
		}

		bool IsValid() const
		{
			return projectAsset.IsValid();
		}

		const TArray<AssetInfo>& GetAllTypeAssets() const
		{
			return allTypes;
		}

		AST::AbstractSyntaxTree& GetAST()
		{
			return ast;
		}
		const AST::AbstractSyntaxTree& GetAST() const
		{
			return ast;
		}

		void SetName(Name newName)
		{
			name = Move(newName);
		}
		Name GetName() const
		{
			return name;
		}
	};
}    // namespace Rift
