#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({-15, -17}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_mg({20, 18}, pros::MotorGearset::green);
pros::MotorGroup claw ({13},pros::MotorGearset::red);

// pros::ADIDigitalOut claw('A'); // Create a pneumatic in port A
pros::MotorGroup lift({-19, 16}, pros::MotorGearset::red);

Drivetrain drivetrain(
    &left_mg, // left motor group
    &right_mg, // right motor group
    11.5, // track width (12 inches)
    Omniwheel::NEW_275, // using new 4" omnis
    200, // drivetrain rpm
    2); // horizontal drift (2 is standard for normal drive)

Imu imu(14); 
OdomSensors sensors(nullptr, // vertical tracking wheel 1
                    nullptr, // vertical tracking wheel 2
                    nullptr, // horizontal tracking wheel 1
                    nullptr, // horizontal tracking wheel 2
                    &imu); // inertial sensor

 // --- PID Controllers ---
// Placeholder values - you will need to tune these!
ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
ControllerSettings angular_controller(2, 0, 10, 3, 1, 100, 3, 500, 0);

Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
/**
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "He");
    chassis.calibrate();

	// pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

//     right_mg.move_velocity(100);
// 	left_mg.move_velocity(100);
// 	pros::delay(500);
//   right_mg.move_velocity(-100);
//   left_mg.move_velocity(-100);
//   pros::delay(500);
//   right_mg.move_velocity(100);
//   left_mg.move_velocity(100);
// 	pros::delay(500);
// 	right_mg.move_velocity(-100);
//   left_mg.move_velocity(-100);
//   pros::delay(500);
//   right_mg.brake();
//   left_mg.brake();
}
	// claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	// chassis.setPose(-0.1, 62.5, 180);
	// chassis.moveToPoint(19.1, 50.3, 2650);

	// claw.move(50);
    // pros::delay(300);
    // claw.brake();


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */



void opcontrol() {

	// pros::MotorGroup left_mg({15, 17}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	// pros::MotorGroup right_mg({20, 18}, pros::MotorGearset::green);

  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


	while (true) {
		// pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0); 
        // // Left joystick Y-axis controls forward/backward (Linear)
        // Tank Drive

		int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        // Drive
		
		chassis.tank(leftY, rightY);
			
		
			// chassis.arcade(-rightX , -leftY);
		
        

		
		
		
				// int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
				// int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		
				// int leftPower = leftY + rightX;
				// int rightPower = leftY - rightX;
		
				// left_mg.move(leftPower);
				// right_mg.move(rightPower);
		
				// pros::delay(20);
		// if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		// 	lift.move(100);
		// }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		// 	lift.move(-100);
		// }else{
		// 	lift.move(0);
		// }
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			lift.move(127);
			master.set_text(0, 0, "R1 PRESSED");
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			lift.move(-127);
			master.set_text(0, 0, "R2 PRESSED");
		}
		else {
			lift.move(0);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			claw.move(50);
			master.set_text(0, 0, "L1 PRESSED");
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			claw.move(-50); // Close claw
			master.set_text(0, 0, "L2 PRESSED");
		}
		else{
			claw.brake();
		}
		// if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        //     autonomous();
        // }

		// if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		// 	claw.set_value(true); // Extend
		// 		// Retract
		// }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		// 	claw.set_value(false);
		// }
		// pros::delay(20);
		}
    }
