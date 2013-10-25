#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef WOV_LIBRARY
#  define WOV_EXPORT Q_DECL_EXPORT
#else
#  define WOV_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H
