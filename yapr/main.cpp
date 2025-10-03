
#include <iostream>
#include <print>
#include <ranges>
#include <string_view>
#include <tuple>
#include <vector>
#include <map>
#include <unordered_map>
#include "parseArgs.h"
#include "init_locale.h"
#include "character_set.h"


int main(int argc, char* argv[]) {
	init_locale<de_DE>();
	const auto args = parseArgs(argc, argv);

	for (const fs::path& fn : onlyExistingPdfs(args) ){
		std::println(std::cout, "Processing: {}", fn.string());
	}
	return 0;
}