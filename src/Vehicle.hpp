//==============================================================================
// Assignment 3 - Vehicle Class
//==============================================================================
/*
	File: Vehicle.hpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/11/2017

******************************************************************************/

#ifndef SRC_VEHICLE_HPP_
#define SRC_VEHICLE_HPP_

#include <string>
#include <sstream>
#include "TripLeg.hpp"

namespace tripLegNS
{
	static const std::string DLMTR = "|";
}

class Vehicle
{
public:
	Vehicle();
	Vehicle(std::string make, std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);

	// Accessors
	std::string getMake();
	std::string getModel();
	double 		getEngine();
	int 		getCylinderCount();
	double 		getTankSize();
	int 		getCityMPG();
	int 		getHighwayMPG();
	double 		getCurrentFuel();

	//	Calculates the amount of fuel consumed after a number of miles
	//		Preconditions: Entered miles is greater than 0
	//		Postconditions: None
	//		Returns: Gallons of fuel consumed after the specified number of miles.
	double calcFuelConsumed(double miles, TripLeg::RoadType roadType);

	//	Reduces the current fuel in tank according to the gallons entered
	//		Preconditions: Gallons must be <= to fuel left in tank
	//		Postconditions: Current fuel is reduced by gallons entered
	void consumeFuel(double gallons);

	//	Returns the MPG based on the roadtype entered
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: MPG in gallons
	int getMPG(TripLeg::RoadType type);

	//	Fills the tank to full
	//		Preconditions: None
	//		Postconditions: None
	void fillTank();

	//	Overloaded << operater to stream out the following comma delineated:
	//		make << model << engineSize << engineCylinders << tanksize << cityMPG << highwayMPG << currentFuel
	friend std::ostream & operator <<(std::ostream &lhs, const Vehicle &rhs);

private:
	std::string mMake;
	std::string mModel;
	double 	mEngine;
	int 	mCylinderCnt;
	double 	mTankSize;
	int 	mCityMPG;
	int 	mHighwayMPG;
	double 	mCurrentFuel;
};

#endif /* SRC_VEHICLE_HPP_ */
