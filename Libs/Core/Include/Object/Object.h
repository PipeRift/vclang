// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include "BaseObject.h"
#include "ObjectPtr.h"
#include "Reflection/Class.h"
#include "Serialization/Archive.h"


namespace VCLang
{
	class Context;

	class CORE_API Object : public BaseObject
	{
		ORPHAN_CLASS(Object, ReflectionTags::None)

	private:
		PROP(Name, name);
		Name name;

		Refl::Class* ownClass;
		Ptr<BaseObject> self;
		Ptr<BaseObject> owner;


	public:
		Object() : BaseObject(), ownClass{nullptr}, self{}, owner{} {};

		void PreConstruct(
			Ptr<BaseObject>&& inSelf, Refl::Class* inClass, const Ptr<BaseObject>& inOwner)
		{
			ownClass = inClass;
			self = inSelf;
			owner = inOwner;
		}
		virtual void Construct() {}

		virtual bool Serialize(Archive& ar)
		{
			SerializeReflection(ar);
			return true;
		}

		/** Manual destruction is dangerous and a bad practice
		void Destroy()
		{
			if (BaseGlobalPtr* global = Self().__GetGlobal())
			{
				global->Reset();
			}
		}*/

		Ptr<Object> GetOwner() const
		{
			return owner.Cast<Object>();
		}

		Ptr<Object> Self() const
		{
			return self.Cast<Object>();
		}

		template <typename T>
		Ptr<T> Self() const
		{
			return self.Cast<T>();
		}

		Refl::Class* GetType() const
		{
			return ownClass;
		}


		void SetName(Name newName)
		{
			name = MoveTemp(newName);
		}
		Name GetName() const
		{
			return name;
		}

		virtual Ptr<Context> GetContext() const;
	};


	template <typename Type>
	using IsObject = std::is_convertible<Type, Object>;

	template <class ObjectType>
	static CORE_API GlobalPtr<ObjectType> Create(
		Refl::Class* objectClass, const Ptr<Object> owner = {})
	{
		static_assert(IsObject<ObjectType>::value, "Type is not an Object!");

		if (objectClass)
		{
			return objectClass->CreateInstance(owner).Cast<ObjectType>();
		}
		return {};
	}

	template <class ObjectType>
	static CORE_API inline GlobalPtr<ObjectType> Create(const Ptr<Object> owner = {})
	{
		static_assert(IsObject<ObjectType>::value, "Type is not an Object!");

		return GlobalPtr<ObjectType>::Create(owner);
	}
}	 // namespace VCLang
