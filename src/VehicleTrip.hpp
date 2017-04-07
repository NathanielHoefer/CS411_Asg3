//==============================================================================
// Assignment 3 - VehicleTrip Class
//==============================================================================
/*
    File: VehicleTrip.hpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/7/2017

******************************************************************************/

#ifndef TRIP_HPP_
#define TRIP_HPP_

#include <vector>
#include <math.h>
#include <sstream>
#include "TripLeg.hpp"
#include "Vehicle.hpp"
#include "TripParameters.hpp"

namespace vehicleTripNS
{
	static const std::string DLMTR = "|";
}

class VehicleTrip
{
public:
	VehicleTrip(Vehicle *vehicle, TripParameters &parms);
	VehicleTrip(VehicleTrip &trip);		// Copy constructor
	~VehicleTrip();

	// Accessors
	TripParameters 	getParms();
	const Vehicle *getVehicle();		// Normally wouldn't pass back pointer, but doing it for this assignment
	double 		getFuelPurchased();
	double 		getFuelConsumed();
	double 		getCityMiles();
	double 		getHighwayMiles();
	int 		getDriveTime();
	int 		getTripTime();
	int 		getGStationCount();

	//	Executes the trip cycle to run through every leg of the trip, calculating
	// 		total fuel used, time taken, amount spent on gas, and number of miles
	//		Preconditions: None
	//		Postconditions: Member variables are updated per calculations
	void runTrip(std::vector<TripLeg> &legs);

	// 	Overloaded assignment operator to properly handle the pointers
	VehicleTrip & operator =(const VehicleTrip &rhs);

	//	Overloaded << operater to stream out the following:
	//		make << model << engineSize << engineCylinders << tanksize << cityMPG << highwayMPG
	//		<< currentFuel << TripTime << FuelPurchase << FuelConsumed << GasStationCount
	friend std::ostream & operator <<(std::ostream &lhs, VehicleTrip &rhs);

private:
	TripParameters 	mParms;
	Vehicle 	*mVehicle;
	double 		mFuelPurchased;
	double 		mFuelConsumed;
	double 		mCityMiles;
	double 		mHighwayMiles;
	double 		mDriveTime;
	int 		mTripTime;
	int 		mGStationCnt;

	//	Calculates the drive time within a given set of miles
	//		Preconditions: Road type either City or Highway
	//		Returns: The minutes taken to drive the amount of miles
	double calcDriveTime(double miles, TripLeg::RoadType roadType);

	//	Calculates the time taken to refuel based on # of gas stations
	//		Preconditions: Refuel time in minutes
	//		Returns: The minutes taken to refuel during trip
	double calcRefuelTime();

	//	Calculates the total restroom time on the trip based on the # of gas
	//		stations.
	//		Preconditions: Restroom time is in minutes
	//		Returns: The minutes taken to use the restroom during the trip
	double calcRestroomTime();

	//	Calculates the total sleep time on the trip based on the # of gas
	//		stations.
	//		Preconditions: Sleep time is in minutes
	//		Returns: The minutes taken to use the sleep during the trip
	double calcSleepTime();

	//	Increases the total fuel consumed taking into account the road type
	//		Preconditions: Fuel consumed is in gallons
	//		Postconditions: Total fuel consumed increased by the miles driven
	void increaseFuelConsumed(double miles, TripLeg::RoadType roadType);

	//	Increases the total fuel purchased based on the vehicle tank
	//		Preconditions: Valid vehicle
	//		Postconditions: Total fuel purchased increased by difference in gas tank
	void increaseFuelPurchased();

	//	Calculates the amount of fuel to be used on the way to the next station
	//		Returns: number of gallons of fuel needed for next gas station
	double calcFuelUntilStation(std::vector<TripLeg> &tripLegs,
								int currLeg, double legTravelled);
};

#endif /* TRIP_HPP_ */
