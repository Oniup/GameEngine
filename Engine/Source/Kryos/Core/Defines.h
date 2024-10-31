#pragma once

#include <fmt/format.h>	
#include <fmt/color.h>

#if defined(__clang__) || defined(__GNUG__) && defined(__GNUC__)
#	define KY_GENERATE_TRAP() __builtin_trap()
#	define KY_THREADLOCAL __thread
#	define KY_STDCALL __attribute__((stdcall))
#	define KY_CDECL __attribute__((cdecl))
#	define KY_RESTRICT __restrict__
#	define KY_FORCE_INLINE __attribute__((always_inline)) inline
#	define KY_FORCE_NOINLINE __attribute__((noinline))
#	define KY_NO_RETURN __attribute__((noreturn))
#	define KY_DEPRECATED [[deprecated]]
#elif defined(_MSC_VER)
#	if _MSC_VER < 1900
#		error "Required Visual Studio 2015 or newer."
#	endif
#	define KY_GENERATE_TRAP() __debugbreak()
#	define KY_THREADLOCAL __declspec(thread)
#	define KY_STDCALL __stdcall
#	define KY_CDECL __cdecl
#	define KY_RESTRICT __restrict
#	define KY_FORCE_INLINE __forceinline
#	define KY_FORCE_NOINLINE __declspec(noinline)
#	define KY_NO_RETURN __declspec(noreturn)
#	define KY_DEPRECATED __declspec(deprecated)
#	undef __PRETTY_FUNCTION__
#	define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#	error "Unknown compiler"
#endif

#define KY_COLOR_RGB_RED			231, 78, 61
#define KY_COLOR_RGB_DEEP_RED		196, 43, 28
#define KY_COLOR_RGB_ORANGE_YELLOW  240, 162, 25
#define KY_COLOR_RGB_GREY			180, 180, 166
#define KY_COLOR_RGB_DARKER_GREY	103, 103, 95

#if defined(KY_DEBUG) || defined(KY_RELEASE)
#	define KY_ASSERT(_Expression, ...) \
		if (!(_Expression))	\
		{ \
			fmt::print(stderr, fmt::emphasis::bold | fmt::fg(fmt::rgb(KY_COLOR_RGB_DEEP_RED)), __FILE__, __FUNCTION__, __LINE__, #_Expression, fmt::format(__VA_ARGS__)); \
			std::fflush(stderr); \
			KY_GENERATE_TRAP(); \
		} \
		else \
			((void)0)
#else
#	define KY_ASSERT(_Expression, ...)
#endif
