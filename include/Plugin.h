#pragma once

#include <string_view>

namespace Plugin
{
	using namespace std::literals;

	inline constexpr REL::Version VERSION
	{
		// clang-format off
		1,
		3,
		1,
		// clang-format on
	};

	inline constexpr auto NAME = "EldenParry"sv;
}
