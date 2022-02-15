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

using namespace vex;

bool enableDrivePID = true;

int drivePID(){
  while(enableDrivePID){

    
  }

  return 1;
}

void autonomous(void){
  vex::task BillWiTheScienceFi(drivePID);
}

int main() {  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
