/***************************************************************************************
 *
 * Declare the Interface for the Ossining High School Robot
 * 
 */
#pragma once
#include <frc/WPIlib.h>		//Include the FRC Library

using namespace frc;
/*
 * Ultrasonic Sensor Class
 */
class USSensor
{
	public:
		USSensor(unsigned int channel);	//Constructor to intialize - default is off
		float GetRawRange(void);  //Gives unaveraged range value
		void GetSample(void);	//This is used for taking a sample
		float GetRange(void);	//Find the range using the sensor
	private:
		AnalogInput uschannel;
		float averagerange;		//Variable accumulates average range
};
