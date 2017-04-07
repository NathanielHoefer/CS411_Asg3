//==============================================================================
// Assignment 3 - Vehicle Records Class
//==============================================================================
/*
    File: VehicleRecords.hpp
    Project: Assignment 3
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/2/2017

******************************************************************************/

#ifndef SRC_VEHICLERECORDS_HPP_
#define SRC_VEHICLERECORDS_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "Vehicle.hpp"

namespace vehicleRecordsNS
{
	static const std::string DLMTR = "|";
}


class VehicleRecords
{
	// Class cannot be instantiated
	VehicleRecords() {};

public:


	// Imports and creates vehicle objects from the file passed
	// 		Preconditions: File Format:
	//			Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway
 	// 			Lines beginning with '#' are treated as comments
	//		Postconditions: None
	// 		Returns: Array containing all of the Vehicle objects
	static std::vector<Vehicle *> importVehicles(std::string file) throw (std::invalid_argument);
};

#endif /* SRC_VEHICLERECORDS_HPP_ */
