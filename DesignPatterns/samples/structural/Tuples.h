#pragma once
#include "stdafx.h"
#include <vector>
#include <type_traits>
#include <tuple>
#include <functional>
#include <ctime>
#include <array>

namespace nsTuples
{
	//client components
	class IComponent
	{
	public:
		virtual void Update(){}
	};

	class CAIComponent : public IComponent
	{
	public:
		int _data = 1;
	};

	class CSoundComponent : public IComponent
	{
	public:
		int _data = 2;
	};

	class CPhysicsComponent : public IComponent
	{
	public:
		int _data = 3;
	};

	class CUIComponent : public IComponent
	{
	public:
		int _data = 4;
	};


	
	namespace nsTupleIteratorImplementation
	{
		template<int... Is>
		struct final_sequence 
		{ 
		};

		template<int N, int... Is>
		struct generate_seq : generate_seq<N - 1, N - 1, Is...>
		{ 
		};

		template<int... Is>
		struct generate_seq<0, Is...> : final_sequence<Is...>
		{ 
		};

		template<typename TTuple, typename TPredicate, int... Is>
		void for_each(TTuple&& tuple, TPredicate predicate, final_sequence<Is...> sequence)
		{
			std::initializer_list<int> initList = 
			{ 
				(predicate(std::get<Is>(tuple)), 0)... 
			};
			
			std::string typeString = typeid(sequence).name();
		}
	}

	template<typename... TTupleTypes, typename TPredicate>
	void for_each_in_tuple(std::tuple<TTupleTypes...> const& tupleObject, TPredicate predicate)
	{
		constexpr int SIZE_TUPLE = sizeof...(TTupleTypes);
		nsTupleIteratorImplementation::for_each(tupleObject, predicate, nsTupleIteratorImplementation::generate_seq<SIZE_TUPLE>());
	}


	namespace nsTupleIteratorImplementation
	{
		template<typename TTupleContainer, typename TPredicate, int SIZE, int CURRENT_INDEX = 0>
		struct ForEachTupleElement
		{
			static void Invoke(TTupleContainer& tupleContainer, TPredicate predicate)
			{
				predicate(std::get<CURRENT_INDEX>(tupleContainer));

				constexpr int NEXT_INDEX = CURRENT_INDEX + 1;
				ForEachTupleElement<TTupleContainer, TPredicate, SIZE, NEXT_INDEX>::Invoke(tupleContainer, predicate);
			}
		};

		template<typename TTupleContainer, typename TPredicate, int SIZE>
		struct ForEachTupleElement<TTupleContainer, TPredicate, SIZE, SIZE>
		{
			static void Invoke(TTupleContainer& tupleContainer, TPredicate predicate)
			{
			}
		};
	}

	template<typename TTupleContainer, typename TPredicate>
	void for_each_tuple(TTupleContainer& tupleContainer, TPredicate predicate)
	{
		static constexpr int TUPLE_SIZE = std::tuple_size<TTupleContainer>::value;
		nsTupleIteratorImplementation::ForEachTupleElement<TTupleContainer, TPredicate, TUPLE_SIZE>::Invoke(tupleContainer, predicate);
	}

	class CTupleObject
	{
	private:
		using TTupleList = std::tuple<CAIComponent
									, CSoundComponent
									, CPhysicsComponent
									, CUIComponent>;

		static constexpr int TUPLE_SIZE = std::tuple_size<TTupleList>::value;

	public:
		template<class T>
		T& GetComponent()
		{
			T& compomnent = std::get<T>(tupleComponents);
			return compomnent;
		}

		void UpdateAll()
		{
			Update<0>();
		}

		template<typename T>
		void operator () (T&& t)
		{
		}

	private:

		template<int CURRENT_INDEX>
		void Update()
		{
			for_each_in_tuple(tupleComponents, CTupleObject());

			static_assert(CURRENT_INDEX >= 0, "Index must be positive");
			static_assert(CURRENT_INDEX < TUPLE_SIZE, "Index must be inside boundaries");

			IComponent& component = std::get<CURRENT_INDEX>(tupleComponents);
			component.Update();

			constexpr int NEXT_INDEX = CURRENT_INDEX + 1;
			Update<NEXT_INDEX>();
		};
		
		template<>
		void Update<TUPLE_SIZE>()
		{
		};

	private:
		TTupleList tupleComponents;
	};


	class CTupleObjectPtr
	{
	private:
		using TTupleList = std::tuple<CAIComponent*
									, CSoundComponent*
									, CPhysicsComponent*
									, CUIComponent*>;

		static constexpr int TUPLE_SIZE = std::tuple_size<TTupleList>::value;

	public:
		CTupleObjectPtr()
		{
			CreateAll();
		}

		~CTupleObjectPtr()
		{
			DeleteAll();
		}

		void CreateAll()
		{
			Create<0>();
		}

		void DeleteAll()
		{
			Delete<0>();
		}



		void Tests()
		{
			using TPredicte = std::function<void(IComponent*)>;
			TPredicte predicate = std::bind(&CTupleObjectPtr::UpdatePredicate, this, std::placeholders::_1);
			for_each_tuple(tupleComponents, predicate);

			for_each_tuple(tupleComponents,
				[this](auto*& component)
				{
					this->CreateComponent(component);
				}
			);
			
			for_each_tuple(tupleComponents,
				[](IComponent* component)
				{
					component->Update();
				}
			);

			for_each_tuple(tupleComponents,
				[](auto*& component)
				{
					delete component;
					component = nullptr;
				}
			);
		}

		void UpdateAll()
		{
			using TPredicte = std::function<void(IComponent*)>;
			TPredicte predicate = std::bind(&CTupleObjectPtr::UpdatePredicate, this, std::placeholders::_1);
			for_each_tuple(tupleComponents, predicate);
		}

		template<class T>
		T* GetComponent()
		{
			T* compomnent = std::get<T*>(tupleComponents);
			return compomnent;
		}

	private:
		void UpdatePredicate(IComponent* component)
		{
			component->Update();
		}

		template<int CURRENT_INDEX>
		void Create()
		{
			static_assert(CURRENT_INDEX >= 0, "Index must be positive");
			static_assert(CURRENT_INDEX < TUPLE_SIZE, "Index must be inside boundaries");

			//need to use template deduction to retrieve type of the component
			CreateComponent(std::get<CURRENT_INDEX>(tupleComponents));

			constexpr int NEXT_INDEX = CURRENT_INDEX + 1;
			Create<NEXT_INDEX>();
		};

		template<>
		void Create<TUPLE_SIZE>()
		{
		};

		template<class T>
		void CreateComponent(T*& component)
		{
			component = new T();
		}

		template<int CURRENT_INDEX>
		void Delete()
		{
			static_assert(CURRENT_INDEX >= 0, "Index must be positive");
			static_assert(CURRENT_INDEX < TUPLE_SIZE, "Index must be inside boundaries");

			IComponent* component = std::get<CURRENT_INDEX>(tupleComponents);
			delete component;

			constexpr int NEXT_INDEX = CURRENT_INDEX + 1;
			Delete<NEXT_INDEX>();
		};

		template<>
		void Delete<TUPLE_SIZE>()
		{
		};


		template<int CURRENT_INDEX>
		void Update()
		{
			static_assert(CURRENT_INDEX >= 0, "Index must be positive");
			static_assert(CURRENT_INDEX < TUPLE_SIZE, "Index must be inside boundaries");

			IComponent* component = std::get<CURRENT_INDEX>(tupleComponents);
			component->Update();

			constexpr int NEXT_INDEX = CURRENT_INDEX + 1;
			Update<NEXT_INDEX>();
		};

		template<>
		void Update<TUPLE_SIZE>()
		{
		};

	private:
		TTupleList tupleComponents;
	};
}




BEGIN_TEST(Tuples)
	using namespace nsTuples;

	std::tuple<int, int> pairTuple;
	int value = std::get<0>(pairTuple);

	std::tuple<CAIComponent, CSoundComponent, CPhysicsComponent, CUIComponent> tupleComponents;
	CAIComponent& aiComponentTupleTest = std::get<CAIComponent>(tupleComponents);

	CTupleObject tupleObject;
	CAIComponent& aiComponentTuple = tupleObject.GetComponent<CAIComponent>();
	CSoundComponent& soundComponentTuple = tupleObject.GetComponent<CSoundComponent>();
	CPhysicsComponent& physicsComponentTuple = tupleObject.GetComponent<CPhysicsComponent>();
	CUIComponent& uiComponentTuple = tupleObject.GetComponent<CUIComponent>();
	tupleObject.UpdateAll();

	CTupleObjectPtr tupleObjectPtr;
	CAIComponent* aiComponentTuplePtr = tupleObjectPtr.GetComponent<CAIComponent>();
	CSoundComponent* soundComponentTuplePtr = tupleObjectPtr.GetComponent<CSoundComponent>();
	CPhysicsComponent* physicsComponentTuplePtr = tupleObjectPtr.GetComponent<CPhysicsComponent>();
	CUIComponent* uiComponentTuplePtr = tupleObjectPtr.GetComponent<CUIComponent>();
	tupleObjectPtr.UpdateAll();


	//performance tests

	const int cycles = 100000000;


	clock_t startTimestamp = clock();
	for (int i = 0; i < cycles; ++i)
	{
	}
	clock_t controlDuration = clock() - startTimestamp;
	
	startTimestamp = clock();
	for (int i = 0; i < cycles; ++i)
	{
		std::get<CUIComponent>(tupleComponents);
	}
	clock_t endTimeStamp = clock();
	clock_t durationTimeStatmp = endTimeStamp - startTimestamp;



	std::array<IComponent*, 4> arrayComponents;
	arrayComponents[0] = new CAIComponent();
	arrayComponents[1] = new CSoundComponent();
	arrayComponents[2] = new CPhysicsComponent();
	arrayComponents[3] = new CUIComponent();
	startTimestamp = clock();
	for (int i = 0; i < cycles; ++i)
	{
		arrayComponents.at(3);
	}
	endTimeStamp = clock();
	clock_t durationArrayTimeStatmp = endTimeStamp - startTimestamp;




	std::vector<IComponent*> vectorComponents;
	vectorComponents.push_back(new CAIComponent());
	vectorComponents.push_back(new CSoundComponent());
	vectorComponents.push_back(new CPhysicsComponent());
	vectorComponents.push_back(new CUIComponent());
	startTimestamp = clock();
	for (int i = 0; i < cycles; ++i)
	{
		vectorComponents.at(3);
	}
	endTimeStamp = clock();
	clock_t durationVectorTimeStatmp = endTimeStamp - startTimestamp;



	std::cout << "control duration :" << controlDuration << std::endl;
	std::cout << "duration tuple :" << durationTimeStatmp << std::endl;
	std::cout << "duration array:" << durationArrayTimeStatmp << std::endl;
	std::cout << "duration vector:" << durationVectorTimeStatmp << std::endl;
	
END_TEST()