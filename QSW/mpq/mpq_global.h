#ifndef MPQ_GLOBAL_H
#define MPQ_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MPQ_LIBRARY)
#  define MPQSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MPQSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MPQ_GLOBAL_H
