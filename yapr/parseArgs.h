#pragma once
#include <span>
#include <tuple>
#include <string_view>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

auto parseArgs(int argc, char* argv[]) {
	return std::span{ argv,static_cast<size_t>(argc) }
		| std::views::transform([](auto pChars) { //char* -> string_view
			return std::string_view{ pChars };
			})
		| std::views::transform([](auto&& name) { //string_view -> argType,value
			static __int64 argPos{ -1ll };
			std::println(std::cout, "{}={}", ++argPos, name); //argpos als string? oder gar enum-class als schluessel..?
			return std::tuple<size_t, std::string_view>{argPos, name};
			})
		| std::ranges::to<std::vector>()
		;
}

auto onlyExistingPdfs(const auto& args) {
	return args
		//ignore index 0, but return anything else
		| std::views::filter([](const auto& tpl) { return std::get<0>(tpl) > 0ull; })
		//just the path of the tuple, transformed to absolute
		| std::views::transform([](const auto& tpl) { return fs::absolute(fs::path{ std::get<1>(tpl) }); })
		//and just PDFs that exist
		| std::views::filter([](const fs::path& p) { return
			(p.extension().string() == ".pdf" || p.extension().string() == ".PDF")
			&& fs::exists(p);
			});
}

