#pragma once
#include <frc/WPIlib.h>
#include "Constants.h"
#include "Ultrasonic.h"
#include "Vision.h"

using namespace frc;
class Tankdrive
{
public: // for functions
	Tankdrive(unsigned int Leftchannel, unsigned int Rightchannel, unsigned int GyroPort, unsigned int UsonicPort);
	void Drive(float left, float right);
	void DirectDrive(float left, float right);
	void SetThrottle(float Ithrottle);
	void AutoDriveGyro(float distance, float speed, float TimeOut);
	void AutoTurnGyro(float angle, float speed);
	void AutoDriveGyroUS(float, float, float);
	int AutoDriveVision(float USrange, float speed, float Maxdistance, float TimeOut);

	double GetREncoder();
	double GetLEncoder();
	void ResetEncoders();
	void ResetGyro();

	double GetAngle();
	void GetUSSample();
	double GetUSRange();
private: // for variables
	Spark Left;
	Spark Right;
	Encoder LWEncoder;
	Encoder RWEncoder;
	AnalogGyro Gyro;
	Timer AutoTimer;
	Vision vision;
	USSensor Usonic;

	float VisionX;
	float throttle;
};
