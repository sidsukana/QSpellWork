#include "dbc.h"
#include "./../mpq/MPQ.h"

DBC::DBC(const QString &fileName) : m_header(0), m_records(0), m_strings(0)
{
    m_data = MPQ::readFile(fileName);

    if (m_data.size() == 0) {
        qCritical("Cannot load DBC '%s'", qPrintable(fileName));
        return;
    }

    m_header = reinterpret_cast<const DBCHeader *>(m_data.constData());

    if (qstrncmp(m_header->magic, DBC_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid DBC file!", qPrintable(fileName));
        return;
    }

    m_records = m_data.constData() + sizeof(DBCHeader);
    m_strings = m_records + m_header->recordCount * m_header->recordSize;
}

const char * DBC::getStringBlock() const
{
    return m_strings;
}

AnimationDataDBC::entry AnimationDataDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/AnimationData.dbc");

    entry e = dbc.getEntry<entry>(id);
    e.name = dbc.getStringBlock() + quint32(e.name);

    return e;
}

CameraShakesDBC::entry CameraShakesDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/CameraShakes.dbc");

    return dbc.getEntry<entry>(id);
}

CreatureDisplayInfoDBC::entry CreatureDisplayInfoDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/CreatureDisplayInfo.dbc");

    entry e = dbc.getEntry<entry>(id);
    e.skin1 = dbc.getStringBlock() + quint32(e.skin1);
    e.skin2 = dbc.getStringBlock() + quint32(e.skin2);
    e.skin3 = dbc.getStringBlock() + quint32(e.skin3);

    return e;
}

CreatureModelDataDBC::entry CreatureModelDataDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/CreatureModelData.dbc");

    entry e = dbc.getEntry<entry>(id);
    e.model = dbc.getStringBlock() + quint32(e.model);

    return e;
}

SpellEffectCameraShakesDBC::entry SpellEffectCameraShakesDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/SpellEffectCameraShakes.dbc");

    return dbc.getEntry<entry>(id);
}

SpellVisualDBC::entry SpellVisualDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/SpellVisual.dbc");

    return dbc.getEntry<entry>(id);
}

SpellVisualKitDBC::entry SpellVisualKitDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/SpellVisualKit.dbc");

    return dbc.getEntry<entry>(id);
}

SpellVisualEffectNameDBC::entry SpellVisualEffectNameDBC::getEntry(quint32 id)
{
    static DBC dbc("DBFilesClient/SpellVisualEffectName.dbc");

    entry e = dbc.getEntry<entry>(id);
    e.name = dbc.getStringBlock() + quint32(e.name);
    e.model = dbc.getStringBlock() + quint32(e.model);

    return e;
}


