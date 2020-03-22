![GitHub](https://img.shields.io/github/license/rufus31415/sharer)
![GitHub release](https://img.shields.io/github/v/release/rufus31415/sharer.net)

![.NET Framework 3.5](https://img.shields.io/badge/.NET_Framework-3.5-blueviolet)
![.NET Framework 4.0](https://img.shields.io/badge/.NET_Framework-4.0-blueviolet)
![.NET Framework 4.5](https://img.shields.io/badge/.NET_Framework-4.5-blueviolet)
![.NET Framework 4.6](https://img.shields.io/badge/.NET_Framework-4.6-blueviolet)
![.NET Framework 4.7](https://img.shields.io/badge/.NET_Framework-4.7-blueviolet)
![.NET Framework 4.8](https://img.shields.io/badge/.NET_Framework-4.8-blueviolet)


![.NET Core 2.0](https://img.shields.io/badge/.NET_Core-2.0-blueviolet)
![.NET Core 2.1](https://img.shields.io/badge/.NET_Core-2.1-blueviolet)
![.NET Core 2.2](https://img.shields.io/badge/.NET_Core-2.2-blueviolet)
![.NET Core 3.0](https://img.shields.io/badge/.NET_Core-3.0-blueviolet)
![.NET Core 3.1](https://img.shields.io/badge/.NET_Core-3.1-blueviolet)

![.NET Standard 2.1](https://img.shields.io/badge/.NET_Standard-2.1-blueviolet)

![Arduino Uno](https://img.shields.io/badge/Arduino-Uno-blue)
![Arduino Mega](https://img.shields.io/badge/Arduino-Mega-blue)
![Arduino Nano](https://img.shields.io/badge/Arduino-Nano-blue)
![Arduino Due](https://img.shields.io/badge/Arduino-Due-blue)

<p align="center">
  <img src="https://raw.githubusercontent.com/Rufus31415/Sharer.NET/master/Sharer.png">
</p>

Sharer is both a <b>.NET and an Arduino Library</b>. It allows a desktop application to <b>read/write variables</b> and <b>remote call functions on Arduino</b>, using the Sharer protocole accross a serial communication.


# Overview
## Arduino code
``` C++
#include <Sharer.h>

// A simple function that sums an integer and a byte and return an integer
int Sum(int a, byte b) {
	return a + b;
}

// a asimple integer
int myVar = 25;

void setup() {
	Sharer.init(115200); // Init Serial communication with 115200 bauds

	// Expose this function to Sharer : int Sum(int a, byte b) 
	Sharer_ShareFunction(int, Sum, int, a, byte, b);

	// Expose this variable to Sharer so that the desktop application can read/write it
	Sharer_ShareVariable(int, myVar);
}

// Run Sharer engine in the main Loop
void loop() {
	Sharer.run();
}
```


## .Net code to interact with shared variables and functions :
``` C#
// Connect to Arduino board
var connection = new SharerConnection("COM3", 115200);
connection.Connect();

// remote call function on Arduino and wait for the result
var result = connection.Call("Sum", 10, 12);

// Display the result
Console.WriteLine("Status : " + result.Status);
Console.WriteLine("Type : " + result.Type);
Console.WriteLine("Value : " + result.Value);

// Status : OK
// Type : int
// Value : 22


// Read the variable
var value = connection.ReadVariable("myVar");
Console.WriteLine("Status : " + value.Status);
Console.WriteLine("Value : " + value.Value);

// Status : OK
// Value : 25


//Write a variable
connection.WriteVariable("myVar", 12);
```

# Get Started
## Sources
Sharer is divided into 2 repositories, one for the Arduino sources and the other for .NET sources
- Arduino : https://github.com/Rufus31415/Sharer
- .NET : https://github.com/Rufus31415/Sharer.NET

## Download and install Arduino library
Please download the Sharer library archive : https://github.com/Rufus31415/Sharer/releases/latest/download/Sharer.zip

Sharer has been tested with Arduino UNO, NANO, MEGA and DUE. It may work with other boards.
Extract so that you get a Sharer directory in your Arduino "libraries" directory : ```C:\Program Files (x86)\Arduino\libraries\Sharer```

You can then enjoy the examples by restarting your Arduino IDE and go to menu ```File / examples / Sharer```.

## Sharer .NET
### Nuget
Sharer.NET is available on nuget : https://www.nuget.org/packages/Sharer/

Use this command line to install it with you package manager :

```Install-Package Sharer```

### Download .NET assembly
Sharer.dll assembly can be downloaded here : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerAsssemblies.zip

This archive contains the nuget package Sharer.nupkg and Sharer.dll compiled in AnyCPU Release for the following targets:
- NET Framework 3.5, 4.0, 4.5.1, 4.5.2, 4.6, 4.6.1, 4.6.2, 4.7, 4.7.1, 4.7.2, 4.8
- NET Core 2.0, 2.1, 2.2, 3.0, 3.1
- NET Standard 2.1

### Try examples
#### Windows Forms
Windows Forms example requires .NET Framework 3.5. It can be downloaded here : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerWindowsFormsExample.zip

![Winforms example](https://raw.githubusercontent.com/Rufus31415/Sharer.NET/master/Resources/winforms.png)

#### Console cross-plateform example
The console example run with .NET Core 3.0. But you don't need any runtime to execute it. The standalone console examples are available here :
- Windows 64 bits : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_win-x64.zip
- Windows 64 bits : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_win-x86.zip
- Windows ARM (for example Windows IOT for Raspberry PI) : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_win-arm.zip
- Linux ARM (for example Raspbian for Raspberry PI) : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_linux-arm.zip
- Linux 64 bits : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_linux-x64.zip
- Mac OS X : https://github.com/Rufus31415/Sharer.net/releases/latest/download/SharerConsoleExample_osx-x64.zip

![Console example](https://raw.githubusercontent.com/Rufus31415/Sharer.NET/master/Resources/console.gif)

# License: MIT 😘
© Rufus31415
See the [license file](https://github.com/Rufus31415/Sharer.NET/blob/master/LICENSE) for details.


# Usage
## Arduino Usage
### Initialization
The header file <Sharer.h> should be included. 

In function ```setup()```, Sharer is initialized by passing a baudrate to function ```Sharer.init(...)```. It internally call ```Serial.init()``` with the same baudrate.

In function ```loop()```, ```Sharer.run()``` should be called. It runs the internal kernel of Sharer that decodes commands received.
``` C++
#include <Sharer.h>

void setup() {
	Sharer.init(115200);
}

void loop() {
	Sharer.run();
}
```

You also can initialize Sharer with another stream, such as the Serial2 of Arduino DUE if you use Serial2 to communication with the desktop application :
``` C++
void setup() {
	// Initialize with another Serial interface
	Serial2.begin(9600);
	Sharer.init(Serial2);
}
```

### Share variables
To add a variable in the shared variable list, you should call the macro ```Sharer_ShareVariable```. Its first argument is the type of the variable, and the second is its name. This macro allows Sharer to have a pointer to the variable, its name, its type and its memory size.
``` C++
byte myByteVar;
long myLongVar;
int myIntArray[2];

void setup() {
	Sharer.init(115200);
	
	Sharer_ShareVariable(byte, myByteVar);
	Sharer_ShareVariable(long, myLongVar);
	Sharer_ShareVariable(int, myIntArray[0]);
	Sharer_ShareVariable(int, myIntArray[1]);
}
```

### Share functions with a return type
To add a variable in the shared function list, you should call the macro ```Sharer_ShareFunction```. Its first argument is the returned type, and the second is its name. Following arguments of the macro describe the argument of the shared function by its type and its name. There is no limit in the number of argument you can share, but all arguments should be shared.

You can share your own functions, but all system functions like analogRead, digitalRead, digitalWrite, millis, ...

``` C++
int Sum(int a, byte b) {
	return a + b;
}

void setup() {
	Sharer.init(115200);

	// Share your function to Sharer : int Sum(int a, byte b) 
	Sharer_ShareFunction(int, Sum, int, a, byte, b);
	
	// Sharer system functions
	Sharer_ShareFunction(int, analogRead, uint8_t, pin);
	Sharer_ShareFunction(bool, digitalRead, uint8_t, pin);
}
```

### Share void functions
Void functions are functions without returned type. You should call the macro ```Sharer_ShareVoid``` to share a void function. The first argument is its name, followed by type and name of each arguments.

``` C++
void TurnLEDOn(void) {
	pinMode(13, OUTPUT);
	digitalWrite(13, true);
}

void SetLEDState(bool state) {
	pinMode(13, OUTPUT);
	digitalWrite(13, state);
}

void setup() {
	Sharer.init(115200);
	
	// Share your void fuctions
	Sharer_ShareVoid(TurnLEDOn);
	Sharer_ShareVoid(SetLEDState, bool, state);
	
	// Sharer system void functions
	Sharer_ShareVoid(digitalWrite, uint8_t, pin);
}
```

### Receive and send regular serial messages


### Capabilities

## .NET usage



# How it works
Sharer uses a unique protocole called the Sharer Protocole. Every serial commands received by the Arduino are interprated.


To be continued, I promise... 😉

![Sharer](https://raw.githubusercontent.com/Rufus31415/Sharer.NET/master/Resources/RemoteFunctionCall.png)

