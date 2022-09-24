from vex import *
import urandom

brain=Brain()

controller = Controller(PRIMARY)

motor_left_1 = Motor(Ports.PORT1, GearSetting.RATIO_18_1, False)
motor_left_2 = Motor(Ports.PORT5, GearSetting.RATIO_18_1, False)
motor_right_1 = Motor(Ports.PORT6, GearSetting.RATIO_18_1, False)
motor_right_2 = Motor(Ports.PORT9, GearSetting.RATIO_18_1, False)

wait(30, MSEC)

def mecanum_drive():
    while True:
        motor_left_1.set_velocity(
            controller.axis3.position() + 
            controller.axis1.position() + 
            controller.axis4.position() + 
            controller.axis2.position(), 
            PERCENT
        )
        
        motor_left_2.set_velocity(
            controller.axis3.position() - 
            controller.axis1.position() + 
            controller.axis4.position() - 
            controller.axis2.position(), 
            PERCENT
        )

        motor_right_1.set_velocity(
            controller.axis3.position() - 
            controller.axis1.position() - 
            controller.axis4.position() - 
            controller.axis2.position(), 
            PERCENT
        )

        motor_right_2.set_velocity(
            controller.axis3.position() + 
            controller.axis1.position() - 
            controller.axis4.position() + 
            controller.axis2.position(), 
            PERCENT
        )

        motor_left_1.spin(FORWARD)
        motor_left_2.spin(FORWARD)
        motor_right_1.spin(FORWARD)
        motor_right_2.spin(FORWARD)

        wait(5, MSEC)

mecanum_drive()
