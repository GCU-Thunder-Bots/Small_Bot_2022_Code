using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Claw;
extern motor Arm;
extern motor Drawbridge;
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor Clamp;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );