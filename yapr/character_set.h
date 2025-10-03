#pragma once
#include <array>
#include <numeric>

using uchar = unsigned char;
constexpr size_t maxchar = std::numeric_limits<uchar>::max();

const enum whitespace_codes : uchar{
	NUL='\x00',
	HT='\x09',
	LF='\x0A',
	FF='\x0C',
	CR='\x0D',
	SP='\x20',
};

const enum delimiter_codes : uchar {
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

constexpr static const std::array<bool, maxchar> whitespaces = []() {
	std::array<bool, maxchar> white{};
	constexpr std::array<uchar,6> whitecodes = {NUL,HT,LF,FF,CR,SP};
	for (const uchar& c : whitecodes) {
		white[c] = true;
	}
	return white;
	}();



constexpr static const std::array<bool, maxchar> delimiters = []() {
	std::array<bool, 255> del{};
	constexpr std::array<uchar, 10> delcodes = { 
	LEFTPARENTHESIS,RIGHTPARENTHESIS,
	LESSTHAN,GREATERTHAN,
	LEFTSQUARE,RIGHTSQUARE,
	LEFTCURL,RIGHTCURL,
	SOLIDUS,
	PERCENT,
	};
	for (const uchar& c : delcodes) {
		del[c] = true;
	}
	return del;
	}();

constexpr bool is_whitespace(const uchar c) {
	return whitespaces[c];
}

constexpr bool is_delimiter(const uchar c) {
	return delimiters[c];
}

constexpr bool is_regular(const uchar c) {
	return !is_whitespace(c) && !is_delimiter(c);
}