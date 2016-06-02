#include <QRegExp>

#include "spellvisualkit.h"
#include "m2.h"
#include "modelscene.h"
#include "wovdbc.h"

SpellVisualKit::SpellVisualKit(quint32 id, bool oneshot)
    : m_kit(SpellVisualKitDBC::getRecord(id, true)),
      m_oneshot(oneshot),
      m_model(0)
{
}

void SpellVisualKit::attach(M2 *model)
{
    m_model = model;

    attachEffect(m_kit->head, ATTACHMENT_HEAD);
    attachEffect(m_kit->chest, ATTACHMENT_CHEST);
    attachEffect(m_kit->base, ATTACHMENT_BASE);
    attachEffect(m_kit->leftHand, ATTACHMENT_LEFT_HAND);
    attachEffect(m_kit->rightHand, ATTACHMENT_RIGHT_HAND);
    attachEffect(m_kit->breath1, ATTACHMENT_BREATH_2);
    attachEffect(m_kit->breath2, ATTACHMENT_BREATH);
    attachEffect(m_kit->base2, ATTACHMENT_BASE);

    //if (m_kit->startAnimation != -1)
    //    m_model->setAnimation(m_kit->startAnimation);

    if (m_kit->animation != -1)
        m_model->setAnimation(m_kit->animation);
}

void SpellVisualKit::detach()
{
    QHash<quint32, M2 *>::const_iterator it = m_effects.constBegin();
    while (it != m_effects.constEnd()) {
        it.value()->setAnimation(-1);
        it.value()->setAnimation(159);
        it++;
    }

    m_model->setAnimation(0);
}

void SpellVisualKit::addCameraShakes(ModelScene *scene)
{
    if (!scene || !m_kit || !m_kit->shakes)
        return;

    const SpellEffectCameraShakesDBC::entry* shakes = SpellEffectCameraShakesDBC::getRecord(m_kit->shakes, true);
    if (!shakes)
        return;

    for (int i = 0; i < 3; i++) {
        if (shakes->shakes[i])
            scene->addCameraShake(shakes->shakes[i]);
    }
}

bool SpellVisualKit::update(M2 *model)
{
    if (!model || !m_kit)
        return false;

    if (!m_model)
        attach(model);

    QHash<quint32, M2 *>::iterator it = m_effects.begin();
    while (it != m_effects.end()) {
        M2 *effect = it.value();

        if (effect->animation() == -1) {
            m_model->detachModel(it.key(), effect);
            it = m_effects.erase(it);
            delete effect;
        } else {
            it++;
        }
    }

    return !m_effects.isEmpty();
}

void SpellVisualKit::attachEffect(qint32 id, quint32 slot)
{
    if (id <= 0)
        return;

    const SpellVisualEffectNameDBC::entry* effectName = SpellVisualEffectNameDBC::getRecord(id, true);
    if (!effectName)
        return;

    QString modelName = QString(effectName->model()).replace(QRegExp(".md[xl]", Qt::CaseInsensitive), ".m2");

    M2 *effect = new M2(modelName);
    effect->setAnimation(0, m_oneshot);
    effect->setAnimation(158);

    m_model->attachModel(slot, effect);

    m_effects[slot] = effect;
}
