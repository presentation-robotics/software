// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoPos3.h"
#include "AutoPosANYMove.h"
#include "AutoPos3Switch.h"
#include "AutoPos3Scale.h"

#include "RobotDefaults.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoPos3::AutoPos3(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoPos3::Initialize() {
	std::printf("2135: Auto Pos 3 - Init\n");
}

// Called repeatedly when this Command is scheduled to run
void AutoPos3::Execute() {
	// Wait for gameData before scheduling next steps
}

// Make this return true when this Command no longer needs to run execute()
bool AutoPos3::IsFinished() {
	bool			isFinished = false;
	std::string 	alliSwitch;			// Holds alliance switch game data setting
	std::string 	scale;				// Holds scale game data setting
	frc::Command	* cmd = nullptr;	// Pointer to command/command group to run

	// Check if gameData has been sent
	alliSwitch = SmartDashboard::GetString(ROBOT_FMSALLISWITCH, ROBOT_FMS_UNINIT);
	// If not the uninitialized string, then new data received
    if (alliSwitch.compare(ROBOT_FMS_UNINIT) != 0) {
		bool allowScale;
		allowScale = frc::SmartDashboard::GetBoolean(ROBOT_ALLOW_SCALE, false);

    	// Select group command for Pos 3 decisions here
    	scale = SmartDashboard::GetString(ROBOT_FMSSCALE, ROBOT_FMS_UNINIT);
    	std::printf("2135: Auto Pos 3 - AlliSwitch: %s Scale: %s Dash: %s\n",
				alliSwitch.c_str(), scale.c_str(), (allowScale) ? "TRUE" : "FALSE");

    	if (alliSwitch.compare(ROBOT_FMS_LEFT) == 0) {		// If alliance switch is LEFT
    		if ((scale.compare(ROBOT_FMS_RIGHT) == 0) && allowScale) {	// Else	scale is RIGHT (case LR) and allowed
    		    cmd = new(AutoPos3Scale);    	    		// Attack the scale
    		}
    		else if (scale.compare(ROBOT_FMS_LEFT) == 0) {	// If scale is LEFT (case LL)
    			cmd = new(AutoPosANYMove);    				// Drive to auto line
    		}
			else {
				std::printf("2135: Auto Pos 3 - unrecognized scale side\n");
				cmd = new(AutoPosANYMove);					// Drive to auto line
			}
    	}
    	else if (alliSwitch.compare(ROBOT_FMS_RIGHT) == 0) { // Else alliance switch is RIGHT
    		if (scale.compare(ROBOT_FMS_LEFT) == 0) {		 // If scale is LEFT (case RL)
    			cmd = new(AutoPos3Switch);    				 // Attack the switch
    		}
    		else if (scale.compare(ROBOT_FMS_RIGHT) == 0) {  // Else scale is RIGHT (case RR)
				// Both are RIGHT, use SmartDashboard (switch or scale)
				if (allowScale) {						// If dashboard setting says TAKE THE SCALE
					cmd = new(AutoPos3Scale);				//		prefer the scale
				}
				else {										// Else (any other value)
					cmd = new(AutoPos3Switch);				//		go for the switch
				}
     		}
			else {
				std::printf("2135: Auto Pos 3 - unrecognized scale side\n");
				cmd = new(AutoPosANYMove);					// Drive to auto line
			}
    	}

    	if (cmd != nullptr) {
    		cmd->Start();									// Start the correct command
    	}
    	isFinished = true;									// Let this command finish
    }
    return isFinished;
}

// Called once after isFinished returns true
void AutoPos3::End() {
	std::printf("2135: Auto Pos 3 - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoPos3::Interrupted() {
	std::printf("2135: Auto Pos 3 - Interrupted\n");
}
