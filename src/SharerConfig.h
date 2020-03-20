#pragma once

/**************************************************************************/
/*!
	@file SharerConfig.h
	License: MIT (see LICENSE)

	Author: Rufus31415

	Website: https://rufus31415/github.io

	Sharer is a connector library that facilitates communication between an Arduino board and a desktop application (see Sharer.NET library).
	Features :
		- Desktop applicaion can Read/Write variable on Arduino
		- Remote call function on Arduino with arguments and retrieve returned value in the desktop application
		- Get board information
*/
/**************************************************************************/

// maximum number of shared functions
#define _SHARER_MAX_FUNCTION_COUNT	16

// maximum number of shared variables
#define _SHARER_MAX_VARIABLE_COUNT 32

// circle buffer size for user serial message
#define _SHARER_USER_RECEIVE_BUFFER_SIZE	64

// maximum number of call to Serial.read() each time Sharer.Run() is called
#define _SHARER_MAX_BYTE_READ_PER_RUN	1000
