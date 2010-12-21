/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_DEFINE_H
#define ANATHEMA_DEFINE_H

#include <sys/types.h>

#include <ace/Basic_Types.h>
#include <ace/Default_Constants.h>
#include <ace/OS_NS_dlfcn.h>
#include <ace/ACE_export.h>

#include "Platform/CompilerDefs.h"

#define ANATHEMA_LITTLEENDIAN 0
#define ANATHEMA_BIGENDIAN    1

#if !defined(ANATHEMA_ENDIAN)
#  if defined (ACE_BIG_ENDIAN)
#    define ANATHEMA_ENDIAN ANATHEMA_BIGENDIAN
#  else //ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define ANATHEMA_ENDIAN ANATHEMA_LITTLEENDIAN
#  endif //ACE_BYTE_ORDER
#endif //ANATHEMA_ENDIAN

typedef ACE_SHLIB_HANDLE ANATHEMA_LIBRARY_HANDLE;

#define ANATHEMA_SCRIPT_NAME "ASE"
#define ANATHEMA_SCRIPT_SUFFIX ACE_DLL_SUFFIX
#define ANATHEMA_SCRIPT_PREFIX ACE_DLL_PREFIX
#define ANATHEMA_LOAD_LIBRARY(libname)    ACE_OS::dlopen(libname)
#define ANATHEMA_CLOSE_LIBRARY(hlib)      ACE_OS::dlclose(hlib)
#define ANATHEMA_GET_PROC_ADDR(hlib,name) ACE_OS::dlsym(hlib,name)

#define ANATHEMA_PATH_MAX PATH_MAX                            // ace/os_include/os_limits.h -> ace/Basic_Types.h

#if PLATFORM == PLATFORM_WINDOWS
#  define ANATHEMA_EXPORT __declspec(dllexport)
#  define ANATHEMA_IMPORT __cdecl
#else //PLATFORM != PLATFORM_WINDOWS
#  define ANATHEMA_EXPORT export
#  if defined(__APPLE_CC__) && defined(BIG_ENDIAN)
#    define ANATHEMA_IMPORT __attribute__ ((longcall))
#  elif defined(__x86_64__)
#    define ANATHEMA_IMPORT
#  else
#    define ANATHEMA_IMPORT __attribute__ ((cdecl))
#  endif //__APPLE_CC__ && BIG_ENDIAN
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  ifdef ANATHEMA_WIN32_DLL_IMPORT
#    define ANATHEMA_DLL_DECL __declspec(dllimport)
#  else //!ANATHEMA_WIN32_DLL_IMPORT
#    ifdef ANATHEMA_WIND_DLL_EXPORT
#      define ANATHEMA_DLL_DECL __declspec(dllexport)
#    else //!ANATHEMA_WIND_DLL_EXPORT
#      define ANATHEMA_DLL_DECL
#    endif //ANATHEMA_WIND_DLL_EXPORT
#  endif //ANATHEMA_WIN32_DLL_IMPORT
#else //PLATFORM != PLATFORM_WINDOWS
#  define ANATHEMA_DLL_DECL
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  define ANATHEMA_DLL_SPEC __declspec(dllexport)
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#else //PLATFORM != PLATFORM_WINDOWS
#  define ANATHEMA_DLL_SPEC
#  define DECLSPEC_NORETURN
#endif //PLATFORM

#if !defined(DEBUG)
#  define ANATHEMA_INLINE inline
#else //DEBUG
#  if !defined(ANATHEMA_DEBUG)
#    define ANATHEMA_DEBUG
#  endif //ANATHEMA_DEBUG
#  define ANATHEMA_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else //COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif //COMPILER == COMPILER_GNU

typedef ACE_INT64 int64;
typedef ACE_INT32 int32;
typedef ACE_INT16 int16;
typedef ACE_INT8 int8;
typedef ACE_UINT64 uint64;
typedef ACE_UINT32 uint32;
typedef ACE_UINT16 uint16;
typedef ACE_UINT8 uint8;

#if COMPILER != COMPILER_MICROSOFT
typedef uint16      WORD;
typedef uint32      DWORD;
#endif //COMPILER

typedef uint64 OBJECT_HANDLE;

#endif //ANATHEMA_DEFINE_H
