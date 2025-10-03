#pragma once
#include <optional>
#include <string_view>
#include <string>
#include "character_set.h"
#include <vector>
#include <map>
#include <variant>

//starts on '/' and ends on whitespace or delimiter i guess (not mentioned in reference)
// on first reading, will try !is_regular
//can contain #Numbersigns-> 2digit hexcode to char, encodes whitespaces/delimiters
//->is a keytype, should become comparable/orderable/indexable "<=>"
//further thoughts "10 0" might be an ObjectName also..without leading "/"
struct ObjectName {
	using value_type = std::string;
	value_type value{};
	explicit ObjectName(const std::string& str)
		:value{ str }
	{
	};

	auto operator<=>(const ObjectName& lh)noexcept {
		return this->value <=> lh.value;
	}

	ObjectName& operator=(const std::string& str) noexcept {
		this->value = str;
		return *this;
	}

	ObjectName& operator=(const ObjectName& obj) noexcept {
		this->value = obj.value;
		return *this;
	}
};

//created by "id rev obj", to "endobj"
//or "id rev R", precreated with unknown type
//defaults to nullopt
//meant to hold decoded data, after applying filters,
//pdf will come in mostly base85-encoded, 
// maybe lz-compressed, crypted, or postscript maybe -> raw-data will stay in separate file-structure
//unparsable stay at nullopt
struct BaseObject{
	using value_type = std::variant<
		std::nullopt_t,
		bool, //Boolean
		std::int64_t, //NumericInt
		double, //NumericReal
		std::string, //LiteralString,HexString (same type, read different)
		std::vector<uchar>, //stream -> could be refined to startpos..endpos/or length
		std::vector<BaseObject*>, //[] Array
		std::map<ObjectName, BaseObject*>, //<<>> Dictionary
		std::tuple<BaseObject*,BaseObject*>, // <<>>dict, stream..endstream
	>;
	value_type value{std::nullopt};
	
};

//true/false
struct Boolean : public BaseObject{
	using value_type = bool;
};

//number, signed, no dots
struct NumericInt : public BaseObject {
	using value_type = std::int64_t;
	NumericInt() : BaseObject{ value_type{} } {};
};

//number, signed, with dot
struct NumericReal : public BaseObject {
	using value_type = double;
	NumericReal() :BaseObject{ value_type{} } {};
};

//starts on '(', ends on ')',
// can contain escape-sequences on reverse-solidus "\"
struct LiteralString : public BaseObject {
	using value_type = std::string;
	LiteralString() :BaseObject{ value_type{} } {};
};
//starts on '<', ends on '>',
// trailing 0 on uneven count of bytes
// "whitespaces shall be ignored" (why?)
struct HexString : public BaseObject {
	using value_type = std::string;
	HexString() :BaseObject{ value_type{} } {};
};



//starts on '[' ends on ']' (might contain subarrays...)
//any can be any of the mentioned pdf-object-types
struct ObjectArray : public BaseObject {
	using value_type = std::vector<BaseObject*>;
	ObjectArray() :BaseObject{ value_type{} } {};
};

//starts on "<<", ends on ">>", can have subobjects
struct DictionaryObject : public BaseObject {
	using value_type = std::map<ObjectName, BaseObject*>;
	DictionaryObject() : BaseObject{ value_type{} } {};
};

//subcontainer, starts on "stream\n", ends on "\nendstream"
struct StreamEntry : public BaseObject {
	using value_type = std::vector<uchar>; //stream -> could be refined to startpos..endpos/or length
	StreamEntry() : BaseObject{ value_type{} } {};
};

//A stream shall consist of a dictionary followed by zero or more bytes bracketed
//between the keywords "stream" (followed by newline) and "endstream".
struct StreamObject : public BaseObject {
	using value_type = std::tuple<BaseObject*, BaseObject*>;
	StreamObject() : BaseObject{ value_type{} } {};
};