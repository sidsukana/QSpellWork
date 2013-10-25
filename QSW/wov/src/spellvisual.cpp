#include <QTimer>

#include "spellvisual.h"

SpellVisual::SpellVisual() : m_caster(0), m_target(0)
{
    m_visual.id = 0;

    m_castingTime = 2000;
    m_duration = 5000;
    m_channeled = false;
}

quint32 SpellVisual::visual() const
{
    return m_visual.id;
}

quint32 SpellVisual::castingTime() const
{
    return m_castingTime;
}

quint32 SpellVisual::duration() const
{
    return m_duration;
}

bool SpellVisual::channeled() const
{
    return m_channeled;
}

Model * SpellVisual::caster()
{
    return m_caster;
}

Model * SpellVisual::target()
{
    return m_target;
}

void SpellVisual::setVisual(quint32 visual)
{
    m_visual = SpellVisualDBC::getEntry(visual);

    if (m_visual.id != visual)
        m_visual.id = 0;
}

void SpellVisual::setCastingTime(quint32 castingTime)
{
    m_castingTime = castingTime;
}

void SpellVisual::setDuration(quint32 duration)
{
    m_duration = duration;
}

void SpellVisual::setChanneled(bool channeled)
{
    m_channeled = channeled;
}

void SpellVisual::setCaster(Model *caster)
{
    m_caster = caster;
}

void SpellVisual::setTarget(Model *target)
{
    m_target = target;
}

void SpellVisual::start()
{
    if (!visual())
        return;

    if (caster())
        caster()->addSpellVisualKit(m_visual.precast);

    QTimer::singleShot(castingTime(), this, SLOT(cast()));
}

void SpellVisual::cast()
{
    if (!visual())
        return;

    if (caster()) {
        caster()->removeSpellVisualKit(m_visual.precast);
        caster()->addSpellVisualKit(m_visual.cast, true);

        if (duration() && channeled())
            caster()->addSpellVisualKit(m_visual.channel);
    }

    if (target()) {
        target()->addSpellVisualKit(m_visual.impact, true);

        if (duration())
            target()->addSpellVisualKit(m_visual.state);
    }

    if (duration())
        QTimer::singleShot(duration(), this, SLOT(cancel()));
}

void SpellVisual::cancel()
{
    if (!visual())
        return;

    if (caster()) {
        caster()->removeSpellVisualKit(m_visual.precast);
        caster()->removeSpellVisualKit(m_visual.channel);
    }

    if (target())
        target()->removeSpellVisualKit(m_visual.state);
}
