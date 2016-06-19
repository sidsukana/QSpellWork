#ifndef QSW_EXPORT_H
#define QSW_EXPORT_H
#include <QtGlobal>
 
#ifdef QSW_LIB
	#define QSW_EXPORT Q_DECL_EXPORT
#else
	#define QSW_EXPORT Q_DECL_IMPORT
#endif
 
#endif
