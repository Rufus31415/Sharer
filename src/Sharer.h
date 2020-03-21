/**************************************************************************/
/*!
				███████╗██╗  ██╗ █████╗ ██████╗ ███████╗██████╗
				██╔════╝██║  ██║██╔══██╗██╔══██╗██╔════╝██╔══██╗
				███████╗███████║███████║██████╔╝█████╗  ██████╔╝
				╚════██║██╔══██║██╔══██║██╔══██╗██╔══╝  ██╔══██╗
				███████║██║  ██║██║  ██║██║  ██║███████╗██║  ██║
				╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝

	@file Sharer.h
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

#ifndef _SHARER_h
#define _SHARER_h

#include "SharerConfig.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#if defined(TEENSYDUINO) 

//  --------------- Teensy -----------------

#if defined(__AVR_ATmega32U4__)
#define SHARER_BOARD "Teensy 2.0"
#elif defined(__AVR_AT90USB1286__)       
#define SHARER_BOARD "Teensy++ 2.0"
#elif defined(__MK20DX128__)       
#define SHARER_BOARD "Teensy 3.0"
#elif defined(__MK20DX256__)       
#define SHARER_BOARD "Teensy 3.2" // and Teensy 3.1 (obsolete)
#elif defined(__MKL26Z64__)       
#define SHARER_BOARD "Teensy LC"
#elif defined(__MK64FX512__)
#define SHARER_BOARD "Teensy 3.5"
#elif defined(__MK66FX1M0__)
#define SHARER_BOARD "Teensy 3.6"
#else
#error "Unknown board"
#endif

#else // --------------- Arduino ------------------

#if   defined(ARDUINO_AVR_ADK)       
#define SHARER_BOARD "Mega Adk"
#elif defined(ARDUINO_AVR_BT)    // Bluetooth
#define SHARER_BOARD "Bt"
#elif defined(ARDUINO_AVR_DUEMILANOVE)       
#define SHARER_BOARD "Duemilanove"
#elif defined(ARDUINO_AVR_ESPLORA)       
#define SHARER_BOARD "Esplora"
#elif defined(ARDUINO_AVR_ETHERNET)       
#define SHARER_BOARD "Ethernet"
#elif defined(ARDUINO_AVR_FIO)       
#define SHARER_BOARD "Fio"
#elif defined(ARDUINO_AVR_GEMMA)
#define SHARER_BOARD "Gemma"
#elif defined(ARDUINO_AVR_LEONARDO)       
#define SHARER_BOARD "Leonardo"
#elif defined(ARDUINO_AVR_LILYPAD)
#define SHARER_BOARD "Lilypad"
#elif defined(ARDUINO_AVR_LILYPAD_USB)
#define SHARER_BOARD "Lilypad Usb"
#elif defined(ARDUINO_AVR_MEGA)       
#define SHARER_BOARD "Mega"
#elif defined(ARDUINO_AVR_MEGA2560)       
#define SHARER_BOARD "Mega 2560"
#elif defined(ARDUINO_AVR_MICRO)       
#define SHARER_BOARD "Micro"
#elif defined(ARDUINO_AVR_MINI)       
#define SHARER_BOARD "Mini"
#elif defined(ARDUINO_AVR_NANO)       
#define SHARER_BOARD "Nano"
#elif defined(ARDUINO_AVR_NG)       
#define SHARER_BOARD "NG"
#elif defined(ARDUINO_AVR_PRO)       
#define SHARER_BOARD "Pro"
#elif defined(ARDUINO_AVR_ROBOT_CONTROL)       
#define SHARER_BOARD "Robot Ctrl"
#elif defined(ARDUINO_AVR_ROBOT_MOTOR)       
#define SHARER_BOARD "Robot Motor"
#elif defined(ARDUINO_AVR_UNO)       
#define SHARER_BOARD "Uno"
#elif defined(ARDUINO_AVR_YUN)       
#define SHARER_BOARD "Yun"

// These boards must be installed separately:
#elif defined(ARDUINO_SAM_DUE)       
#define SHARER_BOARD "Due"
#elif defined(ARDUINO_SAMD_ZERO)       
#define SHARER_BOARD "Zero"
#elif defined(ARDUINO_ARC32_TOOLS)       
#define SHARER_BOARD "101"
#else
#define SHARER_BOARD "Unknown board"
#endif

#endif

#define SHARER_VERSION_MAJOR	1
#define SHARER_VERSION_MINOR	0
#define SHARER_VERSION_FIX		0

#ifdef F_CPU
#define SHARER_F_CPU F_CPU
#else
#define SHARER_F_CPU -1L
#endif // F_CPU

#ifdef GCC_VERSION
#define SHARER_GCC_VERSION GCC_VERSION
#else
#define SHARER_GCC_VERSION	-1
#endif // GCC_VERSION

#ifdef __cplusplus
#define SHARER___cplusplus __cplusplus
#else
#define SHARER___cplusplus	-1L
#endif // __cplusplus



// Start byte that identifies a Sharer command
#define _SHARER_START_COMMAND_CHAR	0x92


// Here is a very complicated way of implementing param array (__VA_ARGS__) with C++ macros and counting the number of arguments
// This allows to make macros Sharer_ShareFunction, Sharer_ShareVoid and Sharer_ShareVariable work.

#define _SHARER_PP_NARG(...) \
         _SHARER_PP_NARG_(__VA_ARGS__,_SHARER_PP_RSEQ_N())
#define _SHARER_PP_NARG_(...) \
         _SHARER_PP_ARG_N(__VA_ARGS__)
#define _SHARER_PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define _SHARER_PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0



#define _SHARER_GET_OVERRIDE(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, NAME, ...) NAME

#define _SHARER_DECLARE_STATIC_BASE(functionName, argumentType, argumentName) static argumentType functionName ## _arg_ ## argumentName;

#define _SHARER_DECLARE_STATIC10(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC9(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC9(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC8(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC8(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC7(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC7(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC6(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC6(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC5(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC5(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC4(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC4(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC3(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC3(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC2(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC2(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC1(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC1(f, t, n)        _SHARER_DECLARE_STATIC_BASE(f, t, n)
#define _SHARER_DECLARE_STATIC0(...)   

#define _SHARER_DECLARE_STATIC(f, ...) _SHARER__GET_OVERRIDE(__VA_ARGS__, \
        _SHARER_DECLARE_STATIC10, _SHARER_DECLARE_STATIC9_, _SHARER_DECLARE_STATIC9,  _SHARER_DECLARE_STATIC8_, _SHARER_DECLARE_STATIC8,  _SHARER_DECLARE_STATIC7_, _SHARER_DECLARE_STATIC7, _SHARER_DECLARE_STATIC6_, _SHARER_DECLARE_STATIC6, _SHARER_DECLARE_STATIC5_, _SHARER_DECLARE_STATIC5, _SHARER_DECLARE_STATIC4_, _SHARER_DECLARE_STATIC4, _SHARER_DECLARE_STATIC3_, _SHARER_DECLARE_STATIC3, _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(f, __VA_ARGS__);


#define _SHARER_DECLARE_ARG_BASE(functionName, argumentType, argumentName) { PSTR(#argumentName), SharerClass::_SharerFunctionArgType::Type ## argumentType, & functionName ## _arg_ ## argumentName },

#define _SHARER_DECLARE_ARG10(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG9(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG9(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG8(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG8(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG7(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG7(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG6(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG6(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG5(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG5(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG4(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG4(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG3(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG3(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG2(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG2(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG1(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG1(f, t, n)        _SHARER_DECLARE_ARG_BASE(f, t, n)
#define _SHARER_DECLARE_ARG0(...)  

#define _SHARER_DECLARE_CALL_BASE(functionName, argumentType, argumentName) functionName ## _arg_ ## argumentName

#define _SHARER_DECLARE_CALL10(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL9(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL9(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL8(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL8(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL7(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL7(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL6(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL6(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL5(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL5(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL4(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL4(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL3(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL3(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL2(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL2(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL1(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL1(f, t, n)        _SHARER_DECLARE_CALL_BASE(f, t, n)
#define _SHARER_DECLARE_CALL0(...)



#define Sharer_ShareFunction(returnType, functionName, ...)    \
if (Sharer.functionList.count < _SHARER_MAX_FUNCTION_COUNT) {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_STATIC10, _SHARER_DECLARE_STATIC9_, _SHARER_DECLARE_STATIC9,  _SHARER_DECLARE_STATIC8_, _SHARER_DECLARE_STATIC8,  _SHARER_DECLARE_STATIC7_, _SHARER_DECLARE_STATIC7,  _SHARER_DECLARE_STATIC6_, _SHARER_DECLARE_STATIC6,  _SHARER_DECLARE_STATIC5_, _SHARER_DECLARE_STATIC5,  _SHARER_DECLARE_STATIC4_, _SHARER_DECLARE_STATIC4,  _SHARER_DECLARE_STATIC3_, _SHARER_DECLARE_STATIC3,  _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(functionName, __VA_ARGS__);\
    static returnType functionName ## _ret;\
    static const SharerClass::_SharerFunctionArgument functionName ## _args[] = {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_ARG10, _SHARER_DECLARE_ARG9_, _SHARER_DECLARE_ARG9,  _SHARER_DECLARE_ARG8_, _SHARER_DECLARE_ARG8,  _SHARER_DECLARE_ARG7_, _SHARER_DECLARE_ARG7,  _SHARER_DECLARE_ARG6_, _SHARER_DECLARE_ARG6,  _SHARER_DECLARE_ARG5_, _SHARER_DECLARE_ARG5,  _SHARER_DECLARE_ARG4_, _SHARER_DECLARE_ARG4,  _SHARER_DECLARE_ARG3_, _SHARER_DECLARE_ARG3,  _SHARER_DECLARE_ARG2_, _SHARER_DECLARE_ARG2, _SHARER_DECLARE_ARG1_, _SHARER_DECLARE_ARG1, _SHARER_DECLARE_ARG0)(functionName, __VA_ARGS__)\
};\
\
	Sharer.functionList.functions[Sharer.functionList.count].name = PSTR(#functionName);\
        \
    Sharer.functionList.functions[Sharer.functionList.count].Arguments = functionName ## _args;\
        \
    Sharer.functionList.functions[Sharer.functionList.count].argumentCount = _SHARER_PP_NARG(__VA_ARGS__) / 2;\
        \
    Sharer.functionList.functions[Sharer.functionList.count].returnValue.type = SharerClass::_SharerFunctionArgType::Type ## returnType;\
    Sharer.functionList.functions[Sharer.functionList.count].returnValue.pointer = & functionName ##_ret;\
\
    Sharer.functionList.functions[Sharer.functionList.count].pointer = []() {\
        functionName ## _ret = functionName (_SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_CALL10, _SHARER_DECLARE_CALL9_, _SHARER_DECLARE_CALL9,  _SHARER_DECLARE_CALL8_, _SHARER_DECLARE_CALL8,  _SHARER_DECLARE_CALL7_, _SHARER_DECLARE_CALL7,  _SHARER_DECLARE_CALL6_, _SHARER_DECLARE_CALL6,  _SHARER_DECLARE_CALL5_, _SHARER_DECLARE_CALL5,  _SHARER_DECLARE_CALL4_, _SHARER_DECLARE_CALL4,  _SHARER_DECLARE_CALL3_, _SHARER_DECLARE_CALL3,  _SHARER_DECLARE_CALL2_, _SHARER_DECLARE_CALL2, _SHARER_DECLARE_CALL1_, _SHARER_DECLARE_CALL1, _SHARER_DECLARE_CALL0)(functionName, __VA_ARGS__) );\
    };\
        \
    Sharer.functionList.count++;\
\
}

#define Sharer_ShareVoid(functionName, ...)    \
if (Sharer.functionList.count < _SHARER_MAX_FUNCTION_COUNT) {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_STATIC10, _SHARER_DECLARE_STATIC9_, _SHARER_DECLARE_STATIC9,  _SHARER_DECLARE_STATIC8_, _SHARER_DECLARE_STATIC8,  _SHARER_DECLARE_STATIC7_, _SHARER_DECLARE_STATIC7,  _SHARER_DECLARE_STATIC6_, _SHARER_DECLARE_STATIC6,  _SHARER_DECLARE_STATIC5_, _SHARER_DECLARE_STATIC5,  _SHARER_DECLARE_STATIC4_, _SHARER_DECLARE_STATIC4,  _SHARER_DECLARE_STATIC3_, _SHARER_DECLARE_STATIC3,  _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(functionName, __VA_ARGS__);\
    static const SharerClass::_SharerFunctionArgument functionName ## _args[] = {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_ARG10, _SHARER_DECLARE_ARG9_, _SHARER_DECLARE_ARG9,  _SHARER_DECLARE_ARG8_, _SHARER_DECLARE_ARG8,  _SHARER_DECLARE_ARG7_, _SHARER_DECLARE_ARG7,  _SHARER_DECLARE_ARG6_, _SHARER_DECLARE_ARG6,  _SHARER_DECLARE_ARG5_, _SHARER_DECLARE_ARG5,  _SHARER_DECLARE_ARG4_, _SHARER_DECLARE_ARG4,  _SHARER_DECLARE_ARG3_, _SHARER_DECLARE_ARG3,  _SHARER_DECLARE_ARG2_, _SHARER_DECLARE_ARG2, _SHARER_DECLARE_ARG1_, _SHARER_DECLARE_ARG1, _SHARER_DECLARE_ARG0)(functionName, __VA_ARGS__)\
};\
\
    Sharer.functionList.functions[Sharer.functionList.count].name = PSTR(#functionName);\
        \
    Sharer.functionList.functions[Sharer.functionList.count].Arguments = functionName ## _args;\
        \
    Sharer.functionList.functions[Sharer.functionList.count].argumentCount = _SHARER_PP_NARG(__VA_ARGS__) / 2;\
        \
    Sharer.functionList.functions[Sharer.functionList.count].returnValue.type = 	SharerClass::_SharerFunctionArgType::TypeVoid;\
    Sharer.functionList.functions[Sharer.functionList.count].returnValue.pointer = 0;\
\
    Sharer.functionList.functions[Sharer.functionList.count].pointer = []() {\
        functionName (_SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_CALL10, _SHARER_DECLARE_CALL9_, _SHARER_DECLARE_CALL9,  _SHARER_DECLARE_CALL8_, _SHARER_DECLARE_CALL8,  _SHARER_DECLARE_CALL7_, _SHARER_DECLARE_CALL7,  _SHARER_DECLARE_CALL6_, _SHARER_DECLARE_CALL6,  _SHARER_DECLARE_CALL5_, _SHARER_DECLARE_CALL5,  _SHARER_DECLARE_CALL4_, _SHARER_DECLARE_CALL4,  _SHARER_DECLARE_CALL3_, _SHARER_DECLARE_CALL3,  _SHARER_DECLARE_CALL2_, _SHARER_DECLARE_CALL2, _SHARER_DECLARE_CALL1_, _SHARER_DECLARE_CALL1, _SHARER_DECLARE_CALL0)(functionName, __VA_ARGS__) );\
    };\
        \
    Sharer.functionList.count++;\
\
}


#define Sharer_ShareVariable(variableType, variable) \
if (Sharer.variableList.count < _SHARER_MAX_VARIABLE_COUNT) {\
	Sharer.variableList.variables[Sharer.variableList.count].name = PSTR(#variable);\
	Sharer.variableList.variables[Sharer.variableList.count].value.pointer = (void*)& variable;\
	Sharer.variableList.variables[Sharer.variableList.count].value.type = SharerClass::_SharerFunctionArgType::Type ## variableType;\
	Sharer.variableList.count++;\
} \

#define _SHARER_ENUM_COMMAND				\
					None = 0x00,			\
					FunctionCount,			\
					FunctionPrototype,		\
					AllFunctionsPrototype,	\
					CallFunction,			\
					AllVariables,			\
					ReadVariables,			\
					WriteVariables,			\
					GetInfos,				\


class SharerClass : public Stream
{
public :
// Supported types
	enum class _SharerFunctionArgType : byte {
		TypeVoid = 0,
		Typebool = 1,
		Typeint8_t = 2,
		Typeuint8_t = 3,
		Typeint16_t = 4,
		Typeuint16_t = 5,
		Typeint32_t = 6,
		Typeuint32_t = 7,
		Typeint64_t = 8,
		Typeuint64_t = 9,
		Typefloat = 10,
		Typedouble = 11,
		
		Typebyte = Typeint8_t,
		Typeint = Typeint16_t,
		Typesigned = Typeint16_t,
		Typelong = Typeint32_t,
		Typeshort = Typeint8_t,
		Typechar = Typeuint8_t,
		Typeword = Typeuint16_t,
		Typeboolean = Typebool,
	};

// Types for function sharing
	typedef void(*_sharer_void_ptr)(void);

	typedef struct {
		_SharerFunctionArgType type;
		void* pointer;
	} _SharerPointerValue;

	typedef struct {
		char* name;
		_SharerPointerValue value;
	} _SharerFunctionArgument;

	typedef struct {
		const char* name;
		_sharer_void_ptr pointer;
		_SharerPointerValue returnValue;
		byte argumentCount;
		const _SharerFunctionArgument* Arguments;
	} _SharerFunction;


	typedef struct {
		int16_t count;
		_SharerFunction functions[_SHARER_MAX_FUNCTION_COUNT];
	} _SharerFunctionList;


// Types for variable sharing
	typedef struct {
		const char* name;
		_SharerPointerValue value;
	} _SharerVariable;

	typedef struct {
		int16_t count;
		_SharerVariable variables[_SHARER_MAX_VARIABLE_COUNT];
	}_SharerVariableList;


protected:
	enum class _SharerReceiveState {
		Free,
		MessageID,
		Commande,
		ComplexCommandeBody
	};

	enum class _SharerReceivedCommand : byte {
		_SHARER_ENUM_COMMAND
	};

	enum class _SharerSentCommand : byte {
		_SHARER_ENUM_COMMAND

		Error = 0x80,
	};

	enum class _SharerCallFunctionStatus {
		OK,
		FunctionIdOutOfRange,
		UnknownType,
	};

	enum class _SharerReadVariableStatus {
		OK,
		VariableIdOutOfRange,
		UnknownType,
	};

	void init();

	byte _receiveBuffer[_SHARER_USER_RECEIVE_BUFFER_SIZE];

	void _storeNewValue(byte value);

	byte _lastReceivedCommandId = 0;
	_SharerReceivedCommand _lastReceivedCommand = _SharerReceivedCommand::None;

	byte _lastSentCommandId = 0;

	void _sendHeader(_SharerSentCommand cmd);

	// Send default header that corresponds to the current command
	inline void _sendHeader() {
		_sendHeader((_SharerSentCommand)_lastReceivedCommand);
	}

	_SharerReceiveState _receiveState = _SharerReceiveState::Free;

	inline void _endSend() { _receiveState = _SharerReceiveState::Free; }

	void _rollBackCommand();

	void _handleSimpleCommand();

	void _printp(const char *data);

	int16_t _sizeof(_SharerFunctionArgType type);

	// write the description of the idth function in the list
	void _printFunctionPrototype(int16_t id);

	void _printFunctionsPrototype();

	void _printInfos();

	void _printVariablesDefinition();

	int16_t _complexCommandStep;

	void _callFunctionAndAnswer(_SharerFunction* fnc);

	void _handleComplexCommand(byte receiveByte);

	Stream* _parentStream = &Serial;

	bool _initDone = false;

	int _userMessageHead = 0;
	int _userMessageTail = 0;

	inline int _getNextHeadIndex() {
		int next = _userMessageHead + 1; 
		if (next >= _SHARER_USER_RECEIVE_BUFFER_SIZE) next = 0;

		// if full
		if (next == _userMessageTail) return -1;
		else return next;
	}

public:
	SharerClass() { }

	_SharerFunctionList functionList;
	_SharerVariableList variableList;

	void init(Stream*);
	void init(unsigned long baud);

	void run();

	inline bool Full() { return _getNextHeadIndex() < 0; };

	int available();
	int read();
	int peek();
	void flush();
	size_t write(uint8_t);
};

// Sharer global instance defined in .cpp
extern SharerClass Sharer;

#endif

