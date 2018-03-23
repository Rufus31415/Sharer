// Sharer.h

#ifndef _SHARER_h
#define _SHARER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define _SHARER_MAX_FUNCTION_COUNT	10

#define _SHARER_USER_RECEIVE_BUFFER_SIZE	20

#define _SHARER_START_COMMAND_CHAR	0x92

// maximum numbre of call to Serial read() each time Sharer.Run() is called
#define _SHARER_MAX_BYTE_READ_PER_RUN	20



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



#define _SHARER_GET_OVERRIDE(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

#define _SHARER_DECLARE_STATIC_BASE(functionName, argumentType, argumentName) static argumentType functionName ## _arg_ ## argumentName;

#define _SHARER_DECLARE_STATIC3(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC2(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC2(f, t, n, ...)   _SHARER_DECLARE_STATIC_BASE(f, t, n) _SHARER_DECLARE_STATIC1(f, __VA_ARGS__)
#define _SHARER_DECLARE_STATIC1(f, t, n)        _SHARER_DECLARE_STATIC_BASE(f, t, n)
#define _SHARER_DECLARE_STATIC0(...)   

#define _SHARER_DECLARE_STATIC(f, ...) _SHARER__GET_OVERRIDE(__VA_ARGS__, \
        _SHARER_DECLARE_STATIC3, _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(f, __VA_ARGS__);


#define _SHARER_DECLARE_ARG_BASE(functionName, argumentType, argumentName) { PSTR(#argumentName), SharerClass::_SharerFunctionArgType::Type ## argumentType, & functionName ## _arg_ ## argumentName },

#define _SHARER_DECLARE_ARG3(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG2(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG2(f, t, n, ...)   _SHARER_DECLARE_ARG_BASE(f, t, n) _SHARER_DECLARE_ARG1(f, __VA_ARGS__)
#define _SHARER_DECLARE_ARG1(f, t, n)        _SHARER_DECLARE_ARG_BASE(f, t, n)
#define _SHARER_DECLARE_ARG0(...)  



#define _SHARER_DECLARE_CALL_BASE(functionName, argumentType, argumentName) functionName ## _arg_ ## argumentName

#define _SHARER_DECLARE_CALL3(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL2(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL2(f, t, n, ...)   _SHARER_DECLARE_CALL_BASE(f, t, n), _SHARER_DECLARE_CALL1(f, __VA_ARGS__)
#define _SHARER_DECLARE_CALL1(f, t, n)        _SHARER_DECLARE_CALL_BASE(f, t, n)
#define _SHARER_DECLARE_CALL0(...)



#define Sharer_ShareFunction(returnType, functionName, ...)    \
if (Sharer.functionList.count < _SHARER_MAX_FUNCTION_COUNT) {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_STATIC3, _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(functionName, __VA_ARGS__);\
    static returnType functionName ## _ret;\
    static const SharerClass::_SharerFunctionArgument functionName ## _args[] = {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_ARG3, _SHARER_DECLARE_ARG2_, _SHARER_DECLARE_ARG2, _SHARER_DECLARE_ARG1_, _SHARER_DECLARE_ARG1, _SHARER_DECLARE_ARG0)(functionName, __VA_ARGS__)\
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
        functionName ## _ret = functionName (_SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_CALL3, _SHARER_DECLARE_CALL2_, _SHARER_DECLARE_CALL2, _SHARER_DECLARE_CALL1_, _SHARER_DECLARE_CALL1, _SHARER_DECLARE_CALL0)(functionName, __VA_ARGS__) );\
    };\
        \
    Sharer.functionList.count++;\
\
}

#define Sharer_ShareVoid(functionName, ...)    \
if (Sharer.functionList.count < _SHARER_MAX_FUNCTION_COUNT) {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_STATIC3, _SHARER_DECLARE_STATIC2_, _SHARER_DECLARE_STATIC2, _SHARER_DECLARE_STATIC1_, _SHARER_DECLARE_STATIC1, _SHARER_DECLARE_STATIC0)(functionName, __VA_ARGS__);\
    static const SharerClass::_SharerFunctionArgument functionName ## _args[] = {\
    _SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_ARG3, _SHARER_DECLARE_ARG2_, _SHARER_DECLARE_ARG2, _SHARER_DECLARE_ARG1_, _SHARER_DECLARE_ARG1, _SHARER_DECLARE_ARG0)(functionName, __VA_ARGS__)\
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
        functionName (_SHARER_GET_OVERRIDE(__VA_ARGS__, _SHARER_DECLARE_CALL3, _SHARER_DECLARE_CALL2_, _SHARER_DECLARE_CALL2, _SHARER_DECLARE_CALL1_, _SHARER_DECLARE_CALL1, _SHARER_DECLARE_CALL0)(functionName, __VA_ARGS__) );\
    };\
        \
    Sharer.functionList.count++;\
\
}


#define _SHARER_ENUM_COMMAND			\
					None = 0x00,			\
					FunctionCount,			\
					FunctionPrototype,		\
					AllFunctionsPrototype,	\
					CallFunction,			\
					ReadVariable,			\
					WriteVariable,			\
					SubscribeVariable,		\
					UnsubscribeVariable,		\


class SharerClass : public Stream
{
public :
	enum class _SharerFunctionArgType : byte {
		TypeVoid,
		Typeint,
		Typefloat,
	};

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
		int count;
		_SharerFunction functions[_SHARER_MAX_FUNCTION_COUNT];
	} _SharerFunctionList;

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
		SubscriptionValues,
	};

	enum class _SharerCallFunctionStatus {
		OK,
		FunctionIdOutOfRange,
		UnknownType,
	};

	void init();

	byte _receiveBuffer[_SHARER_USER_RECEIVE_BUFFER_SIZE];
	int _available = 0;
	int _receiveIndex = 0;

	void _storeNewValue(byte value);

	byte _lastReceivedCommandId = 0;
	_SharerReceivedCommand _lastReceivedCommand = _SharerReceivedCommand::None;

	byte _lastSentCommandId = 0;

	void _sendHeader(_SharerSentCommand cmd);

	// Send default header that corresponds to the current command
	inline void _sendHeader() {
		_sendHeader((_SharerSentCommand)_lastReceivedCommand);
	}

	void _endSend();

	void _rollBackCommand();

	void _handleSimpleCommand();

	void _printp(const char *data);

	int _sizeof(_SharerFunctionArgType type);

	// write the description of the idth function in the list
	void _printFunctionPrototype(int id);

	int _complexCommandStep;

	void _callFunctionAndAnswer(_SharerFunction* fnc);

	void _handleComplexCommand(byte receiveByte);

	inline int _receiveNextIndex() {
		if (_receiveIndex < _SHARER_USER_RECEIVE_BUFFER_SIZE - 1) return _receiveIndex + 1;
		else return 0;
	};

	_SharerReceiveState _receiveState = _SharerReceiveState::Free;

	Stream* _parentStream = &Serial;

public:

	SharerClass() { }

	_SharerFunctionList functionList;

	void init(Stream*);
	void init(unsigned long baud);

	void run();


	inline bool Full() { return _available >= _SHARER_USER_RECEIVE_BUFFER_SIZE; };

	int available();
	int read();
	int peek();
	void flush();
	size_t write(uint8_t);
};

extern SharerClass Sharer;

#endif

