#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <fstream>
std::unordered_map<size_t, size_t> find_loops(const std::string& code)
{
	std::unordered_map<size_t, size_t> loops;
	std::stack<size_t> left_brackets;
	size_t i = 0;
	for (; i < code.size(); i++)
	{
		if (code[i] == '[') left_brackets.push(i);
		if (code[i] == ']')
		{
			if (left_brackets.empty())
			{
				throw std::runtime_error("Brackets are not properly matched at character " + std::to_string(i));
			}
			loops[left_brackets.top()] = i;
			loops[i] = left_brackets.top();
			left_brackets.pop();
		}
	}
	if (!left_brackets.empty())
	{
		throw std::runtime_error("Brackets are not properly matched at character " + std::to_string(i));
	}

	return loops;
}

void intepret(const std::string& code)
{
	std::vector<uint8_t> mem(1048576, 0);
	std::unordered_map<size_t, size_t> loops = find_loops(code);
	size_t ptr = 0;
	size_t ip = 0;
	while (ip < code.size())
	{
		switch (code[ip])
		{
			case '>':
				if (ptr + 1 >= mem.size()) throw std::runtime_error("Memory pointer overflow");
		    	ptr++;
		    	break;
		    case '<':
		    	if (ptr == 0) throw std::runtime_error("Memory pointer overflow");
		    	ptr--;
		    	break;
		    case '+': mem[ptr]++; break;
		    case '-': mem[ptr]--; break;
		    case '.': std::cout << static_cast<unsigned char>(mem[ptr]); break;
		    case ',':
		    {
		    	int inp = std::getchar();
				if (inp != EOF) mem[ptr] = static_cast<uint8_t>(inp);
				else throw std::runtime_error("EOF reached");
				break;
			}
			case '[':
			{
				size_t matching_right_bracket = loops[ip];
				if (mem[ptr] == 0) ip = matching_right_bracket;
				break;
			}
			case ']':
			{
				size_t matching_left_bracket = loops[ip];
				if (mem[ptr] != 0) ip = matching_left_bracket;
				break;
			}
			default: break;
		}
		
		ip++;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) throw std::runtime_error("Invalid arguments. Usage: <executable filename> <code filename>");
	char* filename = argv[1];
	std::ifstream codefile;
	codefile.open(filename, std::ios::in);
	if (!codefile) throw std::runtime_error("Could not open source file");

	std::string code;
	std::string line;
	while (std::getline(codefile, line))
	{
		code += line;
	}
	intepret(code);
	return 0;
}