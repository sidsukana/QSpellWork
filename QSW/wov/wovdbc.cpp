#include "dbc/DBC.h"
#include "mpq/MPQ.h"
#include "wovdbc.h"

// AnimationData.dbc
const DBCFile& AnimationDataDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/AnimationData.dbc");
    return dbc;
}

const DBCFileHeader* AnimationDataDBC::getHeader()
{
    return getDbc().getHeader();
}

const AnimationDataDBC::entry* AnimationDataDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString AnimationDataDBC::entry::name() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(nameOffset));
}

// CameraShakes.dbc
const DBCFile& CameraShakesDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/CameraShakes.dbc");
    return dbc;
}

const DBCFileHeader* CameraShakesDBC::getHeader()
{
    return getDbc().getHeader();
}

const CameraShakesDBC::entry* CameraShakesDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// CreatureDisplayInfo.dbc
const DBCFile& CreatureDisplayInfoDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/CreatureDisplayInfo.dbc");
    return dbc;
}

const DBCFileHeader* CreatureDisplayInfoDBC::getHeader()
{
    return getDbc().getHeader();
}

const CreatureDisplayInfoDBC::entry* CreatureDisplayInfoDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString CreatureDisplayInfoDBC::entry::skin1() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(skin1Offset));
}

const QString CreatureDisplayInfoDBC::entry::skin2() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(skin2Offset));
}

const QString CreatureDisplayInfoDBC::entry::skin3() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(skin3Offset));
}

// CreatureModelData.dbc
const DBCFile& CreatureModelDataDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/CreatureModelData.dbc");
    return dbc;
}

const DBCFileHeader* CreatureModelDataDBC::getHeader()
{
    return getDbc().getHeader();
}

const CreatureModelDataDBC::entry* CreatureModelDataDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString CreatureModelDataDBC::entry::model() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(modelOffset));
}

// SpellEffectCameraShakes.dbc
const DBCFile& SpellEffectCameraShakesDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellEffectCameraShakes.dbc");
    return dbc;
}

const DBCFileHeader* SpellEffectCameraShakesDBC::getHeader()
{
    return getDbc().getHeader();
}

const SpellEffectCameraShakesDBC::entry* SpellEffectCameraShakesDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisual.dbc
const DBCFile& SpellVisualDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellVisual.dbc");
    return dbc;
}

const DBCFileHeader* SpellVisualDBC::getHeader()
{
    return getDbc().getHeader();
}

const SpellVisualDBC::entry* SpellVisualDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisualKit.dbc
const DBCFile& SpellVisualKitDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellVisualKit.dbc");
    return dbc;
}

const DBCFileHeader* SpellVisualKitDBC::getHeader()
{
    return getDbc().getHeader();
}

const SpellVisualKitDBC::entry* SpellVisualKitDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisualEffectName.dbc
const DBCFile& SpellVisualEffectNameDBC::getDbc()
{
    static DBCFile dbc("DBFilesClient/SpellVisualEffectName.dbc");
    return dbc;
}

const DBCFileHeader* SpellVisualEffectNameDBC::getHeader()
{
    return getDbc().getHeader();
}

const SpellVisualEffectNameDBC::entry* SpellVisualEffectNameDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellVisualEffectNameDBC::entry::name() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(nameOffset));
}

const QString SpellVisualEffectNameDBC::entry::model() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(modelOffset));
}
