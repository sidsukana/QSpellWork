/*
 * Copyright (C) 2010 Anathema Engine project <http://valkyrie-wow.ru/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ANATHEMA_BYTECONVERTER_H
#define ANATHEMA_BYTECONVERTER_H

/** ByteConverter reverse your byte order.  This is use
    for cross platform where they have different endians.
 */

#include <Platform/Define.h>
#include <algorithm>

namespace ByteConverter
{
    template<size_t T>
    inline void convert(char *val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char *) {}
    template<> inline void convert<1>(char *) {}            // ignore central byte

    template<typename T>
    inline void apply(T *val)
    {
        convert<sizeof(T)>((char *)(val));
    }
}

#if ANATHEMA_ENDIAN == ANATHEMA_BIGENDIAN
template<typename T> inline void EndianConvert(T& val) { ByteConverter::apply<T>(&val); }
template<typename T> inline void EndianConvertReverse(T&) { }
#else
template<typename T> inline void EndianConvert(T&) { }
template<typename T> inline void EndianConvertReverse(T& val) { ByteConverter::apply<T>(&val); }
#endif

template<typename T> void EndianConvert(T*);         // will generate link error
template<typename T> void EndianConvertReverse(T*);  // will generate link error

inline void EndianConvert(quint8&) { }
inline void EndianConvert(qint8&)  { }
inline void EndianConvertReverse(quint8&) { }
inline void EndianConvertReverse(qint8&) { }

#endif
