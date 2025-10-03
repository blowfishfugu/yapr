#pragma once
#include <array>
const enum whitespace_codes : char{
	NUL='\x00',
	HT='\x09',
	LF='\x0A',
	FF='\x0C',
	CR='\x0D',
	SP='\x20',
};

constexpr static std::array<bool, 255> whitespaces = []() {
	std::array<bool, 255> white{};
	const std::array<char,6> whitecodes = {NUL,HT,LF,FF,CR,SP};
	for (const char& c : whitecodes) {
		white[c] = true;
	}
	return white;
	}();

const enum delimiter_codes : char {
	LEFTPARENTHESIS='(',
	RIGHTPARENTHESIS=')',
	LESSTHAN='<',
	GREATERTHAN='>',
	LEFTSQUARE='[',
	RIGHTSQUARE=']',
	LEFTCURL='{',
	RIGHTCURL='}',
	SOLIDUS='/',
	PERCENT='%',
};

constexpr static std::array<bool, 255> delimiters = []() {
	std::array<bool, 255> del{};
	const std::array<char, 10> delcodes = { 
	LEFTPARENTHESIS,RIGHTPARENTHESIS,
	LESSTHAN,GREATERTHAN,
	LEFTSQUARE,RIGHTSQUARE,
	LEFTCURL,RIGHTCURL,
	SOLIDUS,
	PERCENT,
	};
	for (const char& c : delcodes) {
		del[c] = true;
	}
	return del;
	}();