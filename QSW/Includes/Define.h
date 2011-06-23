/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef QSW_DEFINE_H
#define QSW_DEFINE_H

#include <sys/types.h>
#include "CompilerDefs.h"

#define QSW_LITTLEENDIAN 1
#define QSW_BIGENDIAN    0

#ifndef QSW_ENDIAN
#  if defined (ACE_BIG_ENDIAN)
#    define QSW_ENDIAN QSW_BIGENDIAN
#  else //ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define QSW_ENDIAN QSW_LITTLEENDIAN
#  endif //ACE_BYTE_ORDER
#endif //QSW_ENDIAN

#if PLATFORM == PLATFORM_WINDOWS
#  define QSW_EXPORT __declspec(dllexport)
#  define QSW_IMPORT __cdecl
#else //PLATFORM != PLATFORM_WINDOWS
#  define QSW_EXPORT export
#  if defined(__APPLE_CC__) && defined(BIG_ENDIAN)
#    define QSW_IMPORT __attribute__ ((longcall))
#  elif defined(__x86_64__)
#    define QSW_IMPORT
#  else
#    define QSW_IMPORT __attribute__ ((cdecl))
#  endif //__APPLE_CC__ && BIG_ENDIAN
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  ifdef QSW_WIN32_DLL_IMPORT
#    define QSW_DLL_DECL __declspec(dllimport)
#  else //!QSW_WIN32_DLL_IMPORT
#    ifdef QSW_WIND_DLL_EXPORT
#      define QSW_DLL_DECL __declspec(dllexport)
#    else //!QSW_WIND_DLL_EXPORT
#      define QSW_DLL_DECL
#    endif //QSW_WIND_DLL_EXPORT
#  endif //QSW_WIN32_DLL_IMPORT
#else //PLATFORM != PLATFORM_WINDOWS
#  define QSW_DLL_DECL
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  define QSW_DLL_SPEC __declspec(dllexport)
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#else //PLATFORM != PLATFORM_WINDOWS
#  define QSW_DLL_SPEC
#  define DECLSPEC_NORETURN
#endif //PLATFORM

#ifndef DEBUG
#  define QSW_INLINE inline
#else //DEBUG
#  ifndef QSW_DEBUG
#    define QSW_DEBUG
#  endif //QSW_DEBUG
#  define QSW_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else //COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif //COMPILER == COMPILER_GNU

#if COMPILER != COMPILER_MICROSOFT

#endif //COMPILER


#endif //QSW_DEFINE_H
