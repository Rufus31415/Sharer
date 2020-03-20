/*
	Name:		UserMessages.ino
	Author:	rufu31415 

	This example shows how to use Sharer library to send custom messages to a desktop application
*/

#include <Sharer.h>


void setup() {
	// Init Sharer on Serial at 115200 bauds
	Sharer.init(115200);
}


void loop() {
  
	Sharer.run();

	// If the desktop application sent a user message
	// Run Sharer, this is essential to call it at every loop
	if (Sharer.available()) {
		
		Sharer.print("You just wrote ");		// Send a string
		Sharer.print(Sharer.available());		// send a number
		Sharer.println(" character(s) : ");		// send a string and a new line
		Sharer.print("--> ");
			   
		// Write all received characters
		while (Sharer.available()) Sharer.write(Sharer.read());

		Sharer.println();
	}

	


}
