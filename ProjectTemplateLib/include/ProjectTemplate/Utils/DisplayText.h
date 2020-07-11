#pragma once

#include <string>

// Introductory Tutorial
constexpr std::string terminalOne_Welcome = "Welcome to Terminal One. User log in required. No user passcode found. Generating passcode. New user passcode is: ";
constexpr std::string terminalOne_LogIn = "Please log into the terminal. And don't forget your passcode, you will not be provided another. :)";
constexpr std::string terminalOne_FireBind = "It appears that the room housing Terminal One is on fire. Please put out the fires. "
												"To do so, please bind the sprinkler system to a sequence on your datapad (Numpad). "
												"Placing your datapad in record mode now. Please hit Enter when finished.";
constexpr std::string terminalOne_FireBound = "Sequence bound to the sprinklers successfully. The following sequence will control the sprinklers: ";
constexpr std::string terminalOne_FireRequest = "Please use the sprinklers to put out the fires.";
constexpr std::string terminalOne_FireOut = "Great! Using the sprinkler systems will use some amount of Water. "
											"Our water accumulation systems will slowly collect more from the air within the ship. Ensure that the fires stay out, as they consume Oxygen. "
											"You know, that stuff you breath? Do not let the ships Oxygen drop to 0%.";

constexpr std::string logInSuccessful = "Log in successful.";
constexpr std::string logInFailed = "Log in failed. Incorrect passcode sequence. Please try again.";



constexpr std::string oxygenAmount = "Percentage of Oxygen: ";
constexpr std::string hullIntegrityAmount = "Percentage of Hull Intact: ";
constexpr std::string temperatureAmount = "Temperature (C): ";
constexpr std::string firesAmount = "Percentage of the room on Fire: ";
constexpr std::string waterAmount = "Percentage of Water: ";