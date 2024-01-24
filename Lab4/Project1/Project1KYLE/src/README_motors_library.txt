Functions servoLeft();, servoRight();, and servoStraight(); all are funcitons used to control
	the servo that the sonic sensor is mounted to. If you want the servo to look left, use
	the servoLeft(); funciton and give it about 2 seconds to turn and initialize.

Function sonicSensor(); is for the ultrasonic sensor. Once called, this will return the value
	in inches for how far away an object is from where the sensor is pointing at. 

Function myDelay(); will pass in an int for the number of quarter seconds you want to pass. 
	This funciton was made since timer 0 is modified and the original delay(); funciton
	has no more use.

Function myDelay12Microseconds(); will pass in an int for the number of 12 microseconds you 
	want to pass. This is made since the function delaymicroseconds(); has no use due to the
	modified timer 0.

Functions driveForward();, driveBackward();, driveLeft(); driveRight(); all are for the 
	motors which will pass in 3 parameters. Will pass the number of quarter seconds that
	the wheels will be on for. And a 255 int limit for each wheel where 155 is the lowest 
	int you can pass for compare register A or B.