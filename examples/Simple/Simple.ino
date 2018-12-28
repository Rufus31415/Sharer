#include <Sharer.h>


// A simple function that sums an integer and a byte and return an integer
int Sum(int a, byte b) {
	return a + b;
}

// A simple function that return a^2
float Square(float a) {
	return a * a;
}

// Init Sharer and declare your function to share
void setup() {
	Sharer.init(115200); // Init Serial communication with 115200 bauds

	// Expose this function to Sharer : int Sum(int a, byte b) 
	Sharer_ShareFunction(int, Sum, int, a, byte, b);

	// Expose this function to Sharer : float Square(float a)
	Sharer_ShareFunction(float, Square, float, a);
}

// Run Sharer engine in the main Loop
void loop() {
	Sharer.run();
}
