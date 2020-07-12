#pragma once

#include <string_view>

// Introductory Tutorial
constexpr std::string_view terminalTutorial_Welcome = "Welcome to Terminal One. User log in required. No user passcode found. Generating passcode. New user passcode is: ";
constexpr std::string_view terminalTutorial_LogIn = "Please log into the terminal. And don't forget your passcode, you will not be provided another. :)";
constexpr std::string_view terminalTutorial_FireBind = "It appears that the room housing Terminal One is on fire. Please put out the fires. "
												"To do so, please bind the sprinkler system to a sequence on your datapad (Numpad). "
												"Placing your datapad in record mode now. Please hit Enter when finished.";
constexpr std::string_view terminalTutorial_FireBound = "Sequence bound to the sprinklers successfully. The following sequence will control the sprinklers: ";
constexpr std::string_view terminalTutorial_FireRequest = "Please use the sprinklers to put out the fires.";
constexpr std::string_view terminalTutorial_FireOut = "Great! Using the sprinkler systems will use some amount of Water. "
											"Our water accumulation systems will slowly collect more from the air within the ship. Ensure that the fires stay out, as they consume Oxygen. "
											"You know, that stuff you breathe? Do not let the ships Oxygen drop to 0%.";

constexpr std::string_view logInSuccessful = "Log in successful.";
constexpr std::string_view logInFailed = "Log in failed. Incorrect passcode sequence. Please try again.";



constexpr std::string_view oxygenAmount = "Percentage of Oxygen: ";
constexpr std::string_view hullIntegrityAmount = "Percentage of Hull Intact: ";
constexpr std::string_view temperatureAmount = "Temperature (C): ";
constexpr std::string_view firesAmount = "Percentage of the room on Fire: ";
constexpr std::string_view waterAmount = "Percentage of Water: ";


/*Your datapad has no graphics, but can control any terminal from anywhere on the ship.*/