#pragma once
#include "stdafx.h"
#include <type_traits>

namespace nsRecursiveTemplate
{

	//client components
	class IComponent1
	{
	};

	class CAIComponent1 : public IComponent1
	{
	};

	class CSoundComponent1 : protected CAIComponent1, public IComponent1
	{
	};

	class CPhysicsComponent1 : protected CSoundComponent1, public IComponent1
	{
	};

	class CUIComponent1 : protected CPhysicsComponent1, public IComponent1
	{
	};

	class CObject1 : protected CUIComponent1
	{
	public:
		template<class T>
		T& GetComponent()
		{
			//IComponent1* c = this;
			return *this;
		}
	};







	//traits helpers
	//type list
	template <class T, class U>
	struct type_node
	{
		typedef T Head; //type of the class
		typedef U Next; //next node type_node
	};

	class type_empty {};

	//Recursive template search for the type inside the type list
	template <class T, typename TypeList>
	struct get_type
	{
		typedef typename
			std::conditional
			<
				std::is_same<T, typename TypeList::Head>::value
				, typename TypeList
				, typename get_type<T, typename TypeList::Next>::TType
			>::type TType;
	};

	//class to stop the search when it reaches the end of the type list
	template <class T>
	struct get_type<T, type_empty>
	{
		typedef typename T TType;
	};

	//Recurring template
	//It stores the component and inherits from the next node on the list.
	template<typename TypeList>
	class CTypeContainer : public CTypeContainer<typename TypeList::Next>
	{
	public:
		typename TypeList::Head& GetComponent() { return _component; }

	private:
		typename TypeList::Head _component;
	};

	//Last inherit class, technically this is the root base class.
	template<>
	class CTypeContainer<type_empty>
	{
	};


	class IComponent {};
	class CAIComponent : public IComponent {};
	class CSoundComponent : public IComponent {};
	class CPhysicsComponent : public IComponent {};
	class CUIComponent : public IComponent{};

	class CGameObject
	{
	public:
		template<class T>
		T* GetComponent() const
		{
			size_t componentId = GetComponentId<T>();
			IComponent* componentBase = _components[componentId];
			T* component = dynamic_cast<T*>(componentBase);
			return component
		}
	private:
		std::map<size_t, IComponent*>  _components;
	};


	class CGameObject2
	{
	public:
		template<class T>
		T* GetComponent() const
		{
			if (std::is_same<T, CAIComponent>::value)
			{
				return _aiCompoment;
			}

			if (std::is_same<T, CSoundComponent>::value)
			{
				return _soundCompoment;
			}

			if (std::is_same<T, CPhysicsComponent>::value)
			{
				return _pysicsCompoment;
			}

			if (std::is_same<T, CUIComponent>::value)
			{
				return _uiCompoment;
			}

			assert(false);
			return nullptr;
		}

	private:
		CAIComponent* _aiCompoment;
		CSoundComponent* _soundCompoment;
		CPhysicsComponent* _pysicsCompoment;
		CUIComponent* _uiCompoment;
	};




	class CObject2  : protected CUIComponent
					, protected CPhysicsComponent
					, protected CSoundComponent
					, protected CAIComponent
	{
	public:
		template<class T>
		T& GetComponent()
		{
			return *this;
		}
	};



	//client type list
	typedef type_node<
		CAIComponent, type_node
		<
			CSoundComponent, type_node
			<
				CPhysicsComponent, type_node
				<
					CUIComponent, type_empty
				>
			>
		>
	> TComponentList;

	/*
	
		//client type list
	typedef 
		type_node<CAIComponent, 
		type_node<CSoundComponent, 
		type_node<CPhysicsComponent,
		type_node<CUIComponent,
		type_empty>>>> 
	TComponentList;
	*/



	//client object to store the component list object
	class CObject
	{
	public:
		template<class T>
		T& GetComponent()
		{
			using TComponent = get_type<T, TComponentList>::TType;
			//std::string typeString = typeid(TComponent).name();

			CTypeContainer<TComponent>& componentListType = _componentList;
			//std::string componentListTypeString = typeid(componentListType).name();

			T& component = componentListType.GetComponent();
			//std::string componentTypeString = typeid(component).name();

			return component;
		}

		void UpdateAllComponents()
		{
			UpdateComponent<TComponentList>();
		}

		template<class TList>
		void UpdateComponent()
		{
			CTypeContainer<TList>* componentListType = &_componentList;
			//componentListType->GetComponent().Update();

			UpdateComponent<TList::Next>();
		}

		//end of the search
		//this method could be removed by using "if(!std::is_same<TList::Next, type_empty>::value)" on the method above
		//...but for every UpdateComponent it would do an "if" check
		template<>
		void UpdateComponent<type_empty>()
		{
		}

	private:
		CTypeContainer<TComponentList> _componentList;
	};
}

BEGIN_TEST(RecursiveTemplate)
	using namespace nsRecursiveTemplate;

	CObject1 obj1;
	//IComponent1& baseComponent = obj1.GetComponent<IComponent1>();//ambiguous return
	//IComponent1& baseComponent = obj1; //ambiguous

	CUIComponent1& uiComponent1 = obj1.GetComponent<CUIComponent1>();
	CPhysicsComponent1& physicsComponent1 = obj1.GetComponent<CPhysicsComponent1>();
	CSoundComponent1& soundComponent1 = obj1.GetComponent<CSoundComponent1>();
	CAIComponent1& aiComponent1 = obj1.GetComponent<CAIComponent1>();
	//IComponent1& baseComponent = uiComponent1; //ambiguous

	CObject2 obj2;
	CUIComponent& uiComponent2 = obj2.GetComponent<CUIComponent>();
	CPhysicsComponent& physicsComponent2 = obj2.GetComponent<CPhysicsComponent>();
	CSoundComponent& soundComponent2 = obj2.GetComponent<CSoundComponent>();
	CAIComponent& aiComponent2 = obj2.GetComponent<CAIComponent>();

	CObject obj;
	CUIComponent& uiComponent = obj.GetComponent<CUIComponent>();
	CPhysicsComponent& physicsComponent = obj.GetComponent<CPhysicsComponent>();
	CSoundComponent& soundComponent = obj.GetComponent<CSoundComponent>();
	CAIComponent& aiComponent = obj.GetComponent<CAIComponent>();
	obj.UpdateAllComponents();
END_TEST()