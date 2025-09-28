#pragma once
#include <span>
#include <tuple>
#include <string_view>
#include <vector>
#include <map>

auto parseArgs(int argc, char* argv[]) {
	auto args = std::span{ argv,static_cast<size_t>(argc) }
		| std::views::transform([](auto pChars) { //char* -> string_view
		return std::string_view{ pChars };
			})
		| std::views::transform([](const auto& name) { //string_view -> argType,value
		static __int64 argPos{ -1ll };
		std::println(std::cout, "{}={}", ++argPos, name); //argpos als string? oder gar enum-class als schluessel..?
		return std::tuple<size_t, std::string_view>{argPos, name};
			})
		| std::ranges::to<std::vector>() //<-hier geht auch nach map
		;
	return args;
}
