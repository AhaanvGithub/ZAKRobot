/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\ahaan                                            */
/*    Created:      Sun Oct 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// roller_motor         motor         8               
// front_left           motor         1               
// back_left            motor         5               
// back_right           motor         6               
// front_right          motor         9               
// VisionSensor         vision        3               
// discintakelower      motor         2               
// discintakeupper      motor         4               
// flywheel             motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

// defining movement functions 
void strafe_left_time(double strafe_left_seconds); // strafe left for certain time
void strafe_right_time(double strafe_right_seconds); // strafe right for certain time
void detect_roller_position(double detect_roller_position__position); // detect roller color and spin roller
void go_forward_time(double go_forward_seconds); // go forward for certain time
void go_backward_time(double go_backward_seconds); // go backward for certain time
void turn_left_time(double turn_left_seconds); // turn left for certain time
void turn_right_time(double turn_right_seconds); // turn right for certain time

// temporary functions accounting for current uneven weight distribution
void go_forward_correct_time(double go_forward_correct_seconds); // correction of movement forward
void go_backward_correct_time(double go_backward_correct_seconds); // correction of movement backward
void strafe_left_correct_time(double strafe_left_correct_seconds); // correction of strafing left
void strafe_right_correct_time(double strafe_right_correct_seconds); // correction of strafing right

int Brain_precision = 0, Console_precision = 0, Controller1_precision = 0;
double full_turn_time, position, turning_back_stop, strafing_back_stop, strafe_time, forwardbackward_time;

// function to strafe left
void strafe_left_time(double strafe_left_seconds) {
  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(strafe_left_seconds, seconds);

  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(strafing_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();
  wait(0.2, seconds);

  // strafe_left_correct_time(strafe_left_seconds);
}

// function for strafing right
void strafe_right_time(double strafe_right_seconds) {
  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(strafe_right_seconds, seconds);

  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(strafing_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();
  wait(0.2, seconds);

  // strafe_right_correct_time(strafe_right_seconds);
}

// detect and spin roller
void detect_roller_position(double detect_roller_position__position) {
  front_left.setVelocity(20.0, percent);
  back_left.setVelocity(-20.0, percent);
  front_right.setVelocity(-20.0, percent);
  back_right.setVelocity(20.0, percent);

  // spin all wheels at only 20% velocity
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);
  
}

// function for driving forward
void go_forward_time(double go_forward_seconds) {
  // change velocity of individual wheels
  // wheels have irregular velocities due to motors being physically reversed
  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(200.0, percent);

  // spin all wheels
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  // keep spinning until time asked by user is finished
  wait(go_forward_seconds, seconds);

  // backstop mechanism to make wheels stop more abruptly
  // minimizes drag on wheels as well

  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(turning_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();

  wait(0.2, seconds);

  // tmeporary function to account for any weight bias
  // go_forward_correct_time(go_forward_seconds);
}

// function for driving backward
void go_backward_time(double go_backward_seconds) {
  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(200.0, percent);

  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(go_backward_seconds, seconds);
  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(turning_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();
  
  wait(0.2, seconds);

  // go_backward_correct_time(go_backward_seconds);
}

// function for turning left
void turn_left_time(double turn_left_seconds) {
  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(200.0, percent);
  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(turn_left_seconds, seconds);

  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(-200.0, percent);
  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(turning_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();

  wait(0.2, seconds);
}

// function for turning right
void turn_right_time(double turn_right_seconds) {
  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(200.0, percent);
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(turn_right_seconds, seconds);

  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(-200.0, percent);
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(turning_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();

  wait(0.2, seconds);
}

// temporary function for correcting weight bias to go forward
void go_forward_correct_time(double go_forward_correct_seconds) {
  double correction_time_foward = go_forward_correct_seconds / 7.0; 

  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(correction_time_foward, seconds);

  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(200.0, percent);

  front_left.spin(reverse);
  back_right.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);

  wait(strafing_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();

  wait(0.2, seconds);
  
  // turn_left_time(go_forward_correct_seconds / 14.0);
}

// temporary function for correcting weight bias to go backward
void go_backward_correct_time(double go_backward_correct_seconds) {
  double correction_time_backward = go_backward_correct_seconds / 7.0; 
  front_left.setVelocity(-200.0, percent);
  back_left.setVelocity(-200.0, percent);
  front_right.setVelocity(-200.0, percent);
  back_right.setVelocity(-200.0, percent);

  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(correction_time_backward, seconds);

  front_left.setVelocity(200.0, percent);
  back_left.setVelocity(200.0, percent);
  front_right.setVelocity(200.0, percent);
  back_right.setVelocity(200.0, percent);
  
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);

  wait(strafing_back_stop, seconds);

  front_left.stop();
  back_left.stop();
  front_right.stop();
  back_right.stop();
  wait(0.2, seconds);

  turn_right_time(go_backward_correct_seconds);
}

// temporary function for correcting strafe left weight bias
void strafe_left_correct_time(double strafe_left_correct_seconds) {
  turn_right_time(strafe_left_correct_seconds / 14.0);
}

// temporary function for correcting strafe right weight bias
void strafe_right_correct_time(double strafe_right_correct_seconds) {
  turn_left_time(strafe_right_correct_seconds / 14.0);
}

// "when started" hat block
int whenStarted1() {
  return 0;
}

// once driver control is enabled
int ondriver_drivercontrol_0() {
  // helps determine what color the robot is playing as
  // also helps choose whether other team has an autonomous or not
  position = 3.0; 

  // variables that record time to make wheel movements (seconds)
  // more rigid and turn 180*
  turning_back_stop = 0.1;
  full_turn_time = 0.9;
  strafing_back_stop = 0.0;
  forwardbackward_time = 0.9;

  // spin all wheels forward
  roller_motor.setVelocity(0, percent);
  front_left.spin(forward);
  back_right.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);
  roller_motor.spin(forward);
  discintakelower.spin(forward);
  discintakeupper.spin(forward);
  flywheel.spin(forward);
  
  // using controller axis 1, and 2, calculate robot strafe and drive
  // using controller axis 4, turn the robot left and right
  while (true) {
    front_left.setVelocity(Controller1.Axis1.position() + (Controller1.Axis2.position() + Controller1.Axis4.position()), percent);
    back_left.setVelocity(Controller1.Axis1.position() - (Controller1.Axis2.position() + Controller1.Axis4.position()), percent);
    front_right.setVelocity(Controller1.Axis1.position() - (Controller1.Axis2.position() - Controller1.Axis4.position()), percent);
    back_right.setVelocity(Controller1.Axis1.position() + (Controller1.Axis2.position() - Controller1.Axis4.position()), percent);
    wait(5, msec);
  }
  return 0;
}

// tells the robot and us where it thinks it is on the field
// useful for improvising if another team already has an autonomous
void whenbrainpressed() {
  Brain.Screen.newLine();

  if (position >= 3.0) {
    position = 0;
  } else {
    position += 1;
  }

  if (position == 0.0) {
      Brain.Screen.setFillColor(red);
      Brain.Screen.print("LEFT");
      Brain.Screen.print(position);
  } else if (position == 1.0) {
      Brain.Screen.setFillColor(red);
      Brain.Screen.print("RIGHT");
      Brain.Screen.print(position);
  } else if (position == 2.0) {
      Brain.Screen.setFillColor(blue);
      Brain.Screen.print("LEFT");
      Brain.Screen.print(position);
  } else {
      Brain.Screen.setFillColor(blue);
      Brain.Screen.print("RIGHT");
      Brain.Screen.print(position);
  }
}


void move_roller_forward() {
  roller_motor.setVelocity(100.0, percent);
}

void stop_roller() {
  roller_motor.setVelocity(0, percent);
}

void move_roller_backward() {
  roller_motor.setVelocity(-100, percent);
}

void work_the_disk() {
  discintakelower.setVelocity(100, percent);
  discintakeupper.setVelocity(100, percent);
  flywheel.setVelocity(100, percent);
}

void stop_work_the_disk() {
  discintakelower.setVelocity(0, percent);
  discintakeupper.setVelocity(0, percent);
  flywheel.setVelocity(0, percent);
}

void VEXcode_driver_task() {
  // Start the driver control tasks....
  vex::task drive0(ondriver_drivercontrol_0);
  while(Competition.isDriverControl() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  drive0.stop();
  return;
}

void VEXcode_auton_task() {
  // Start the auton control tasks....
  while(Competition.isAutonomous() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  return;
}

int main() {
  vex::competition::bStopTasksBetweenModes = false;
  Competition.autonomous(VEXcode_auton_task);
  Competition.drivercontrol(VEXcode_driver_task);

  // register event handlers
  Brain.Screen.pressed(whenbrainpressed);
  Controller1.ButtonL1.pressed(move_roller_forward);
  Controller1.ButtonL2.pressed(stop_roller);
  Controller1.ButtonR1.pressed(move_roller_backward);
  Controller1.ButtonR2.pressed(stop_roller);
  Controller1.ButtonA.pressed(work_the_disk);
  Controller1.ButtonB.pressed(stop_work_the_disk);

  wait(15, msec);
  
  // post event registration
  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);
  whenStarted1();
}
