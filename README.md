The AquaPilot library handles the computations for navigation. It is intended to aid in the development of a boat-based autopilot system. It is initially fed waypoints by the user, and then is constantly fed updates from a GPS and compass module. The calculations are processed and then the appropriate servo rudder values are given (or motor speeds if the boat turns by using dual motors).


USAGE

Installation:
The source files must be copied into the Arduino library directory in a folder named "Aquapilot" (NOT "Aquapilot-Master"). The AquaPilot library should then be available within the Arduino IDE.

Adding Waypoints:
First add lat/lon waypoints by calling addWaypoint(LAT, LON, SPEED) where LAT and LON are latitude and logitude floats in decimal form (NOT IN NMEA FORM!), and speed is a float between 0 and 1 inclusive (I.E. 0.5 would be half speed). Note that the AquaPilot does not automatically return to its start destination. If you need the boat to return, the final waypoint needs to be the starting waypoint. Waypoints are generally accurate within 5 meters. 

Next, the AquaPilot needs to be constantly fed updates from both the GPS an the compass. The calculations are computed upon receiving data from the compass (as the compass is typically updated much more frequently than the GPS).

Feeding GPS Data:
When the Arduino receives a GPS upate, call updateGPS(LAT, LON, HAS_FIX), where LAT and LON are latitude and logitude coordinates in decimal form and HAS_FIX is a boolean value that is true when the GPS has a fix. HAS_FIX is a safety feature so that if the GPS loses fix, the motors outputs will be set to zero so the boat will stop. 

Feeding Compass Data:
When the Arduino receives a compass update, call updateCompass(ANGLE), where angle is the degrees (0 is NORTH, 90 is EAST).

Using Rudder Mode:
Once GPS and Compass data have been fed to the AquaPilot, the rudder value can be retrieved by calling rudder() (a 0-255 PWM value to turn the servo). The motor speed can also be retrieved by calling singleMotorSpeed() (a 0-255 PWM value to output to the motor).

Using Dual-Motor Mode:
Once GPS and Compass data have been fed to the AquaPilot, the engine values can be retieved by calling leftMotorSpeed() and rightMotorSpeed (both are 0-255 PWM values to balance the motors speeds to turn as needed).

CONTACT
You may contact me with any questions at joefortune11@gmail.com


