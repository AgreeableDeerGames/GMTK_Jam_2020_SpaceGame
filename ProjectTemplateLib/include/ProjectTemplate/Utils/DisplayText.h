#pragma once

#include <string_view>

// Introductory Tutorial
constexpr std::string_view terminalTutorial_FireBind = "It appears that the room housing Terminal One is on fire. Please put out the fires. "
												"To do so, please bind the sprinkler subsystem to a sequence on your datapad (Numpad). ";
constexpr std::string_view terminalTutorial_FireBound = "Sequence bound to the sprinklers successfully. The following sequence will control the sprinklers: ";
constexpr std::string_view terminalTutorial_FireRequest = "Please use the sprinklers to put out the fires. ";
constexpr std::string_view terminalTutorial_FireWait = "Wait for the fire to go out. ";
constexpr std::string_view terminalTutorial_SprinklersOn = "Great! Using the sprinkler systems will use some amount of Water. "
											"Our water accumulation systems will slowly collect more from the air within the ship. Ensure that the fires stay out, as they consume Oxygen. "
											"You know, that stuff you breathe? Do not let the ships Oxygen drop to 0%. ";

constexpr std::string_view terminalTutorial_BeatIt = "You beat the tutorial. ";
constexpr std::string_view terminalTutorial_FullInstructions = "The full game is much more complicated. "
											"It includes three different consoles that show a subset of the ship state and control different subsystems."
											"The Engine Room shows Oxygen, Fire, Hull Integrity, and Water Reserves. And it controls the sprinklers. "
											"The Biology Lab shows Oxygen, Temperature, Bacteria, and Radiation, and controls the Bateria Population. "
											"Manufacturing shows Temperature, Nanites, and Hull Integrity, and controls the Nanite Population. "
											"These different states also all interact with each other."
											"Fire consumes Oxygen, raising the temperature. Water is from the reactor, irradiating the ship."
											"Bacteria will cleanse the radiation, but also each through the Hull of the ship"
											"Holes in the Hull will allow Oxygen to escape and lower the Temperature."
											"Finally, Nanites will repair the Hull, but often will catch fire."
											"Try your best to manage the remnants of your ship, while it spirals further and further out of control.";


// Welcome
constexpr std::string_view welcome_NewPasscode = "Welcome. User log in required. No user passcode found. Generating passcode. \n\n New user passcode is: ";
constexpr std::string_view welcome_Back = "Welcome back! ";


// Binding Process
constexpr std::string_view binding_RecordState = "Placing your datapad in record mode now. Please hit Enter when finished. ";
constexpr std::string_view binding_Request = "Please bind the following subsystem to a sequence on your datapad (Numpad): ";
constexpr std::string_view binding_BindingComplete = "All available controls have already been bound to your data pad! ";

// Log In/Log Out
constexpr std::string_view logIn_Request = "Please log into the terminal. ";
constexpr std::string_view logOut_Request = "Please log out of the terminal. ";
constexpr std::string_view logIn_DontForget = "And remember not to forget your passcode! You will not be provided another!";

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
constexpr std::string_view bind_SprinklersOn = "Turn On Sprinklers";
constexpr std::string_view bind_SprinklersOff = "Turn Off Sprinklers";
constexpr std::string_view bind_BacteriaOn = "Release Bacteria";
constexpr std::string_view bind_BacteriaOff = "Stop Releasing Bacteria";
constexpr std::string_view bind_AntiBioticBurst = "AntiBiotic Burst";
constexpr std::string_view bind_NaniteOn = "Release Nanites";
constexpr std::string_view bind_NaniteOff = "Stop Releasing Nanites";
constexpr std::string_view bind_EMP = "Electromagnetic Pulse";

// Terminals
constexpr std::string_view terminals_Engine = "Engine Room";
constexpr std::string_view terminals_Bio = "Bio Lab";
constexpr std::string_view terminals_Engineering = "Manufacturing";




/*Your datapad has no graphics, but can control any terminal from anywhere on the ship.*/