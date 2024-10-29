#pragma once

#include <string_view>
#include <array>

#ifdef _MSC_VER
#	include <xhash>
#else
#	include <hash_func>
#endif

namespace Oniun::Meta
{

	namespace Detail
	{

		template<typename T>
		constexpr std::string_view GetWrappedTypeName()
		{
#ifdef _MSC_VER
			return std::string_view(__FUNCSIG__);
#else
			return std::string_view(__PRETTY_FUNCTION__);
#endif
		}

		constexpr size_t GetWrappedPrefixLength()
		{
			constexpr std::string_view wrappedName = GetWrappedTypeName<void>();
			return wrappedName.find("void");
		}

		constexpr size_t GetWrappedSuffixLength()
		{
			constexpr std::string_view wrappedName = GetWrappedTypeName<void>();
			return wrappedName.size() - GetWrappedPrefixLength() - 4;
		}

	}

	template<typename T>
	constexpr std::string_view GetTypeName()
	{
		constexpr std::string_view wrappedName = Detail::GetWrappedTypeName<T>();
		constexpr size_t wrappedPrefixLength = Detail::GetWrappedPrefixLength();
		constexpr size_t wrappedSuffixLength = Detail::GetWrappedSuffixLength();
		
#if _MSC_VER
		std::string_view name = wrappedName.substr(wrappedPrefixLength, wrappedName.size() - wrappedPrefixLength - wrappedSuffixLength);
		constexpr std::array<std::string_view, 4> remove = { "struct", "class", "enum", "union" };

		for (const std::string_view& str : remove)
		{
			size_t offset = name.find(str);
			if (offset != std::string_view::npos)
				name = name.substr(offset + str.size() + 1);
		}

		return name;
#else
		return wrappedName.substr(wrappedPrefixLength, wrappedName.size() - wrappedPrefixLength - wrappedSuffixLength);
#endif
	}

	template<typename T>
	constexpr size_t GetTypeHash()
	{
		return std::hash <std::string_view>{}(GetTypeName<T>());
	}

}