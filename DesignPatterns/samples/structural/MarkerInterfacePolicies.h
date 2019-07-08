#pragma once
#include "stdafx.h"
#include <type_traits>
#include <vector>

namespace nsMarkerInterface
{
	class ISerializationPolicy
	{
	};

	class CSerializationRegular : public ISerializationPolicy
	{
	public:
		static void DoSerialize()
		{

		}
	};

	class CSerializationBinary : public ISerializationPolicy
	{
	public:
		static void DoSerialize()
		{

		}
	};

	class IMarker
	{
	public:
		virtual ~IMarker() {}
	};

	class IMarkerEmpty : public IMarker
	{
	public:
		~IMarkerEmpty() override {}
	};

	class IMarkerUpdatable : public IMarker
	{
	public:
		~IMarkerUpdatable() override {}
	};

	template<class TSerializationPolicy = CSerializationRegular, class TMarker = IMarkerEmpty >
	class CObject : public TMarker
	{
	public:
		CObject()
		{
			static_assert(std::is_base_of<ISerializationPolicy, TSerializationPolicy>::value
				, "Policy must be base class of ISerializationPolicy");

		}
		void Serialize()
		{
			TSerializationPolicy::DoSerialize();
		}

		void Update()
		{
		}
	};
}

BEGIN_TEST(MarkerInterface)
	using namespace nsMarkerInterface;

	CObject<CSerializationBinary, IMarkerEmpty> objectBinary;
	objectBinary.Serialize();

	CObject<CSerializationBinary, IMarkerUpdatable> objectBinary2;
	objectBinary.Serialize();

	std::vector<IMarker*> objects;
	objects.push_back(&objectBinary);
	objects.push_back(&objectBinary2);

	for (IMarker* markerObj : objects)
	{
		IMarkerUpdatable* markerUpdatable = dynamic_cast<IMarkerUpdatable*>(markerObj);
		if (markerUpdatable != nullptr)
		{
			CObject<CSerializationBinary, IMarkerUpdatable>* obj 
				= dynamic_cast<CObject<CSerializationBinary, IMarkerUpdatable>*>(markerUpdatable);
			
			obj->Update();
		}
	}


END_TEST()