#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <map>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <bitset>

using KeyWordsMapNumbers = std::pair<std::string, unsigned int>;

class VMSAssembler {
public:
	//public data

	//public functions
	VMSAssembler(KeyWordsMapNumbers *KWOPS,KeyWordsMapNumbers *RNM,unsigned int NOKOPS, unsigned int NORegs,std::string BufferVarName);
	~VMSAssembler();
	std::string ParseSingleInstruction(std::string Token, unsigned long int OpCodeIndex);
	void GenerateOPCodes(const char* InputFile, const char* OutPutFile);
private:
	//private data
	KeyWordsMapNumbers* KeyWordsOPCodes;
	KeyWordsMapNumbers* RegistersNmbers;
	unsigned int NumberOfKeyWords = 0;
	unsigned int NumberOfRegisters = 0;
	std::string BufferName;
	//private functions	
};