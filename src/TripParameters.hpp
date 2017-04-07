//==============================================================================
// Assignment 3 - TripParameters Class
//==============================================================================
/*
    File: TripParameters.hpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/11/2017

******************************************************************************/

#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <string>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

// Constants for all default values
static const int 	CITY_MPH = 		25;
static const int 	HIGHWAY_MPH = 	70;
static const double FUEL_PRICE = 	2.19;	// Per gallon
static const double GAS_DISTANCE = 	80.0;	// Distance between gas stations
static const int 	REFUEL_TIME = 	20;		// in minutes
static const int 	RESTROOM_TIME = 10;		// in minutes
static const int 	NAP_TIME = 		15;		// in minutes
static const int 	AWAKE_TIME = 	8;		// in hours

// Constants for input .ini labels
static const std::string CITY_MPH_LABEL = 		"MphCity";
static const std::string HIGHWAY_MPH_LABEL = 	"MphHighway";
static const std::string FUEL_PRICE_LABEL = 	"FuelPrice";
static const std::string GAS_DISTANCE_LABEL = 	"DistanceBetweenGasStations";
static const std::string AWAKE_TIME_LABEL = 	"TimeBetweenNaps";
static const std::string REFUEL_TIME_LABEL = 	"RefuelTime";
static const std::string RESTROOM_TIME_LABEL = 	"RestroomTime";
static const std::string NAP_TIME_LABEL = 		"NapTime";

class TripParameters
{
public:
	TripParameters();
	TripParameters(int cityMPH, int highwayMPH, double fuelPrice, int refuelTime,
			int restroomTimeMins, int napTimeMins, int awakeTimeHrs, double gasDistance);

	// Accessor Methods
	int 	getCityMph() const;
	int 	getHighwayMph() const;
	double 	getFuelPrice() const;
	int 	getRefuelTime() const;
	int 	getRestroomTime() const;
	int 	getNapTime() const;
	int 	getAwakeTime() const;
	double 	getGasDistance() const;

	// Mutator Methods
	void 	setCityMph(int cityMph);
	void 	setHighwayMph(int highwayMph);
	void 	setFuelPrice(double fuelPrice);
	void 	setRefuelTime(int refuelTime);
	void 	setRestroomTime(int restroomTime);
	void 	setNapTime(int napTime);
	void 	setAwakeTime(int awakeTime);
	void 	setGasDistance(double gastDistance);

	// Retrieves the parameters from the entered file and updates the data as such
	//		Preconditions: The file must contain the labels listed as constants
	//			followed by the '=' and then the value. Extra white space is ignored
	//			and lines beginning with '#' are treated as comment lines and ignored.
	//		Postconditions: Values found in file are imported to member variables.
	//			If the parameter is not found, the default value will be used.
	void retrieveParms(std::string file) throw (std::invalid_argument);

private:
	int mCityMPH;
	int mHighwayMPH;
	double mFuelPrice;
	int mRefuelTimeMins;		// in minutes
	int mRestroomTimeMins;		// in minutes
	int mNapTimeMins;			// in minutes
	int mAwakeTimeMins;			// in minutes
	double mGasDistance;		// in miles
};

#endif /* PARAMETERS_HPP_ */
