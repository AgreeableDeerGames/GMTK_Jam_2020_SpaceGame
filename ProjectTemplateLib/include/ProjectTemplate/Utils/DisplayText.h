#pragma once

#include <string_view>

// Introductory Tutorial
constexpr std::string_view terminalTutorial_Welcome = "Welcome to Terminal One. User log in required. No user passcode found. Generating passcode. New user passcode is: ";
constexpr std::string_view terminalTutorial_FireBind = "It appears that the room housing Terminal One is on fire. Please put out the fires. "
												"To do so, please bind the sprinkler subsystem to a sequence on your datapad (Numpad). ";
constexpr std::string_view terminalTutorial_FireBound = "Sequence bound to the sprinklers successfully. The following sequence will control the sprinklers: ";
constexpr std::string_view terminalTutorial_FireRequest = "Please use the sprinklers to put out the fires. ";
constexpr std::string_view terminalTutorial_FireWait = "Wait for the fire to go out. ";
constexpr std::string_view terminalTutorial_SprinklersOn = "Great! Using the sprinkler systems will use some amount of Water. "
											"Our water accumulation systems will slowly collect more from the air within the ship. Ensure that the fires stay out, as they consume Oxygen. "
											"You know, that stuff you breathe? Do not let the ships Oxygen drop to 0%. ";

// Binding Process
constexpr std::string_view binding_RecordState = "Placing your datapad in record mode now. Please hit Enter when finished. ";
constexpr std::string_view binding_Request = "Please bind the following subsystem to a sequence on your datapad (Numpad): ";

// Log In/Log Out
constexpr std::string_view logIn_Request = "Please log into the terminal. ";
constexpr std::string_view logOut_Request = "Please log out of the terminal. ";
constexpr std::string_view logIn_DontForget = "And remember not to forget your passcode, you will not be provided another.";

constexpr std::string_view logIn_Successful = "Log in successful. ";
constexpr std::string_view logIn_Failed = "Log in failed. Incorrect passcode sequence. Please try again. ";


// Stats
constexpr std::string_view stats_OxygenAmount = "Percentage of Oxygen: ";
constexpr std::string_view stats_HullIntegrityAmount = "Percentage of Hull Intact: ";
constexpr std::string_view stats_TemperatureAmount = "Temperature (C): ";
constexpr std::string_view stats_FiresAmount = "Percentage of the room on Fire: ";
constexpr std::string_view stats_WaterAmount = "Percentage of Water: ";

// Binds
constexpr std::string_view bind_LogOut = "Log Out";
constexpr std::string_view bind_Sprinklers = "Sprinklers";



/*Your datapad has no graphics, but can control any terminal from anywhere on the ship.*/