
#include <iostream>
#include <print>
#include <ranges>
#include <string_view>
#include <tuple>
#include <vector>
#include <map>
#include <unordered_map>
#include "parseArgs.h"
#include "de_de.h"


int main(int argc, char* argv[]) {
	initLocale<de_DE>();
	auto args = parseArgs(argc, argv);

	return 0;
}