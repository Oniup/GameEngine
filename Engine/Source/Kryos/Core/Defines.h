#pragma once

#include <fmt/format.h>	
#include <fmt/color.h>
#include <filesystem>

#if defined(__clang__) || defined(__GNUG__) && defined(__GNUC__)
#  define KY_GENERATE_TRAP() __builtin_trap()
#  define KY_THREADLOCAL __thread
#  define KY_STDCALL __attribute__((stdcall))
#  define KY_CDECL __attribute__((cdecl))
#  define KY_RESTRICT __restrict__
#  define KY_FORCE_INLINE __attribute__((always_inline)) inline
#  define KY_FORCE_NOINLINE __attribute__((noinline))
#  define KY_NO_RETURN __attribute__((noreturn))
#  define KY_DEPRECATED [[deprecated]]
#elif defined(_MSC_VER)
#  if _MSC_VER < 1900
#    error "Required Visual Studio 2015 or newer."
#  endif

#  define KY_GENERATE_TRAP() __debugbreak()
#  define KY_THREADLOCAL __declspec(thread)
#  define KY_STDCALL __stdcall
#  define KY_CDECL __cdecl
#  define KY_RESTRICT __restrict
#  define KY_FORCE_INLINE __forceinline
#  define KY_FORCE_NOINLINE __declspec(noinline)
#  define KY_NO_RETURN __declspec(noreturn)
#  define KY_DEPRECATED __declspec(deprecated)

#  undef __PRETTY_FUNCTION__
#  define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#  error "Unknown compiler"
#endif

#if defined(KY_DEBUG) || defined(KY_RELEASE)

namespace Kryos::Detail
{

	KY_FORCE_INLINE void AssertMessage(bool expression_result, const std::string_view& fileName, const std::string_view& functionName, int line, 
									   const std::string_view& expression, const std::string_view& formattedMessage)
	{
		if (!expression_result)
		{
			fmt::print(stderr, fmt::emphasis::bold | fmt::fg(fmt::color::indian_red), 
				"[ASSERT({} == false)] {}:{}:{}: {}", expression, std::filesystem::path(fileName).filename().c_str(), functionName, line, formattedMessage);
		}
	}

}

#	define KY_ASSERT(_Expression, ...) Kryos::Detail::AssertMessage((_Expression), __FILE__, __FUNCTION__, __LINE__, #_Expression, fmt::format(__VA_ARGS__))
#else
#	define KY_ASSERT(_Expression, ...)
#endif
