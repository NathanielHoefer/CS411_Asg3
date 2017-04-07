//==============================================================================
// Assignment 3 - TripParameters Class
//==============================================================================
/*
    File: TripParameters.cpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/11/2017

******************************************************************************/

#include "TripParameters.hpp"

namespace
{
	// Trims both the right and left side of all white spaces
	// 		Preconditions: String contains chars other than white space
	//		Postconditions: None
	// 		Returns: Reference to trimmed string
	std::string& trimString(std::string &str)
	{
		str.erase(0, str.find_first_not_of(" \t\r\n"));
		str.erase(str.find_last_not_of(" \t\r\n") + 1);
		return str;
	}

	// Determines if the entered string contains only digits
	// 		Preconditions: None
	//		Postconditions: None
	//		Returns: True if string contains only digits
	bool isDigits(std::string str)
	{
		bool isDigits = false;
		str = trimString(str);
		for (int i = 0; i < (int) str.length(); i++ ) {
			if (std::isdigit(str[i]) || str[i] == '.') {
				isDigits = true;
			} else {
				isDigits = false;
				i = str.length();
			}
		}
		return isDigits;
	}

	// Converts an integer to a string
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing the int value
	std::string toString(const int val)
	{
		char buffer[10000];
		std::sprintf(buffer, "%d", val);
		std::string str = buffer;
		return str;
	}
}

TripParameters::TripParameters()
{
	mCityMPH = 			CITY_MPH;
	mHighwayMPH = 		HIGHWAY_MPH;
	mFuelPrice = 		FUEL_PRICE;
	mRefuelTimeMins = 	REFUEL_TIME;
	mRestroomTimeMins = RESTROOM_TIME;
	mNapTimeMins = 		NAP_TIME;
	mAwakeTimeMins = 	AWAKE_TIME * 60;
	mGasDistance = 		GAS_DISTANCE;
}

TripParameters::TripParameters(int cityMPH, int highwayMPH, double fuelPrice, int refuelTime,
		int restroomTimeMins, int napTimeMins, int awakeTimeHrs, double gasDistance)
{
	mCityMPH = 			cityMPH;
	mHighwayMPH = 		highwayMPH;
	mFuelPrice = 		fuelPrice;
	mRefuelTimeMins = 	refuelTime;
	mRestroomTimeMins = restroomTimeMins;
	mNapTimeMins = 		napTimeMins;
	mAwakeTimeMins = 	awakeTimeHrs * 60;
	mGasDistance = 		gasDistance;
}

int 	TripParameters::getCityMph() 		const { return mCityMPH; }
int 	TripParameters::getHighwayMph() 	const { return mHighwayMPH; }
double 	TripParameters::getFuelPrice() 		const { return mFuelPrice; }
int 	TripParameters::getRefuelTime() 	const { return mRefuelTimeMins; }
int 	TripParameters::getRestroomTime() 	const { return mRestroomTimeMins; }
int 	TripParameters::getNapTime() 		const { return mNapTimeMins; }
int 	TripParameters::getAwakeTime() 		const { return mAwakeTimeMins; }
double 	TripParameters::getGasDistance() 	const { return mGasDistance; }

void 	TripParameters::setCityMph(int cityMph) 			{ mCityMPH = cityMph; }
void 	TripParameters::setHighwayMph(int highwayMph) 		{ mHighwayMPH = highwayMph; }
void 	TripParameters::setFuelPrice(double fuelPrice) 		{ mFuelPrice = fuelPrice; }
void 	TripParameters::setRefuelTime(int refuelTime) 		{ mRefuelTimeMins = refuelTime; }
void 	TripParameters::setRestroomTime(int restroomTime) 	{ mRestroomTimeMins = restroomTime; }
void 	TripParameters::setNapTime(int napTime) 			{ mNapTimeMins = napTime; }
void 	TripParameters::setAwakeTime(int awakeTime) 		{ mAwakeTimeMins = awakeTime; }
void 	TripParameters::setGasDistance(double gastDistance) { mGasDistance = gastDistance; }

void TripParameters::retrieveParms(std::string file) throw (std::invalid_argument)
{
	std::ifstream stream;
	stream.open(file.c_str());

	// Validates that the stream is open
	if (stream.fail()) {
		std::string exc = "ERROR - Parameters Import: Unable to open parameter file: " + file;
		throw std::invalid_argument(exc);
	}

	std::string line = "";
	std::string temp = "";
	double value = 0;
	int lineNum = 1;

	// Read through the entire file, line by line
	while (!stream.eof()) {
		std::getline(stream, line);

		// Trim input line
		line = trimString(line);

		// Check to see if it is a comment line or blank line
		if (line[0] != '#' && !line.empty()) {

			// Validates that the line format is correct
			size_t equalIndex = line.find('=');
			if (equalIndex == std::string::npos) {
				std::string exc = "ERROR - Parameters Import: Invalid parameter line [" + toString(lineNum) + "]: \"" + line + "\"";
				throw std::invalid_argument(exc);
			}
			temp = line.substr((int)equalIndex + 1, line.length() - (int)equalIndex);
			temp = trimString(temp);
			line = line.substr(0, (int)equalIndex);
			line = trimString(line);

			// Validates that the parm value is only numeric
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Parameters Import: Invalid parameter value [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			value = std::atof(temp.c_str());

			// Determine Label
			if (line == CITY_MPH_LABEL) {
				mCityMPH = (int) value;
			} else if (line == HIGHWAY_MPH_LABEL) {
				mHighwayMPH = (int) value;
			} else if (line == FUEL_PRICE_LABEL) {
				mFuelPrice = value;
			} else if (line == GAS_DISTANCE_LABEL) {
				mGasDistance = value;
			} else if (line == AWAKE_TIME_LABEL) {
				mAwakeTimeMins = (int) value * 60;
			} else if (line == REFUEL_TIME_LABEL) {
				mRefuelTimeMins = (int) value;
			} else if (line == RESTROOM_TIME_LABEL) {
				mRestroomTimeMins = (int) value;
			} else if (line == NAP_TIME_LABEL) {
				mNapTimeMins = (int) value;
			}
		}
		lineNum++;
	}
}
