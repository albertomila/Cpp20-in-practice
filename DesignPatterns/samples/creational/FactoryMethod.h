#pragma once
#include "stdafx.h"

namespace nsFactoryMethod
{
	class IVehiclePart
	{
	};

	class CWheel : public IVehiclePart
	{
	};

	class CChasis : public IVehiclePart
	{
	};

	class CEngine : public IVehiclePart
	{
	};

	class CVehicle
	{
	public:
		void AddPart(IVehiclePart* part)
		{
			_parts.push_back(part);
		}

	private:
		std::vector<IVehiclePart*> _parts;
	};

	class IFactory
	{
	public:
		virtual CVehicle* CreateVehicle() const = 0;
	};

	class CMotorBikeFactory : public IFactory
	{
	public:
		CVehicle* CreateVehicle() const override
		{
			CVehicle* vehicle = new CVehicle();
			vehicle->AddPart(new CChasis());
			vehicle->AddPart(new CWheel());
			vehicle->AddPart(new CWheel());

			return vehicle;
		}
	};

	class CCarFactory : public IFactory
	{
	public:
		CVehicle* CreateVehicle() const override
		{
			CVehicle* vehicle = new CVehicle();
			vehicle->AddPart(new CChasis());
			vehicle->AddPart(new CWheel());
			vehicle->AddPart(new CWheel());
			vehicle->AddPart(new CWheel());
			vehicle->AddPart(new CWheel());

			return vehicle;
		}
	};
}

BEGIN_TEST(FactoryMethod)
	using namespace nsFactoryMethod;

	IFactory* motorbykeFactory = new CMotorBikeFactory();
	CVehicle* motorbyke = motorbykeFactory->CreateVehicle();

	IFactory* carFactory = new CCarFactory();
	CVehicle* car = carFactory->CreateVehicle();

END_TEST()
