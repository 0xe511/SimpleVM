#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string>
#include <cstdint>
#include <bitset>
#include <utility> 
#include <fstream>
#include <sstream>
#include <cstdio>
#include "UnrealVM.hpp"
#include "VMSAssembler.hpp"


#define MP(X,A) std::make_pair(X,A)


int main()
{
	
	KeyWordsMapNumbers KeyWords[] = { 
										MP("Label",0b00101110),MP("GoTo",0b00000100),MP("DefVar",0b00100100),MP("MovRegVarAdr",0b00000001),
										MP("InitVarByVal",0b00000010),MP("InitByAdr",0b00000011)
									};
	KeyWordsMapNumbers RegNumbers[] = { 
										MP("RIP",0),MP("RSP",1),MP("FLZ",2),MP("FLP",3),
										MP("FLN",4),MP("RG1",5),MP("RG2",6),MP("RG3",7),
										MP("RG4",8),MP("RG5",9),MP("RG6",10),MP("RG7",11),
										MP("RG8",12),MP("RG9",13),MP("RS1",14),MP("RS2",15)
									};
	VMSAssembler VM1Assembler(KeyWords, RegNumbers, sizeof(KeyWords) / sizeof(KeyWords[0]), sizeof(RegNumbers) / sizeof(RegNumbers[0]),"VMBuffer");
	VM1Assembler.GenerateOPCodes("VM1In.txt", "VM1Out.txt");
	OpCodes VMBuffer[5] = { 0 };
	VMBuffer[0].Operand = 0b00101110; VMBuffer[0].Arg_1 = 18; VMBuffer[0].CharsHolder.push_back(0b00101110); VMBuffer[0].CharsHolder.push_back(0b01001111); VMBuffer[0].CharsHolder.push_back(0b01110010); VMBuffer[0].CharsHolder.push_back(0b01101001); VMBuffer[0].CharsHolder.push_back(0b01100111); VMBuffer[0].CharsHolder.push_back(0b01101001); VMBuffer[0].CharsHolder.push_back(0b01101110); VMBuffer[0].CharsHolder.push_back(0b01011111); VMBuffer[0].CharsHolder.push_back(0b01001111); VMBuffer[0].CharsHolder.push_back(0b01100110); VMBuffer[0].CharsHolder.push_back(0b01011111); VMBuffer[0].CharsHolder.push_back(0b01010000); VMBuffer[0].CharsHolder.push_back(0b01110010); VMBuffer[0].CharsHolder.push_back(0b01101111); VMBuffer[0].CharsHolder.push_back(0b01100111); VMBuffer[0].CharsHolder.push_back(0b01110010); VMBuffer[0].CharsHolder.push_back(0b01100001); VMBuffer[0].CharsHolder.push_back(0b01101101);
	VMBuffer[1].Operand = 0b00100100; VMBuffer[1].Arg_2 = 1; VMBuffer[1].Arg_1 = 9; VMBuffer[1].CharsHolder.push_back(0b00100100); VMBuffer[1].CharsHolder.push_back(0b01000111); VMBuffer[1].CharsHolder.push_back(0b01101111); VMBuffer[1].CharsHolder.push_back(0b01101111); VMBuffer[1].CharsHolder.push_back(0b01100100); VMBuffer[1].CharsHolder.push_back(0b01011111); VMBuffer[1].CharsHolder.push_back(0b01010110); VMBuffer[1].CharsHolder.push_back(0b01100001); VMBuffer[1].CharsHolder.push_back(0b01110010);
	VMBuffer[2].Operand = 0b00000001; VMBuffer[2].Arg_2 = 5; VMBuffer[2].Arg_1 = 9; VMBuffer[2].CharsHolder.push_back(0b00100100); VMBuffer[2].CharsHolder.push_back(0b01000111); VMBuffer[2].CharsHolder.push_back(0b01101111); VMBuffer[2].CharsHolder.push_back(0b01101111); VMBuffer[2].CharsHolder.push_back(0b01100100); VMBuffer[2].CharsHolder.push_back(0b01011111); VMBuffer[2].CharsHolder.push_back(0b01010110); VMBuffer[2].CharsHolder.push_back(0b01100001); VMBuffer[2].CharsHolder.push_back(0b01110010);
	VMBuffer[3].Operand = 0b00000010; VMBuffer[3].Arg_1 = 9; VMBuffer[3].Arg_2 = 15; VMBuffer[3].CharsHolder.push_back(0b00100100); VMBuffer[3].CharsHolder.push_back(0b01000111); VMBuffer[3].CharsHolder.push_back(0b01101111); VMBuffer[3].CharsHolder.push_back(0b01101111); VMBuffer[3].CharsHolder.push_back(0b01100100); VMBuffer[3].CharsHolder.push_back(0b01011111); VMBuffer[3].CharsHolder.push_back(0b01010110); VMBuffer[3].CharsHolder.push_back(0b01100001); VMBuffer[3].CharsHolder.push_back(0b01110010);
	VMBuffer[4].Operand = 0b00000100; VMBuffer[4].Arg_1 = 18; VMBuffer[4].CharsHolder.push_back(0b00101110); VMBuffer[4].CharsHolder.push_back(0b01001111); VMBuffer[4].CharsHolder.push_back(0b01110010); VMBuffer[4].CharsHolder.push_back(0b01101001); VMBuffer[4].CharsHolder.push_back(0b01100111); VMBuffer[4].CharsHolder.push_back(0b01101001); VMBuffer[4].CharsHolder.push_back(0b01101110); VMBuffer[4].CharsHolder.push_back(0b01011111); VMBuffer[4].CharsHolder.push_back(0b01001111); VMBuffer[4].CharsHolder.push_back(0b01100110); VMBuffer[4].CharsHolder.push_back(0b01011111); VMBuffer[4].CharsHolder.push_back(0b01010000); VMBuffer[4].CharsHolder.push_back(0b01110010); VMBuffer[4].CharsHolder.push_back(0b01101111); VMBuffer[4].CharsHolder.push_back(0b01100111); VMBuffer[4].CharsHolder.push_back(0b01110010); VMBuffer[4].CharsHolder.push_back(0b01100001); VMBuffer[4].CharsHolder.push_back(0b01101101);
	SimpleVM SV(VMBuffer, sizeof(VMBuffer) / sizeof(VMBuffer[0]), 10, 10);
	SV.VMON();

	return 0;
}
