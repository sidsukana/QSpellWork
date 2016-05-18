#ifndef WOV_DBC_H
#define WOV_DBC_H

#include <QString>
#include "dbc/DBC.h"

namespace AnimationDataDBC
{
    struct entry
    {
        quint32 id;
        quint32 nameOffset;

        const QString name() const;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace CameraShakesDBC
{
    struct entry
    {
        quint32 id;
        quint32 type;
        quint32 axis;
        float amplitude;
        float frequency;
        float duration;
        float phase;
        float coefficient;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace CreatureDisplayInfoDBC
{
    struct entry
    {
        quint32 id;
        quint32 model;
        quint32 sound;
        quint32 extra;
        float scale;
        quint32 opacity;
        quint32 skin1Offset;
        quint32 skin2Offset;
        quint32 skin3Offset;
        quint32 unknown1;
        quint32 unknown2;
        quint32 npcSound;

        const QString skin1() const;
        const QString skin2() const;
        const QString skin3() const;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace CreatureModelDataDBC
{
    struct entry
    {
        quint32 id;
        quint32 flags;
        quint32 modelOffset;

        const QString model() const;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellEffectCameraShakesDBC
{
    struct entry
    {
        quint32 id;
        quint32 shakes[3];
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellVisualDBC
{
    struct entry
    {
        quint32 id;
        quint32 precast;
        quint32 cast;
        quint32 impact;
        quint32 state;
        quint32 channel;
        quint32 hasMissile;
        quint32 missile;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellVisualKitDBC
{
    struct entry
    {
        quint32 id;
        qint32 startAnimation;
        qint32 animation;
        qint32 head;
        qint32 chest;
        qint32 base;
        qint32 leftHand;
        qint32 rightHand;
        qint32 breath1;
        qint32 breath2;
        qint32 unknown1;
        qint32 unknown2;
        qint32 base2;
        quint32 sound;
        quint32 shakes;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

namespace SpellVisualEffectNameDBC
{
    struct entry
    {
        quint32 id;
        quint32 nameOffset;
        quint32 modelOffset;

        const QString name() const;
        const QString model() const;
    };

    const DBCFile& getDbc();
    const DBCFileHeader* getHeader();
    const entry* getRecord(quint32 id, bool realId = false);
}

#endif
