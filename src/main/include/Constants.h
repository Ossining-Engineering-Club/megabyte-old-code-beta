#pragma once
#define VERSION "2.0.2"

// drive constants
#define LEFTMULT	.97	//was  1.05 multiplier for the left drive relative to the right

// AUTONOMOUS
#define AUTOSPEED 0.35		// for driving WAS 0.35
#define AUTOSLOWSPEED	0.3
#define AUTOBACKUPSPEED		0.3
#define AUTOTURNSPEED		0.32
#define AUTODISTANCECENTER 69 // in inches for center - was 67.5
#define AUTOGYROCONST 0.016
#define AUTOANGLE 			30
#define ENCODERCONST 0.07766803
#define USDISTANCE 			17	// was 16.5 in

#define AUTOTIMEMAX			6.5

#define AUTOTIMEMID			3.5
#define AUTOTIMESHORT		2.0
#define AUTOTIMEARM			1.0
#define AUTOTIMESCALEMAX	8.5

// auto distances in inches
// for striaght
#define AUTOSTRIAGHT	220.0

// for center paths
#define CENTER1			50.0
#define CENTER2L		50.0
#define CENTER2R		50.0
#define CENTER3L		55.0
#define CENTER3R		55.0

// for wide
#define AUTOWIDEDRIVE		136.0
#define AUTOTOSWITCH		12
#define AUTOWIDEDRIVEMORE	60.0
#define AUTOINDIRECTSWITCH  152.0
#define AUTOSWITCHLEG		25.0
#define AUTOINDIRECTSCALE	290.0	// was 316.0
#define AUTOSCALELEG		15.0
#define AUTOLEGSPEED		0.25

// for direct right
#define AUTODIRECTRIGHTF	110.0			// full way
#define AUTODIRECTNF		50.0			// not full becuase not our color

// for direct General variables
#define AUTODIRECTDIAG		40.0			// drive diagnal
#define AUTODIRECTFIN		100.0

#define AUTODIRECTURNRIGHT	45.0
#define AUTODIRECTURNLEFT	(AUTODIRECTURNRIGHT * -1.0)

// for direct left
#define AUTODIRECTLEFT1		16.0
#define AUTODRIVELEFT2		60.0
#define AUTODIRECTLEFT3		50.0

#define AUTODTURNRIGHT		30
#define AUTODTURNLEFT		(AUTODTURNRIGHT * -1.0)

// FOR AUTO SPECIAL CASE!!!
#define AUTOTOMIDFIELD		220.0
#define AUTOCROSSFIELD		235.0	// was 186.0
#define AUTOMIDTOSCALE		96.0
#define AUTOAPPROACHSCALE	17.0

// FOR MULTI-CUBE!!! --> double check these values again!!!
#define AUTOUSCUBEDISTANCE	18.0		// stop when 18 inches from the wall
#define AUTOTOCUBE			122.0		// was 78.2


// AUTO Constants for LIFT
#define AUTOLIFTPOWER		-0.6		// increase this value!!!
#define AUTOLIFTPOWERSCALE	-0.7		// increase this value!!!
#define AUTOLIFTCONST		-0.15	//  was -.1
#define AUTOLIFTDROP		(AUTOLIFTPOWER * -1.0)
#define AUTOWAITLIFT		2.0		// time to wait for the lift to rise
#define AUTOARMSTATE		true
#define AUTOWAIT			0.15

// Auto Constants for ARM!!!
#define AUTOARMSPEEDOUT	0.35
#define AUTOARMSPEEDIN	(AUTOARMSPEEDOUT * -1.0)

// auto angles
#define TURNLEFT	(TURNRIGHT * -1.0)
#define TURNRIGHT	77

//PID Constants
#define TIMEPERIOD 0.00001
#define PCONSTANT 0.006
#define ICONSTANT 0.025	// was 300
#define DCONSTANT 0		// was 0.000125


// VISION
#define MINVISION 168
#define MAXVISION 198
#define VISIONTARGET 178
#define VISIONMAXHEIGHT 70.0
#define XDIFFERENCEVAL 60
#define AUTODRIVEVISION 0.3
#define AUTOVISIONSPEED	0.36

// for camera values
#define XRESOLUTION			320
#define YRESOLUTION			240
#define CAMERAFPS			30
#define CAMERAEXPOSURE		35
#define CAMERABRIGHTNESS	30

// camera values
#define FPS		30
