#include <Sharer.h>


// A simple function that sums an integer and a byte and return an integer
int Sum(int a, byte b) {
	return a + b;
}

// A simple function that return a^2
float Square(float a) {
	return a * a;
}

void SetLEDState(bool state) {
	pinMode(13, OUTPUT);
	digitalWrite(13, state);
}

// Init Sharer and declare your function to share
void setup() {
	Sharer.init(115200); // Init Serial communication with 115200 bauds

	// Expose this function to Sharer : int Sum(int a, byte b) 
	Sharer_ShareFunction(int, Sum, int, a, byte, b);

	// Expose this function to Sharer : float Square(float a)
	Sharer_ShareFunction(float, Square, float, a);

	// Share the built-in analogRead function
	Sharer_ShareFunction(int, analogRead, uint8_t, pin);

	// Share the built-in digitalRead function
	Sharer_ShareFunction(bool, digitalRead, uint8_t, pin);

	// Expose this function without returned parameters : void SetLEDState(bool state)
	Sharer_ShareVoid(SetLEDState, bool, state);

}

// Run Sharer engine in the main Loop
void loop() {
	Sharer.run();
}
