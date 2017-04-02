//==============================================================================
// Assignment 2 - WichitaToMonticello
//==============================================================================
/*
    File: WichitaToMonticello.cpp
    Project: Assignment 2
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/5/2017

    Simulates a trip from Wichita to Monticello with a number of vehicles to
    determine which vehicles take the least/most time, require the least/most
    fuel purchased, and require the least/most consumed. This program imports both
    the vehicles and the parameters from the string constants provided at the
    beginning of this file. The results are printed to the console as well as to
    the file specified by the string constant OUTPUT_FILE. Helper functions and
    Test drivers were moved to separate files in order to clean this file.

    Notes: Input values have not been fully checked for values ranging far beyond
    reasonable values since it was not explicitly mentioned in the rubric.

******************************************************************************/

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "VehicleTrip.hpp"
#include "TripLeg.hpp"
#include "Vehicle.hpp"
#include "VehicleRecords.hpp"

using namespace std;

// Helper Function Prototypes
vector<TripLeg> initializeTripLegs();
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime, VehicleTrip leastFuelAdded,
				VehicleTrip mostFuelAdded, VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
				ofstream &output);
void printVehicleStats(VehicleTrip trip);
void printToFile(VehicleTrip trip, ofstream &output);

// Testing Function Prototypes
void tripTesting();
void printExpectedStats(int testCase, double tankSize, int cityMPG, int highwayMPG, int tripTime, double fuelAddedCost,
		double fuelUsedCost, double fuelAdded, double fuelUsed, double fuelRemaining, int fuelStops);

// File name constants
static const string VEHICLE_FILE = "WichitaToMonticello-Vehicles.txt";
static const string PARMS_FILE = "WichitaToMonticello-Input.ini";
static const string OUTPUT_FILE = "WichitaToMonticello-Results.txt";

int main()
{
	cout << "========================================================" << endl;
	cout << "           Wichita to Monticello - Assignment 2         " << endl;
	cout << "========================================================" << endl;

//	tripTesting();	// Used for running test cases

	vector<Vehicle> vehicles;
	vector<TripLeg> tripLegs = initializeTripLegs();
	TripParameters parms;

	// Exits the program if vehicles or parameters are not properly imported
	try {
		vehicles = VehicleRecords::importVehicles(VEHICLE_FILE);
		parms.retrieveParms(PARMS_FILE);
	} catch (invalid_argument &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM" << endl;
		exit(1);
	} catch (exception &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM" << endl;
		exit(1);
	}

	// Run initial trip and initialize output stream
	VehicleTrip initialTrip(vehicles.at(0), parms);
	initialTrip.runTrip(tripLegs);
	ofstream outputStream(OUTPUT_FILE.c_str());
	outputStream << "Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)";
	outputStream << "|CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops" << endl;
	printToFile(initialTrip, outputStream);
	outputStream << endl;

	// Initializes records
	VehicleTrip shortestTime = 	initialTrip;
	VehicleTrip longestTime = 	initialTrip;
	VehicleTrip leastFuelAdded = initialTrip;
	VehicleTrip mostFuelAdded = initialTrip;
	VehicleTrip leastFuelUsed = initialTrip;
	VehicleTrip mostFuelUsed = 	initialTrip;

	// Process each vehicle trip
	for (int i = 1; i < (int)vehicles.size(); i++) {
		VehicleTrip trip(vehicles.at(i), parms);
		trip.runTrip(tripLegs);
		printToFile(trip, outputStream);
		outputStream << endl;

		// Updates records
		if (trip.getTripTime() < shortestTime.getTripTime())
			shortestTime = trip;
		if (trip.getTripTime() > longestTime.getTripTime())
			longestTime = trip;
		if (trip.getFuelPurchased() < leastFuelAdded.getFuelPurchased())
			leastFuelAdded = trip;
		if (trip.getFuelPurchased() > mostFuelAdded.getFuelPurchased())
			mostFuelAdded = trip;
		if (trip.getFuelConsumed() < leastFuelUsed.getFuelConsumed())
			leastFuelUsed = trip;
		if (trip.getFuelConsumed() > mostFuelUsed.getFuelConsumed())
			mostFuelUsed = trip;
	}

	// Print the formatted results
	printResults(shortestTime, longestTime, leastFuelAdded, mostFuelAdded,
			leastFuelUsed, mostFuelUsed, outputStream);
}

// Creates trip leg objects for the trip from Wichita to Monticello
//		Preconditions: None
//		Postconditions: None
//		Returns: a vector containing all of the instantiated trip legs in the
//			correct order
vector<TripLeg> initializeTripLegs()
{
	vector<TripLeg> tripLegs;
	tripLegs.push_back(TripLeg(3.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(23.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.05, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(56.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(50.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(6.8, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(53.5, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(21.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(229, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(2.8, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(74.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(47.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(69.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(24.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(21.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(79.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(208, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(181.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(86.6, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(106.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(8.0, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(45.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.1, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.5, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(22.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(1.7, 	TripLeg::CITY));
	return tripLegs;
}

// Prints the results of the trip to the console and the ofstream provided.
//		Preconditions: The entered vehicle trips have already been run with the
//			stats calculated
//		Postconditions: The formatted results printed to the console and ofstream
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime,
					VehicleTrip leastFuelAdded, VehicleTrip mostFuelAdded,
					VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
					ofstream &output)
{
	cout << "========================================================" << endl;
	cout << "                      Trip Results                      " << endl;
	cout << "========================================================" << endl;

	cout << setw(14) << "" << "Total miles driven = " << fixed << setprecision(2)
			<< shortestTime.getCityMiles() + shortestTime.getHighwayMiles()
			<< endl;
	cout << setw(10) << "" << fixed << setprecision(2) << left
			<< "City = " << setw(12) << shortestTime.getCityMiles();
	cout << fixed << setprecision(2) << "Highway = "
			<< shortestTime.getHighwayMiles() << endl << endl << endl;

	cout << "========================================================" << endl;
	cout << "   1. Vehicle ariving first at Jefferson's Monticello:  " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(shortestTime);
	output << endl;
	printToFile(shortestTime, output);
	output << "  # Vehicle arriving first" << endl;

	cout << "========================================================" << endl;
	cout << "   2. Vehicle arriving last at Jefferson's Monticello: " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(longestTime);
	printToFile(longestTime, output);
	output << "  # Vehicle arriving last" << endl;

	cout << "========================================================" << endl;
	cout << "   3. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelAdded);
	printToFile(leastFuelAdded, output);
	output << "  # Vehicle costing least (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   4. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelAdded);
	printToFile(mostFuelAdded, output);
	output << "  # Vehicle costing most (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   5. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelUsed);
	printToFile(leastFuelUsed, output);
	output << "  # Vehicle costing least (fuel used)" << endl;

	cout << "========================================================" << endl;
	cout << "   6. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelUsed);
	printToFile(mostFuelUsed, output);
	output << "  # Vehicle costing most (fuel used)" << endl;
}

// Prints the formatted vehicle stats from the trip entered to the console
//		Preconditions: The trip entered has already be run
//		Postconditions: Formatted stats are printed
void printVehicleStats(VehicleTrip trip)
{
	stringstream results;
	results << trip;
	string temp;
	string make, model;
	int cityMPG, highwayMPG, tripTime, gStationCnt;
	double tankSize, currentFuel, fuelPurchased, fuelConsumed;

	// Parses the results from stream
	getline(results, temp, ',');
	make = temp;
	getline(results, temp, ',');
	model = temp;
	getline(results, temp, ',');
	getline(results, temp, ',');
	getline(results, temp, ',');
	tankSize = atof(temp.c_str());
	getline(results, temp, ',');
	cityMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	highwayMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	currentFuel = atof(temp.c_str());
	getline(results, temp, ',');
	tripTime = atoi(temp.c_str());
	getline(results, temp, ',');
	fuelPurchased = atof(temp.c_str());
	getline(results, temp, ',');
	fuelConsumed = atof(temp.c_str());
	getline(results, temp, ',');
	gStationCnt = atoi(temp.c_str());

	// Calculations for centering title
	int titleLen = make.size() + model.size() + 1;
	int leftTitleSpace = (56 - titleLen) / 2;

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = fuelPurchased * trip.getParms().getFuelPrice();
	double fuelConsumedCost = fuelConsumed * trip.getParms().getFuelPrice();

	// Formats output
	cout << setw(leftTitleSpace) << "";
	cout << make << " " << model		   << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << fixed << setprecision(2);
	cout << "Tank Size = " << setw(6) << tankSize;
	cout << "gal   City MPG = " << setw(5) << cityMPG;
	cout << "Highway MPG = " << highwayMPG << endl;;
	cout << "--------------------------------------------------------" << endl;
	cout << "Trip time(minutes) = " << setw(7) << tripTime;
	cout << "Trip time(d.hh:mm) = " << days << "." << setfill('0') << right
			<< setw(2) << hours << ":" << setw(2) << minutes << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << setfill(' ');
	cout << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	cout << "Trip cost based on fuel used  = $" << fuelConsumedCost << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fuel added = " << setw(8) << setprecision(4) << fuelPurchased
			<< "gal    Fuel remaining = " << currentFuel << " gal" << endl;
	cout << "Fuel used  = " << setw(8) << fuelConsumed;
	cout << "gal    Fuel stops     = " << gStationCnt << endl << endl << endl;
}

// Appends the vehicle stats from the trip entered to the stream entered
//		Preconditions: Trip entered has already been ran
//		Postcontitions: Trip printed in the following format:
//			Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)|
//			CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops
void printToFile(VehicleTrip trip, ofstream &output)
{
	stringstream results;
	results << trip;
	string temp;

	string make, model;
	int engineCylinders, cityMPG, highwayMPG, tripTime, gStationCnt;
	double engineSize, tankSize, currentFuel, fuelPurchased, fuelConsumed;

	// Parses the results from stream
	getline(results, temp, ',');
	make = temp;
	getline(results, temp, ',');
	model = temp;
	getline(results, temp, ',');
	engineSize = atof(temp.c_str());
	getline(results, temp, ',');
	engineCylinders = atoi(temp.c_str());
	getline(results, temp, ',');
	tankSize = atof(temp.c_str());
	getline(results, temp, ',');
	cityMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	highwayMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	currentFuel = atof(temp.c_str());
	getline(results, temp, ',');
	tripTime = atoi(temp.c_str());
	getline(results, temp, ',');
	fuelPurchased = atof(temp.c_str());
	getline(results, temp, ',');
	fuelConsumed = atof(temp.c_str());
	getline(results, temp, ',');
	gStationCnt = atoi(temp.c_str());

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = fuelPurchased * trip.getParms().getFuelPrice();
	double fuelConsumedCost = fuelConsumed * trip.getParms().getFuelPrice();

	// Format:
	//	Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)|
	//	CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops
	output << left << setfill(' ') << setw(9) << make << "|" << setw(15) << model << "|";
	output << right << fixed << setfill('0') << setw(4) << setprecision(1) << engineSize << "|";
	output << engineCylinders << "|";
	output << setw(4) << tankSize << "|";
	output << setw(2) << cityMPG << "|" << setw(2) << highwayMPG << "|";
	output << setw(4) << tripTime << "|";
	output << days << "." << setfill('0') << right << setw(2) << hours << ":" << setw(2) << minutes << "|";
	output << setprecision(2) << setw(7) << fuelAddedCost << "|" << setw(7) << fuelConsumedCost << "|";
	output << setprecision(4) << setw(9) << fuelConsumed << "|" << setw(9) << fuelPurchased << "|";
	output << setw(9) << currentFuel << "|" << setw(2) << gStationCnt;
}

// Used with tripTesting() for outputting the expected values for the test
//		Preconditions: None
//		Postconditions: Entered values are printed in the same format as the printVehicleStats()
void printExpectedStats(int testCase, double tankSize, int cityMPG, int highwayMPG, int tripTime, double fuelAddedCost,
		double fuelUsedCost, double fuelAdded, double fuelUsed, double fuelRemaining, int fuelStops)
{
	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	cout << "========================================================" << endl;
	cout << "                     Test Case: " << testCase 			<< endl;
	cout << "========================================================" << endl;
	cout << "                       Expected: " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << fixed << setprecision(2);
	cout << "Tank Size = " << setw(6) << tankSize;
	cout << "gal   City MPG = " << setw(5) << cityMPG;
	cout << "Highway MPG = " << highwayMPG << endl;;
	cout << "--------------------------------------------------------" << endl;
	cout << "Trip time(minutes) = " << setw(7) << tripTime;
	cout << "Trip time(d.hh:mm) = " << days << "." << setfill('0') << right
			<< setw(2) << hours << ":" << setw(2) << minutes << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << setfill(' ');
	cout << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	cout << "Trip cost based on fuel used  = $" << fuelUsedCost << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fuel added = " << setw(8) << setprecision(4) << fuelAdded
			<< "gal    Fuel remaining = " << fuelRemaining << " gal" << endl;
	cout << "Fuel used  = " << setw(8) << fuelUsed;
	cout << "gal    Fuel stops     = " << fuelStops << endl;
	cout << "========================================================" << endl;
}

// Tests small vehicle trips that include calculations done by hand to compare results
//		generated by algorithm
//		Preconditions: None
//		Postconditions: Each test case is run and printed to the screen with actual
//			and expected results
void tripTesting()
{
	// Test Case 1 - Confirmed
	// Vehicle travels 1 trip leg containing 1 gas station, no refuel
	Vehicle v1("Actual:", "", 1, 1,
			2, 		// Tank size
			15, 	// cityMPG
			30);
	vector<TripLeg> l1;
	l1.push_back(TripLeg(20, TripLeg::CITY));			// Trip is 20 miles
	TripParameters p1(30, 60, 2.5, 20, 10, 15, 8, 15);		// Station every 15 miles
	VehicleTrip t1(v1, p1);
	t1.runTrip(l1);
	printExpectedStats(1, 2, 15, 30, 40, 0, 3.33, 0, 1.3333, .6666, 0);
	printVehicleStats(t1);

	// Test Case 2 - Confirmed
	// Vehicle travels 1 trip leg containing 1 gas station, need to refuel 1 time
	Vehicle v2("Actual:", "", 1, 1,
			1.75, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l2;
	l2.push_back(TripLeg(20, TripLeg::CITY));	// Trip is 20 miles
	TripParameters p2(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t2(v2, p2);
	t2.runTrip(l2);
	printExpectedStats(
			2, 		// Test Case
			1.75, 	// Tank
			10, 	// CityMPG
			30, 	// HighwayMPG
			60, 	// Trip Time
			3.75, 	// Fuel Added Cost
			5, 		// Fuel Used Cost
			1.5, 	// Fuel Added
			2, 		// Fuel Used
			1.25, 	// Fuel Remaining
			1);		// Fuel Stops
	printVehicleStats(t2);

	// Test Case 3 - Confirmed
	// Vehicle travels 1 trip leg containing 3 gas stations, need to refuel 1 time
	Vehicle v3("Actual:", "", 1, 1,
			3.5, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l3;
	l3.push_back(TripLeg(50, TripLeg::CITY));	// Trip is 50 miles
	TripParameters p3(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t3(v3, p3);
	t3.runTrip(l3);
	printExpectedStats(
			3, 		// Test Case
			3.5, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			120, 	// Trip Time
			7.5, 	// Fuel Added Cost
			12.5,	// Fuel Used Cost
			3,	 	// Fuel Added
			5, 		// Fuel Used
			1.5, 	// Fuel Remaining
			1);		// Fuel Stops
	printVehicleStats(t3);

	// Test Case 4 - Confirmed
	// Vehicle travels 1 trip leg containing 4 gas stations, need to refuel 2 times
	Vehicle v4("Actual:", "", 1, 1,
			3.6, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l4;
	l4.push_back(TripLeg(70, TripLeg::CITY));	// Trip is 70 miles
	TripParameters p4(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t4(v4, p4);
	t4.runTrip(l4);
	printExpectedStats(
			4, 		// Test Case
			3.6, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			190, 	// Trip Time
			15, 	// Fuel Added Cost
			17.5,	// Fuel Used Cost
			6,	 	// Fuel Added
			7, 		// Fuel Used
			2.6, 	// Fuel Remaining
			2);		// Fuel Stops
	printVehicleStats(t4);

	// Test Case 5 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	Vehicle v5("Actual:", "", 1, 1,
			4.5, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l5;
	l5.push_back(TripLeg(50, TripLeg::CITY));
	l5.push_back(TripLeg(50, TripLeg::CITY));	// Trip is 100 miles
	TripParameters p5(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			3, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t5(v5, p5);
	t5.runTrip(l5);
	printExpectedStats(
			5, 		// Test Case
			4.5, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			265, 	// Trip Time
			22, 	// Fuel Added Cost
			25,		// Fuel Used Cost
			8.8,	// Fuel Added
			10, 	// Fuel Used
			3.3, 	// Fuel Remaining
			2);		// Fuel Stops
	printVehicleStats(t5);

	// Test Case 6 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	// One Trip leg is City, the other Highway
	Vehicle v6("Actual:", "", 1, 1,
			2.4, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l6;
	l6.push_back(TripLeg(50, TripLeg::CITY));
	l6.push_back(TripLeg(50, TripLeg::HIGHWAY));	// Trip is 100 miles
	TripParameters p6(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			2, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t6(v6, p6);
	t6.runTrip(l6);
	printExpectedStats(
			6, 		// Test Case
			2.4, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			235, 	// Trip Time
			14.5, 	// Fuel Added Cost
			18.75,		// Fuel Used Cost
			5.8,	// Fuel Added
			7.5, 	// Fuel Used
			.7, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t6);

	// Test Case 7 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	// One Trip leg is City, the other Highway
	Vehicle v7("Actual:", "", 1, 1,
			2.6, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l7;
	l7.push_back(TripLeg(50, TripLeg::CITY));
	l7.push_back(TripLeg(50, TripLeg::HIGHWAY));	// Trip is 100 miles
	TripParameters p7(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			2, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t7(v7, p7);
	t7.runTrip(l7);
	printExpectedStats(
			7, 		// Test Case
			2.6, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			235, 	// Trip Time
			17.25, 	// Fuel Added Cost
			18.75,		// Fuel Used Cost
			6.9,	// Fuel Added
			7.5, 	// Fuel Used
			2, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t7);

	// Test Case 8 - Confirmed
	// Vehicle travels multiple roadtypes and trip legs to test more realistic trip
	Vehicle v8("Actual:", "", 1, 1,
			1.12, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l8;
	l8.push_back(TripLeg(2.5, 	TripLeg::CITY));
	l8.push_back(TripLeg(3, 	TripLeg::CITY));
	l8.push_back(TripLeg(14.5, 	TripLeg::HIGHWAY));
	l8.push_back(TripLeg(20, 	TripLeg::HIGHWAY));
	l8.push_back(TripLeg(10, 	TripLeg::CITY));	// Trip is 50 miles
	TripParameters p8(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			1, 		// Awake Time
			11);	// Station every 11 miles
	VehicleTrip t8(v8, p8);
	t8.runTrip(l8);
	printExpectedStats(
			8, 		// Test Case
			1.12, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			151, 	// Trip Time
			6.69, 	// Fuel Added Cost
			8.19,		// Fuel Used Cost
			2.675,	// Fuel Added
			3.275, 	// Fuel Used
			.52, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t8);
}

