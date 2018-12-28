
#define _SHARER_MAX_FUNCTION_COUNT 15
#include <Sharer.h>



int myFunc(int a, float b) {

	float B = b;

	Serial.write(*(byte*)&B);
	Serial.write(*(byte*)(&B + 1));
	Serial.write(*(byte*)(&B + 2));
	Serial.write(*(byte*)(&B + 3));


	Serial.print("myFunc - ");
	Serial.print(a);
	Serial.print(" ");
	Serial.print(b, 10);
	Serial.println();

	return a + b + 1;
}



float myFunc2(int c) {
	Serial.print("myFunc2");
	return (float)(c * 10 + 1);
}

int myFunc3(int a, int b) {
	Serial.print("myFunc3 - ");
	Serial.print(a);
	Serial.print(" ");
	Serial.print(b);
	Serial.println();

	return a + b + 1;
}
void testVoid(int a) {

	Serial.print("testVoid - ");
	Serial.println(a);

}

void pureVoid() {
	Serial.print("pureVoid");
}

int notArgs() {
	Serial.print("notArgs");

}


int a;

void setup()
{
	Serial.begin(115200);


	/*
	if (functionList.count < MAX_FUNCTION_COUNT) {
	static int myFunc_arg_a;
	static float myFunc_arg_b;
	static int myFunc_ret;

	static const FunctionArgument myFunc_args[] PROGMEM = { { "a", Typeint, &myFunc_arg_a }, {"b", Typefloat, &myFunc_arg_b }, };

	functionList.functions[functionList.count].name = PSTR("myFunc");

	functionList.functions[functionList.count].Arguments = myFunc_args;

	functionList.functions[functionList.count].argumentCount = 2;

	functionList.functions[functionList.count].returnValue.type = Typeint;
	functionList.functions[functionList.count].returnValue.pointer = &myFunc_ret;

	functionList.functions[functionList.count].pointer = []() {
	myFunc_ret = myFunc(myFunc_arg_a, myFunc_arg_b);
	};

	functionList.count++;

	}

	*/
	/*

	static const char* pureVoid_name = "pureVoid"; \
	static const  SharerClass::_SharerFunctionArgument _ pureVoid_args[] = {

	};

	Sharer.functionList.functions[Sharer.functionList.count].name = pureVoid_name;

	Sharer.functionList.functions[Sharer.functionList.count].Arguments = pureVoid_args;

	Sharer.functionList.functions[Sharer.functionList.count].argumentCount = 1 / 2;

	Sharer.functionList.functions[Sharer.functionList.count].returnValue.pointer = 0;

	Sharer.functionList.functions[Sharer.functionList.count].pointer = []() {
	pureVoid();
	};

	Sharer.functionList.count++;
	*/


	Sharer_ShareFunction(int, myFunc, int, a, float, b);



	Sharer_ShareFunction(float, myFunc2, int, c);

	Sharer_ShareVoid(testVoid, int, a);

	Sharer_ShareVoid(testVoid, int, a);


	Sharer_ShareFunction(int, myFunc3, int, a, int, b);


	Sharer_ShareFunction(int, notArgs);


	Sharer_ShareVoid(pureVoid);



	if (Sharer.variableList.count < _SHARER_MAX_VARIABLE_COUNT) {
		Sharer.variableList.variables[Sharer.variableList.count].name = PSTR("a");
		Sharer.variableList.variables[Sharer.variableList.count].value.type = SharerClass::_SharerFunctionArgType::Typeint;
		Sharer.variableList.variables[Sharer.variableList.count].value.pointer = &a;
		Sharer.variableList.count++;
	}

}


int cnt = 0;


void loop()
{

	Sharer.run();

	/*
	delay(1000);

	cnt++;

	*(int*)Sharer.functionList.functions[0].Arguments[0].value.pointer = cnt;
	*(float*)Sharer.functionList.functions[0].Arguments[1].value.pointer = 10.5;

	(*Sharer.functionList.functions[0].pointer)();


	Serial.print("Ret:");
	Serial.println(*(int*)Sharer.functionList.functions[0].returnValue.pointer);

	*(int*)Sharer.functionList.functions[1].Arguments[0].value.pointer = cnt;


	(*Sharer.functionList.functions[1].pointer)();

	Serial.println(*(float*)Sharer.functionList.functions[1].returnValue.pointer);


	*(int*)Sharer.functionList.functions[2].Arguments[0].value.pointer = cnt;
	(*Sharer.functionList.functions[2].pointer)();

	*/

}
