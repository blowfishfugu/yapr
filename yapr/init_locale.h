#pragma once
#include <locale>
#define NOMINMAX
#include <Windows.h>
#include <iostream>



struct de_DE{
	inline static std::locale de_de{ "DE_de" };
};

template<typename localeType>
void init_locale() {
	static_assert(false, "please name a locale-type");
}

template<>
void init_locale<de_DE>(){
	SetConsoleOutputCP(1252u); //����
	std::cout.imbue(de_DE::de_de);
}