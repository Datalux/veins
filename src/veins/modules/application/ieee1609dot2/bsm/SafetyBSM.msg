//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//


packet SafetyBSM{
    char DSRC_MessageID; 		// used by parser to determine how to parse the rest of the message
    char msgCount; 				// incremented with each successive trasmission of a BSM
    int temporaryID;			// helps a receiver correlate a stream of BSMs from a given sender
    int DSecond; 				// current time, modulo one minute, with resolution 1 millisecond
    int latitude;				// resolution 1/10 microdegree
    int longitude;				// resolution 1/10 microdegree
    int elevation; 				// resolution 0.1 meter
    int positionalAccuracy; 	// conveys the one-standard-deviation position error along axies
    int trasmisionAndSpeed; 	// vehicle transmission (gear) and speed with resolution 1 cm/seconds
    int heading; 				// compass heading of vehicle's motion, resolution 1/80 degree.
    char steeringWheelAngle;	// current position of the streering wheel, resolution 1.5 degree
    int accelerationSet4Way; 	// longitudinal acceleration, lateral accel., vertical accel. and yaw rate   
    int brakeSystemStatus; 		// conveys whether or not braking is active on each of four wheels, 
    							// also conveys the status of Traction Control, Anti-Lock Brakes, Stability
    							// Control, Brake Boost and Auxiliary Brakes
	int vehicleSize;			// Vehicle length and width, resolution 1 cm
    
}
