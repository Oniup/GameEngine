#pragma once

#if defined(__clang__) || defined(__GNUG__) && defined(__GNUC__)
#  define O_GENERATE_TRAP() __builtin_trap()
#  define O_THREADLOCAL __thread
#  define O_STDCALL __attribute__((stdcall))
#  define O_CDECL __attribute__((cdecl))
#  define O_RESTRICT __restrict__
#  define O_FORCE_INLINE __attribute__((always_inline)) inline
#  define O_FORCE_NOINLINE __attribute__((noinline))
#  define O_NO_RETURN __attribute__((noreturn))
#  define O_DEPRECATED [[deprecated]]
#elif defined(_MSC_VER)
#  if _MSC_VER < 1900
#    error "Required Visual Studio 2015 or newer."
#  endif

#  define O_GENERATE_TRAP() __debugbreak()
#  define O_THREADLOCAL __declspec(thread)
#  define O_STDCALL __stdcall
#  define O_CDECL __cdecl
#  define O_RESTRICT __restrict
#  define O_FORCE_INLINE __forceinline
#  define O_FORCE_NOINLINE __declspec(noinline)
#  define O_NO_RETURN __declspec(noreturn)
#  define O_DEPRECATED __declspec(deprecated)

#  undef __PRETTY_FUNCTION__
#  define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#  error "Unknown compiler"
#endif
