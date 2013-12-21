#ifndef SPELL_VISUAL_KIT
#define SPELL_VISUAL_KIT

#include <QHash>

#include "dbc.h"

class M2;
class ModelScene;

class SpellVisualKit
{
public:
    explicit SpellVisualKit(quint32 id, bool oneshot = false);

    void attach(M2 *model);
    void detach();

    void addCameraShakes(ModelScene *scene);

    bool update(M2 *model);

private:
    void attachEffect(qint32 id, quint32 slot);

    SpellVisualKitDBC::entry m_kit;
    bool m_oneshot;

    M2 *m_model;

    QHash<quint32, M2 *> m_effects;
};

#endif
