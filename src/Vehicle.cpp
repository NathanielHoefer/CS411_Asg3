//==============================================================================
// Assignment 3 - Vehicle Class
//==============================================================================
/*
    File: Vehicle.cpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

******************************************************************************/

#include "Vehicle.hpp"

using tripLegNS::DLMTR;
using std::string;

Vehicle::Vehicle()
{
	mMake = 		"Default";
	mModel = 		"Default";
	mEngine = 		0.0;
	mCylinderCnt = 	0;
	mTankSize = 	0;
	mCityMPG = 		0;
	mHighwayMPG = 	0;
	mCurrentFuel = 	0;
}

Vehicle::Vehicle(string make, string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG)
{
	mMake = 		make;
	mModel = 		model;
	mEngine = 		engine;
	mCylinderCnt = 	cylinders;
	mTankSize = 	tankSize;
	mCityMPG = 		cityMPG;
	mHighwayMPG = 	highwayMPG;
	mCurrentFuel = 	tankSize;
}

string 	Vehicle::getMake() 			{ return mMake; }
string 	Vehicle::getModel()			{ return mModel; }
double 	Vehicle::getEngine() 		{ return mEngine; }
int 	Vehicle::getCylinderCount()	{ return mCylinderCnt; }
double 	Vehicle::getTankSize() 		{ return mTankSize; }
int 	Vehicle::getCityMPG() 		{ return mCityMPG; }
int 	Vehicle::getHighwayMPG() 	{ return mHighwayMPG; }
double 	Vehicle::getCurrentFuel() 	{ return mCurrentFuel; }

double Vehicle::calcFuelConsumed(double miles, TripLeg::RoadType roadType)
{
	double mpg;
	if (roadType == TripLeg::CITY) {
		mpg = mCityMPG;
	} else if (roadType == TripLeg::HIGHWAY) {
		mpg = mHighwayMPG;
	}
	return miles / mpg;
}

void Vehicle::consumeFuel(double gallons)
{
	// Only reduce fuel if the tank wont be empty
	if (gallons <= mCurrentFuel) {
		mCurrentFuel -= gallons;
	}
}

int Vehicle::getMPG(TripLeg::RoadType type)
{
	int mpg = -1;
	if (type == TripLeg::CITY) {
		mpg = mCityMPG;
	} else if (type == TripLeg::HIGHWAY) {
		mpg = mHighwayMPG;
	}
	return mpg;
}

void Vehicle::fillTank()
{
	mCurrentFuel = mTankSize;
}

std::ostream & operator <<(std::ostream &lhs, const Vehicle &rhs)
{
	std::stringstream stream;

	// Delineates data with commas
	lhs << rhs.mMake + DLMTR;
	lhs << rhs.mModel + DLMTR;
	stream << rhs.mEngine;
	lhs << stream.str() + DLMTR;
	stream.str("");
	stream.clear();
	stream << rhs.mCylinderCnt;
	lhs << stream.str() + DLMTR;
	stream.str("");
	stream.clear();
	stream << rhs.mTankSize;
	lhs << stream.str() + DLMTR;
	stream.str("");
	stream.clear();
	stream << rhs.mCityMPG;
	lhs << stream.str() + DLMTR;
	stream.str("");
	stream.clear();
	stream << rhs.mHighwayMPG;
	lhs << stream.str() + DLMTR;
	stream.str("");
	stream.clear();
	stream << rhs.mCurrentFuel;
	lhs << stream.str() + DLMTR;
	return lhs;
}
