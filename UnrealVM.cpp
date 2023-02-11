#include "UnrealVM.hpp"


SimpleVM::SimpleVM(OpCodes* OpCodesBuffer, unsigned long int OpCodesBufferSize, const unsigned int StackSize, const unsigned int VMMemSize)
{
	VMMemorySize = VMMemSize;
	memset(RegVal, 0, sizeof(RegVal));
	DefinedVarsCounter = 0;
	VMMem = new long long int[VMMemSize];
	VMStack = new OpCodes[StackSize];
	BufferSize = OpCodesBufferSize;
	VMOpcodesBuffer = new OpCodes[BufferSize];
	for (unsigned long int i = 0; i < BufferSize; i++)
	{
		VMOpcodesBuffer[i] = OpCodesBuffer[i];
	}
	RegMap[Regs(0)] = "RIP"; RegMap[Regs(1)] = "RSP"; RegMap[Regs(2)] = "FLZ"; RegMap[Regs(3)] = "FLP";
	RegMap[Regs(4)] = "FLN"; RegMap[Regs(5)] = "RG1"; RegMap[Regs(6)] = "RG2"; RegMap[Regs(7)] = "RG3";
	RegMap[Regs(8)] = "RG4"; RegMap[Regs(9)] = "RG5"; RegMap[Regs(10)] = "RG6"; RegMap[Regs(11)] = "RG7";
	RegMap[Regs(12)] = "RG8"; RegMap[Regs(13)] = "RG9"; RegMap[Regs(14)] = "RS1"; RegMap[Regs(15)] = "RS2";
}

SimpleVM::~SimpleVM()
{
	delete[] VMMem;
	delete[] VMStack;
}

int SimpleVM::Label(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	std::string Token;
	for (unsigned int i = 0; i < ByteCode.Arg_1; i++)
		Token.push_back(ByteCode.CharsHolder[i]);
	LabelMap[Token] = &VMOpcodesBuffer[RegVal[RIP]];
	std::cout << "[+] Label instruction Executed." << std::endl;
	return VMExecutionLasterror;
}

int SimpleVM::GoTo(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	std::string Token;
	for (unsigned int i = 0; i < ByteCode.Arg_1; i++)
		Token.push_back(ByteCode.CharsHolder[i]);
	if ((long long int)VMOpcodesBuffer <= (long long int) LabelMap[Token] && (long long int)LabelMap[Token] <= (long long int)VMOpcodesBuffer + sizeof(OpCodes) * sizeof(*VMOpcodesBuffer) / sizeof(VMOpcodesBuffer[0]))
		RegVal[RIP] = ((long long int) LabelMap[Token] - (long long int)VMOpcodesBuffer) / sizeof(OpCodes) - 1; // -1 is because of loop
	else return VMInsRead_InvalidArg;
	std::cout << "[+] GoTo instruction Executed." << std::endl;
	return VMExecutionLasterror;

}

int SimpleVM::DefVar(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	std::string Token;
	for (unsigned int i = 0; i < ByteCode.Arg_1; i++)
		Token.push_back(ByteCode.CharsHolder[i]);
	if (VarMap.find(Token) != VarMap.end())
	{
		std::cout << "[-] Variable defined before!" << std::endl;
		return Variable_Defined_Before;
	}

	if (ByteCode.Arg_2 == 1)
	{
		if (VMMemorySize - 1 < DefinedVarsCounter)
		{
			VMExecutionLasterror = VMMemory_Not_Enough;
			std::cout << "[-] VM memory is not enough to define variable!" << std::endl;
			return VMExecutionLasterror;
		}
		VMMem[DefinedVarsCounter] = 0;
		VarMap[Token] = &VMMem[DefinedVarsCounter];
		DefinedVarsCounter++;
	}
	else if (ByteCode.Arg_2 > 1)
	{
		if (VMMemorySize < DefinedVarsCounter + ByteCode.Arg_2)
		{
			VMExecutionLasterror = VMMemory_Not_Enough;
			std::cout << "[-] VM memory is not enough to define variable!" << std::endl;
			return VMExecutionLasterror;
		}
		VarMap[Token] = &VMMem[DefinedVarsCounter];
		for (unsigned long int t = 0; t < ByteCode.Arg_2; t++)
		{
			VMMem[DefinedVarsCounter] = 0;
			DefinedVarsCounter++;
		}
	}
	else
	{
		VMExecutionLasterror = Variable_Size_Undefined;
		std::cout << "[-] Undefined Variable size in DefVar instruction!" << std::endl;
		return VMExecutionLasterror;
	}
	std::cout << "[+] DefVar instruction Executed." << std::endl;
	return VMExecutionLasterror;
}



int SimpleVM::MovRegVarAdr(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	std::string Token;
	for (unsigned int i = 0; i < ByteCode.Arg_1; i++)
		Token.push_back(ByteCode.CharsHolder[i]);
	if (0 <= ByteCode.Arg_2 && ByteCode.Arg_2 <= NumberOfRegister)
	{
		RegVal[ByteCode.Arg_1] = (long long int)VarMap[Token];
	}
	else
	{
		std::cout << "[+] MovRegVarAdr instruction failed!" << std::endl;
		return MovRegVarAdr_Fail;
	}
	std::cout << "[+] MovRegVarAdr instruction Executed." << std::endl;
	return VMExecutionLasterror;
}


int SimpleVM::InitVarByVal(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	std::string Token;
	for (unsigned int i = 0; i < ByteCode.Arg_1; i++)
		Token.push_back(ByteCode.CharsHolder[i]);
	if (VarMap.find(Token) == VarMap.end())
	{
		std::cout << "[-] Variable is not defined!" << std::endl;
		return InitVarByVal_Fail;
	}
	*VarMap[Token] = ByteCode.Arg_2;
	std::cout << "[+] InitVar instruction Executed." << std::endl;
	return VMExecutionLasterror;
}

int SimpleVM::InitByAdr(OpCodes ByteCode)
{
	int VMExecutionLasterror = VMInsRead_SUCCESS;
	if ((unsigned long long int)VMMem <= ByteCode.Arg_1 && ByteCode.Arg_1 <= (unsigned long long int)VMMem + sizeof(long long int) * sizeof(VMMem) / sizeof(VMMem[0]))
	{
		*(long long int*)ByteCode.Arg_1 = RegVal[ByteCode.Arg_2];
	}
	else
	{
		std::cout << "[+] InitByAdr instruction failed, address is out of boudn!" << std::endl;
		return InitByAdr_Fail;
	}
	std::cout << "[+] InitByAdr instruction Executed." << std::endl;
	return VMExecutionLasterror;
}


int SimpleVM::Execute(OpCodes ByteCode)
{
	int VMExecutionLasterror = SUCCESS;

	if (!(ByteCode.Operand ^ 0b00101110))
	{
		VMExecutionLasterror = Label(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}


	if (!(ByteCode.Operand ^ 0b00000100))
	{
		VMExecutionLasterror = GoTo(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}
	if (!(ByteCode.Operand ^ 0b00100100))
	{
		VMExecutionLasterror = DefVar(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}

	if (!(ByteCode.Operand ^ 0b00000001))
	{
		VMExecutionLasterror = MovRegVarAdr(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}

	if (!(ByteCode.Operand ^ 0b00000010))
	{
		VMExecutionLasterror = InitVarByVal(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}
	if (!(ByteCode.Operand ^ 0b00000011))
	{
		VMExecutionLasterror = InitByAdr(ByteCode);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
			return VMExecutionLasterror;
	}


	return VMExecutionLasterror;
}

int SimpleVM::VMON()
{
	int VMExecutionLasterror = SUCCESS;
	RegVal[RIP] = 0;
	for (RegVal[RIP]; RegVal[RIP] < BufferSize; RegVal[RIP]++)
	{
		VMExecutionLasterror = Execute(VMOpcodesBuffer[RegVal[RIP]]);
		if (!(VMExecutionLasterror != SUCCESS) || (VMExecutionLasterror != VMInsRead_SUCCESS))
		{
			std::cout << "[-] VM stopped execution with last code: " << VMExecutionLasterror << std::endl;
			return VMExecutionLasterror;
		}
	}
	std::cout << "[+] VM executed all the instructions successfully." << VMExecutionLasterror << std::endl;
	return VMExecutionLasterror;
}