#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <bitset>
#include <random>
#include <map>





struct OpCodes {
	unsigned int Operand = 0;
	unsigned long long int Arg_1 = 0;
	unsigned long long int Arg_2 = 0;
	std::vector <unsigned char> CharsHolder;
};
enum VMExecutionCodes
{
	SUCCESS,
	VMMemSizeErr,
	VMInsExecution_SUCCESS,
	VMInsExecution_Fail,
	VMInsRead_Fail,
	VMInsRead_SUCCESS,
	VMInsRead_InvalidArg,
	VMMemory_Not_Enough,
	Variable_Size_Undefined,
	Variable_Defined_Before,
	GetVarAdr_Inavlid_Argument,
	MovRegVarAdr_Fail,
	InitVarByVal_Fail,
	InitByAdr_Fail

};
constexpr unsigned int NumberOfRegister = 16;
constexpr unsigned int NumberOfOpCodes = 6;
class SimpleVM {
public:
	SimpleVM(OpCodes* OpCodesBuffer,unsigned long int OpCodesBufferSize,const unsigned int StackSize, const unsigned int VMMemSize);
	~SimpleVM();
	int VMON();

private:
	enum Regs {
		RIP,
		RSP,
		FLZ,
		FLP,
		FLN,
		RG1,
		RG2,
		RG3,
		RG4,
		RG5,
		RG6,
		RG7,
		RG8,
		RG9,
		RS1,
		RS2
	};
	std::map <Regs, std::string> RegMap;
	std::map <std::string, OpCodes*> LabelMap;
	std::map <std::string, long long int*> VarMap;
	long long int RegVal[NumberOfRegister] = { 0 };
	unsigned long int VMMemorySize = 0;
	unsigned int VMStackSize = 0;
	unsigned long int BufferSize;
	unsigned long int DefinedVarsCounter = 0;
	long long int* VMMem = NULL;
	OpCodes* VMStack = NULL;
	OpCodes* VMOpcodesBuffer = NULL;
	//Private functions
	int Execute(OpCodes ByteCode);
	//----------------------------------------VM Instructions-------------------------------------------
	int Label(OpCodes ByteCode);
	int GoTo(OpCodes ByteCode);
	int DefVar(OpCodes ByteCode);
	int MovRegVarAdr(OpCodes ByteCode);
	int InitVarByVal(OpCodes ByteCode);
	int InitByAdr(OpCodes ByteCode);
	//----------------------------------------End Of VM Instructions------------------------------------

};

//-------------------------------SimpeVM instructions manual
// Label .labelname (Label name lenght in Arg_1)
// GoTo .labelname (Label name lenght in Arg_1)
//DefVar 0xNumberOfVaribles(Arg_1) 0xLenghtOfVariableeName(Arg_2) Varname in vector