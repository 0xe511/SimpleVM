#include "VMSAssembler.hpp"


VMSAssembler::VMSAssembler(KeyWordsMapNumbers* KWOPS, KeyWordsMapNumbers* RNM, unsigned int NOKOPS, unsigned int NORegs, std::string BufferVarName)
{
	KeyWordsOPCodes = KWOPS;
	RegistersNmbers = RNM;
	NumberOfKeyWords = NOKOPS;
	NumberOfRegisters = NORegs;
	BufferName = BufferVarName;

}

VMSAssembler::~VMSAssembler()
{

}


std::string VMSAssembler::ParseSingleInstruction(std::string Token, unsigned long int OpCodeIndex)
{
	std::string OPCode;
	std::vector<std::string> Words;
	unsigned int Pos = 0;
	for (unsigned int i = 0; i <= Token.length(); i++)
	{
		if (isspace(Token[i]) || Token[i] == '\0')
		{
			Words.push_back(Token.substr(Pos, i - Pos));
			Pos = i + 1;
		}
	}


	//Find operator opcode
	for (unsigned int j = 0; j < NumberOfKeyWords; j++)
	{
		if (Words[0] == KeyWordsOPCodes[j].first)
		{
			std::string s = std::bitset<8>(KeyWordsOPCodes[j].second).to_string();
			OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Operand = 0b");
			OPCode.append(s);
			OPCode.append(";");
			j = NumberOfKeyWords;
		}


	}


	if (Words[0] == "Label" || Words[0] == "GoTo")
	{
		for (unsigned int i = 1; i < Words.size(); i++)
		{
			OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_1 =" + std::to_string(Words[i].size()) + ";");
			for (unsigned t = 0; t < Words[i].size(); t++)
			{
				OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].CharsHolder.push_back(0b");
				std::string s = std::bitset<8>(Words[i][t]).to_string();
				OPCode.append(s);
				OPCode.append(");");
			}
		}
	}

	if (Words[0] == "DefVar")
	{
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_2 =" + Words[1] + ";");
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_1 =" + std::to_string(Words[2].size()) + ";");
		for (unsigned t = 0; t < Words[2].size(); t++)
		{
			OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].CharsHolder.push_back(0b");
			std::string s = std::bitset<8>(Words[2][t]).to_string();
			OPCode.append(s);
			OPCode.append(");");
		}
	}

	if (Words[0] == "MovRegVarAdr")
	{
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_2 =" + Words[1] + ";");
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_1 =" + std::to_string(Words[2].size()) + ";");
		for (unsigned t = 0; t < Words[2].size(); t++)
		{
			OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].CharsHolder.push_back(0b");
			std::string s = std::bitset<8>(Words[2][t]).to_string();
			OPCode.append(s);
			OPCode.append(");");
		}
	}

	if (Words[0] == "InitVarByVal")
	{
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_1 =" + std::to_string(Words[1].size()) + ";");
		OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].Arg_2 =" + Words[2] + ";");
		for (unsigned t = 0; t < Words[1].size(); t++)
		{
			OPCode.append(BufferName + "[" + std::to_string(OpCodeIndex) + "].CharsHolder.push_back(0b");
			std::string s = std::bitset<8>(Words[1][t]).to_string();
			OPCode.append(s);
			OPCode.append(");");
		}
	}

	return OPCode;

}


void VMSAssembler::GenerateOPCodes(const char* InputFile, const char* OutPutFile)
{
	std::string line, token;
	std::ifstream input_file(InputFile, std::ios::in);
	std::ofstream output_file(OutPutFile, std::ios::out);
	unsigned long int Counter = 0;
	while (std::getline(input_file, line))
	{
		output_file << ParseSingleInstruction(line, Counter) << std::endl;
		Counter++;
	}
	input_file.close();
	output_file.close();
}