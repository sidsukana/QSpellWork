#include "Defines.h"

QSettings& QSW::settings()
{
    static QSettings m_settings("QSW.ini", QSettings::IniFormat);
    m_settings.sync();
    return m_settings;
}

QString QSW::VERSION = "2.0.0";
