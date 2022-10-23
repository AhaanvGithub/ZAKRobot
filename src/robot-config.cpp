#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor roller_motor = motor(PORT8, ratio18_1, false);
motor front_left = motor(PORT1, ratio18_1, false);
motor back_left = motor(PORT5, ratio18_1, true);
motor back_right = motor(PORT6, ratio18_1, true);
motor front_right = motor(PORT9, ratio18_1, false);
/*vex-vision-config:begin*/
signature VisionSensor__REDROLLER = signature (1, 7193, 9403, 8298, -869, -159, -514, 2.5, 0);
signature VisionSensor__BLUEROLLER = signature (2, -3037, -2207, -2622, 8721, 12163, 10442, 2.5, 0);
signature VisionSensor__DISC = signature (3, -51, 51, 0, -4497, -2375, -3436, 2.5, 0);
vision VisionSensor = vision (PORT3, 150, VisionSensor__REDROLLER, VisionSensor__BLUEROLLER, VisionSensor__DISC);
/*vex-vision-config:end*/
motor discintakelower = motor(PORT2, ratio18_1, true);
motor discintakeupper = motor(PORT4, ratio18_1, true);
motor flywheel = motor(PORT7, ratio6_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}