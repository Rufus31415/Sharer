#pragma once

// maximum number of shared functions
#define _SHARER_MAX_FUNCTION_COUNT	20

// maximum number of shared variables
#define _SHARER_MAX_VARIABLE_COUNT 30

// circle buffer size for user serial message
#define _SHARER_USER_RECEIVE_BUFFER_SIZE	100

// maximum numbre of call to Serial read() each time Sharer.Run() is called
#define _SHARER_MAX_BYTE_READ_PER_RUN	1000
