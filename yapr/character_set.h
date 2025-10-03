#pragma once
#include <array>
#include <numeric>
#include <concepts>
#include <type_traits>
#include <ranges>

using uchar = unsigned char;
constexpr size_t maxchar = std::numeric_limits<uchar>::max();

template<typename T>
constexpr bool can_uchar= std::is_same_v<T,uchar>|std::is_convertible_v<T, uchar>;

template<typename T=uchar>
concept is_uchar = can_uchar<T>;

const enum whitespace_codes : uchar{
	NUL='\x00',
	TAB='\x09',
	LINEFEED='\x0A',
	FORMFEED='\x0C',
	CARRIAGERETURN='\x0D',
	SPACE='\x20',
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
	constexpr std::array<uchar,6> whitecodes = {
		NUL,TAB,LINEFEED,FORMFEED,CARRIAGERETURN,SPACE
	};
	for (const uchar& c : whitecodes) {
		white[c] = true;
	}
	return white;
	}();



constexpr static const std::array<bool, maxchar> delimiters = []() {
	std::array<bool, maxchar> del{};
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

template<is_uchar UC>
constexpr bool is_whitespace(const UC c) {
	return whitespaces[c];
}

/// Override of is_whitespace: "PDF treats any sequence of consecutive white-space characters as one character"
/// auto = iterable of uchars, is there a concept for that?
constexpr bool is_whitespace( std::string_view characters ) {
	for (const uchar& c : characters) {
		if (!is_whitespace(c)) {
			return false;
		}
	}
	return true;
}

template<is_uchar UC=uchar>
constexpr bool is_delimiter(const UC c) {
	return delimiters[c];
}

template<is_uchar UC=uchar>
constexpr bool is_regular(const UC c) {
	return !is_whitespace(c) && !is_delimiter(c);
}

#ifndef NDEBUG
constexpr bool t1 = is_whitespace(" \t\r\n");
static_assert(t1 == true);
constexpr bool t2 = is_delimiter(0x28);
constexpr bool t3 = is_delimiter(41);
#endif
