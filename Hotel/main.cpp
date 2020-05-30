#include <iostream>
#include "HotelManager.h"
#include "TextUtilities.h"

/**
 * @brief	Main entry-point for the application, in particular running new instance
 * 			of Hotel Manager to demonstrate the basic workflow of the  whole system
 *
 * @returns	Exit-code for the process - 0 for success, else an error code.
 */

int main() {
	HotelManager* hm = new HotelManager();
	hm->startConsole();
}