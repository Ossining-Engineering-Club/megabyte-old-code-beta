#include "Pneumatics.h"
#include "Tankdrive.h"
#include "Constants.h"

using namespace frc;

class Robot : public SampleRobot {
private:

	Tankdrive tankdrive;
	Pneumatics pnuematics;
	Joystick LeftStick;
	Joystick RightStick;
	Joystick LiftStick;
	Jaguar Lift;
	Talon Winch;
	Talon ArmL;
	Talon ArmR;
	DigitalInput switch0;		// switch for left or right
	DigitalInput switch1;		// switch for center or not
	DigitalInput switch2;		// switch for direct or wide
	DigitalInput switch3;		// switch for switch or scale
	DigitalInput switch4;		// switch for multi-cube
	DigitalInput switch5;		// switch for if we are corssing the field or not
	AnalogInput AutoPmeter;		// for the Pmeter for a starting delay during auto
	PowerDistributionPanel pdp;
	cs::UsbCamera camera;
	SmartDashboard* dash;

public:
	Robot():
	tankdrive(1, 0, 0, 3),
	pnuematics(0, 1),
	LeftStick(0),
	RightStick(1),
	LiftStick(2),
	Lift(2),
	Winch(3),
	ArmL(4),
	ArmR(5),
	switch0(6),
	switch1(7),
	switch2(8),
	switch3(9),
	switch4(5),
	switch5(0),
	AutoPmeter(1),
	pdp(),
	camera(),
	dash()
	{
		dash->init();
	}

	void RobotInit()
	{
		camera = CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetResolution(XRESOLUTION, YRESOLUTION);
		camera.SetFPS(CAMERAFPS);
		camera.SetExposureManual(CAMERAEXPOSURE);
		camera.SetBrightness(CAMERABRIGHTNESS);
		dash->PutString("VERSION", VERSION);
	}

	void Autonomous()
	{
		pnuematics.compstart();
		std::string PlateColor = DriverStation::GetInstance().GetGameSpecificMessage();
		tankdrive.ResetGyro();
		tankdrive.ResetEncoders();
		dash->PutString("version", VERSION);
		dash->PutString("Message", PlateColor);
		dash->PutNumber("Gyro Angle", tankdrive.GetAngle());
		tankdrive.DirectDrive(0.0, 0.0);
		char CloseSwitch, Scale;
		CloseSwitch = PlateColor[0];
		Scale = PlateColor[1];

		Wait(AutoPmeter.GetVoltage() * 2.0);

							// just straight
		if(!switch0.Get() && !switch1.Get() && !switch2.Get() && !switch3.Get() && !switch4.Get() && !switch5.Get())
			tankdrive.AutoDriveGyro(AUTOSTRIAGHT, AUTOSPEED, AUTOTIMEMAX);

							// center path
		else if(!switch1.Get())
		{
			dash->PutString("Autonomous", "CENTER");
			Lift.Set(AUTOLIFTPOWER);                              //Start Lifting
			tankdrive.AutoDriveGyro(CENTER1, AUTOSPEED, AUTOTIMEMAX);
			if(CloseSwitch == 'L')
			{
				dash->PutString("Autonomous", "CENTER LEFT");
				tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				Lift.Set(AUTOLIFTCONST);
				tankdrive.AutoDriveGyro(CENTER2L, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);		// this is so the lift is definatly higher
				tankdrive.AutoDriveGyro(CENTER3L, AUTOSPEED, AUTOTIMESHORT);
				Wait(AUTOWAIT);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}
			else if(CloseSwitch == 'R')
			{
				dash->PutString("Autonomous", "CENTER RIGHT");
				tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				Lift.Set(AUTOLIFTCONST);
				tankdrive.AutoDriveGyro(CENTER2R, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);		// this is so that the lift is higher
				tankdrive.AutoDriveGyro(CENTER3R, AUTOSPEED, AUTOTIMESHORT);
				Wait(AUTOWAIT);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}
		}

							// direct right
		else if(!switch0.Get() && switch1.Get() && switch2.Get())
		{
			dash->PutString("Autonomous", "DIRECT RIGHT");
			Lift.Set(AUTOLIFTPOWER);
			if(CloseSwitch == 'R')
			{
				tankdrive.AutoDriveGyro(AUTODIRECTRIGHTF, AUTOSPEED, AUTOTIMEMAX);
				Lift.Set(AUTOLIFTCONST);
				Wait(AUTOWAIT);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}
			else
			{
				tankdrive.AutoDriveGyro(AUTODIRECTNF, AUTOSPEED, AUTOTIMEMAX);
				Lift.Set(AUTOLIFTCONST);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTODIRECTDIAG, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTODIRECTFIN, AUTOSPEED, AUTOTIMEMAX);
			}
		}
						// direct left
		else if(switch0.Get() && switch1.Get() && switch2.Get())
		{
			dash->PutString("Autonomous", "DIRECT LEFT");
			Lift.Set(AUTOLIFTPOWER);
			if(CloseSwitch == 'L')
			{
				tankdrive.AutoDriveGyro(AUTODIRECTLEFT1, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(AUTODTURNRIGHT, AUTOTURNSPEED);
				tankdrive.AutoDriveGyro(AUTODIRECTDIAG, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				Lift.Set(AUTOLIFTCONST);
				tankdrive.AutoTurnGyro(AUTODTURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTODIRECTLEFT3, AUTOSPEED, AUTOTIMEMAX);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}
			else
			{
				tankdrive.AutoDriveGyro(AUTODIRECTNF, AUTOSPEED, AUTOTIMEMAX);
				Lift.Set(AUTOLIFTCONST);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTODIRECTDIAG, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTODIRECTFIN, AUTOSPEED, AUTOTIMEMAX);
			}
		}
		// wide right or wide left
		else if(!switch2.Get())
		{
			dash->PutString("Autonomous", "WIDE");

			// DRIVE STRAIGHT --> neither switch or scale is same side as robot with no cross
			if((!switch0.Get() != (CloseSwitch == 'R')) && (!switch0.Get() != (Scale == 'R')) && switch5.Get())
			{
				dash->PutString("Autonomous", "WIDE STRIAGHT");
				tankdrive.AutoDriveGyro(AUTOSTRIAGHT, AUTOSPEED, AUTOTIMEMAX);
			}
			// CROSS THE FIELD FOR SCALE --> If the switch and scale aren't on our side but the cross switch is on
			else if((!switch0.Get() != (CloseSwitch == 'R')) && (!switch0.Get() != (Scale == 'R')) && !switch5.Get())
			{
				dash->PutString("Autonomous", "WIDE CROSSING");
				tankdrive.AutoDriveGyro(AUTOTOMIDFIELD, AUTOSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);
				// Turn at mid field
				if(!switch0.Get())
					tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				else
					tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				tankdrive.AutoDriveGyro(AUTOCROSSFIELD, AUTOSPEED, AUTOTIMEMAX);
				Lift.Set(AUTOLIFTPOWER);
				Wait(AUTOWAIT);
				// turn perpendicular toward scale
				if(!switch0.Get())
					tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				else
					tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				Wait(AUTOWAIT);

				tankdrive.AutoDriveGyro(AUTOMIDTOSCALE, AUTOSLOWSPEED, AUTOTIMEMAX);
				Wait(AUTOWAIT);

				if(!switch0.Get())
					tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				else
					tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);

				tankdrive.AutoDriveGyro(AUTOSCALELEG, AUTOSLOWSPEED, AUTOTIMESHORT);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}
			// SWITCH PATH
			// Do if Switch is on same side as the robot and both are not true (Switch on our side, Scale Switch)
			else if((!switch0.Get() == (CloseSwitch == 'R')) && (switch3.Get() || (!switch0.Get() != (Scale == 'R'))))		// wide left
			{
				dash->PutString("Autonomous", "WIDE SWITCH");
				Lift.Set(AUTOLIFTPOWER);
				tankdrive.AutoDriveGyro(AUTOINDIRECTSWITCH, AUTOSPEED, AUTOTIMEMAX);
				Lift.Set(AUTOLIFTCONST);
				// evaluate if either left or right and then turn accordingly
				if(!switch0.Get())
					tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				else
					tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				tankdrive.AutoDriveGyro(AUTOSWITCHLEG, AUTOLEGSPEED, AUTOTIMEMAX);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);
			}

			// SCALE PATH - Not Straight and Not switch path
			// mulit-cube is only to be used in the scale path
			else
			{
				dash->PutString("Autonomous", "WIDE SCALE");
				Lift.Set(AUTOLIFTPOWERSCALE);
				tankdrive.AutoDriveGyro(AUTOINDIRECTSCALE, AUTOSPEED, AUTOTIMESCALEMAX);

				// evaluate if either left or right and then turn accordingly
				if(!switch0.Get())
					tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
				else
					tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
				Wait(AUTOWAIT);
				// maybe make the auto scale leg a little less so its not right up against the scale
				tankdrive.AutoDriveGyro(AUTOSCALELEG, AUTOSLOWSPEED, AUTOTIMESHORT);
				Lift.Set(AUTOLIFTCONST);
				ArmL.Set(AUTOARMSPEEDOUT);
				ArmR.Set(AUTOARMSPEEDOUT);

				// backup after we place the block
				Wait(AUTOTIMEARM);
				tankdrive.AutoDriveGyro(AUTOSCALELEG, AUTOBACKUPSPEED, AUTOTIMESHORT);

				// check if it is time for multi-cube
				if(!switch4.Get())
				{
					dash->PutString("Autonomous", "WIDE SCALE MULTICUBE");
					Lift.Set(AUTOLIFTDROP);
					Wait(AUTOWAIT);
					if(!switch0.Get())
						tankdrive.AutoTurnGyro(TURNLEFT, AUTOTURNSPEED);
					else
						tankdrive.AutoTurnGyro(TURNRIGHT, AUTOTURNSPEED);
					Wait(AUTOTIMEARM);		// maybe make this wait more for the lift

					Lift.Set(0.0);
					ArmR.Set(AUTOARMSPEEDIN);
					ArmL.Set(AUTOARMSPEEDIN);
					pnuematics.changeSol(0, AUTOARMSTATE);		// open the arms

					dash->PutNumber("Vision exit",
							tankdrive.AutoDriveVision(AUTOUSCUBEDISTANCE, AUTOVISIONSPEED, AUTOTOCUBE, AUTOTIMEMID));

					Wait(AUTOWAIT);
					ArmR.Set(0.0);
					ArmL.Set(0.0);
					pnuematics.changeSol(0, !(AUTOARMSTATE));	// close the arms

					// if the switch is our color, drop it in
					if((!switch0.Get() == (CloseSwitch == 'R')))
					{
						Lift.Set(AUTOLIFTPOWER);
						Wait(AUTOTIMESHORT);
						Lift.Set(AUTOLIFTCONST);
						ArmR.Set(AUTOARMSPEEDOUT);
						ArmL.Set(AUTOARMSPEEDOUT);
					}
				}
			}
		}
		dash->PutNumber("Gyro Angle", tankdrive.GetAngle());
		tankdrive.DirectDrive(0.0, 0.0);
	}

	void OperatorControl()
	{
//		tankdrive.drive(0.0, 0.0);
		pnuematics.compstart();
		std::string PlateColor = DriverStation::GetInstance().GetGameSpecificMessage();
		unsigned short i = 0;
		tankdrive.ResetEncoders();
		while (IsOperatorControl() && IsEnabled())
		{
			for(i = 0; i < 10; i++)
			{
				tankdrive.Drive(LeftStick.GetY(), RightStick.GetY());
				tankdrive.SetThrottle((RightStick.GetZ() - 1) / 2);
			}

			if (LiftStick.GetRawButton(1))
			{
				Winch.Set(LiftStick.GetY());
				Lift.Set(0.0); // was -0.15
			}																// limit is reached!!
			else if(LiftStick.GetY() < 0.1 && LiftStick.GetY() > -0.1)
			{
				Lift.Set(0.0); //was -0.15
				Winch.Set(0.0);
			}
			else
			{
				Lift.Set(LiftStick.GetY());
				Winch.Set(0.0);
			}

			// make sure that these convenctions are correct and that you are using talons!!!
			if(LiftStick.GetRawButton(4))
			{
				ArmR.Set(0.35);
				ArmL.Set(0.2);
			}
			else if(LiftStick.GetRawButton(5))
			{
				ArmL.Set(-0.35);
				ArmR.Set(-0.35);
			}
			else
			{
				ArmL.Set(0.0);
				ArmR.Set(0.0);
			}

			if(LiftStick.GetRawButton(10))
			{
				pnuematics.compstart();
			}
			else if(LiftStick.GetRawButton(11))
			{
				pnuematics.compstop();
			}

			if(LiftStick.GetRawButton(6))		// check the CONVENTIONS!!!
			{
				pnuematics.changeSol(0, true);
			}
			else if(LiftStick.GetRawButton(7))
			{
				pnuematics.changeSol(0, false);
			}
			// for Displaying current vals!!!
		//	dash->PutNumber("Drive Motor #1 Current", pdp.GetCurrent(#));
		//	dash->PutNumber("Drive Motor #2 Current", pdp.GetCurrent(#));
		//	dash->PutNumber("Drive Motor #3 Current", pdp.GetCurrent(#));
		//	dash->PutNumber("Drive Motor #4 Current", pdp.GetCurrent(#));
			dash->PutNumber("Right Encoder", tankdrive.GetREncoder());
			dash->PutNumber("Left Encoder", tankdrive.GetLEncoder());
			dash->PutNumber("Gyro Angle", tankdrive.GetAngle());
			dash->PutNumber("Usonic Range", tankdrive.GetUSRange());
			dash->PutNumber("Auto Potentiometer val", AutoPmeter.GetVoltage() * 2.0);
			dash->PutNumber("switch0", !switch0.Get());
			dash->PutNumber("switch1", !switch1.Get());
			dash->PutNumber("switch2", !switch2.Get());
			dash->PutNumber("switch3", !switch3.Get());
			dash->PutNumber("switch4", !switch4.Get());
			dash->PutNumber("switch5", !switch5.Get());
			dash->PutNumber("Lift Power", LiftStick.GetY());
			dash->PutString("version", VERSION);
			dash->PutString("Message", PlateColor);
		}

	}

};

START_ROBOT_CLASS(Robot)
