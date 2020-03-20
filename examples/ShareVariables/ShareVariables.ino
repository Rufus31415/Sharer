#include <Sharer.h>


int an_integer = 12;
bool a_boolean = true;
long loopCount = 0;

// Init Sharer and declare your function to share
void setup() {
	Sharer.init(115200); // Init Serial communication with 115200 bauds

	// Share variables for read/write from desktop application
	Sharer_ShareVariable(int, an_integer);
	Sharer_ShareVariable(bool, a_boolean);
	Sharer_ShareVariable(long, loopCount);
}

// Run Sharer engine in the main Loop
void loop() {
	Sharer.run();
	   
	loopCount++; // ;)
}
