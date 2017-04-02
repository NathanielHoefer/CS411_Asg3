//==============================================================================
// Assignment 2 - TripLeg Class
//==============================================================================
/*
    File: TripLeg.cpp
    Project: Assignment 2
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

*******************************************************************************/

#include "TripLeg.hpp"

TripLeg::TripLeg()
{
	mDistance = 0;
	mRoadType = DEFAULT;
}

TripLeg::TripLeg(double distance, RoadType roadType)
{
	mDistance = distance;
	mRoadType = roadType;
}

double TripLeg::getDistance() 				{ return mDistance; }
TripLeg::RoadType TripLeg::getRoadType() 	{ return mRoadType; }
