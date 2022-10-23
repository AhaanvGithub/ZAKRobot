using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor roller_motor;
extern motor front_left;
extern motor back_left;
extern motor back_right;
extern motor front_right;
extern signature VisionSensor__REDROLLER;
extern signature VisionSensor__BLUEROLLER;
extern signature VisionSensor__DISC;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;
extern motor discintakelower;
extern motor discintakeupper;
extern motor flywheel;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );