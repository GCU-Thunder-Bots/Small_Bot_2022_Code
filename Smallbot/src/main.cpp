/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\colea                                            */
/*    Created:      Wed Feb 09 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Claw                 motor         1               
// Arm                  motor         12              
// Drawbridge           motor         20              
// Controller1          controller                    
// Drivetrain           drivetrain    10, 11          
// Clamp                motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

competition Competition;

motor Claw = motor(PORT1, ratio36_1, false);
motor Arm = motor(PORT12, ratio36_1, true);
motor Drawbridge = motor(PORT20, ratio36_1, false);
controller Controller1 = controller(primary);
motor LeftDriveSmart = motor(PORT10, ratio6_1, false);
motor RightDriveSmart = motor(PORT11, ratio6_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
motor Clamp = motor(PORT15, ratio18_1, false);


void pre_auton(void) {
  vexcodeInit();
}

//Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;
double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

//Autonomous Settings
int desiredValue = 200;
int desiredTurnValue = 0;

int error; //SensorValue - DesiredValue : Positional Value
int prevError = 0; //Position 20 miliseconds ago
int derivative; //error - prevError : Speed
int totalError; //totalError = totalError + error

int turnerror; //SensorValue - DesiredValue : Positional Value
int turnprevError = 0; //Position 20 miliseconds ago
int turnderivative; //error - prevError : Speed
int turntotalError; //totalError = totalError + error

bool resetDriveSensors = false;

//variables modified for use
bool enableDrivePID = true;


int drivePID(){
  while(enableDrivePID){
    
    if (resetDriveSensors) {
      resetDriveSensors = false;

      LeftDriveSmart.setPosition(0,degrees);
      RightDriveSmart.setPosition(0,degrees);

    }
    
    
    
    
    //test test testss
    //Get the position of both motors
    int leftMotorPosition = LeftDriveSmart.position(degrees);
    int rightMotorPosition = RightDriveSmart.position(degrees);



    ////////////////////////////////
    //Lateral movement PID
    ///////////////////////////

    //Get average of the two motors
    int averagePosition = (leftMotorPosition + rightMotorPosition)/2;
    
    //Potential
    error = averagePosition - desiredValue;

    //Derivative
    derivative = error - prevError;

    //Integral
    totalError += error;

    double lateralMotorPower = error * kP + derivative * kD + totalError * kI;
    ////////////////////////////////////////////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////////////////////////////////////
    //Turning movement PID
    /////////////////////////////////////////////////////////////////////////////////

    //Get average of the two motors
    int turnDifference = leftMotorPosition - rightMotorPosition;
    
    //Potential
    turnerror = averagePosition - desiredValue;

    //Derivative
    turnderivative = turnerror - turnprevError;

    //Integral
    // turntotalError += turnerror;

    double turnMotorPower = turnerror * turnkP + turnderivative * turnkD + totalError * turnkI;
    ////////////////////////////////////////////////////////////////////////////////////////

    LeftDriveSmart.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    RightDriveSmart.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    //code
    prevError = error;
    turnprevError = error;
    vex::task::sleep(20);
    
  }

  return 1;
}

void autonomous(void){
  vex::task BillWiTheScienceFi(drivePID);

  resetDriveSensors = true;
  desiredValue = 100;
  desiredTurnValue = 600;

  vex::task::sleep(1000);

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 300;

}

//Above is the autonomous


int main() {
  enableDrivePID = false;  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
