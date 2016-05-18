#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "mvp.h"

class QOpenGLShaderProgram;

class M2;
class ModelScene;
class SpellVisualKit;

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 displayId READ displayId WRITE setDisplayId)
    Q_PROPERTY(float x READ x WRITE setX)
    Q_PROPERTY(float y READ y WRITE setY)
    Q_PROPERTY(float orientation READ orientation WRITE setOrientation)

public:
    Model(ModelScene *scene);

    Q_INVOKABLE void addSpellVisualKit(quint32 id, bool oneshot = false);
    Q_INVOKABLE void removeSpellVisualKit(quint32 id);

    quint32 displayId() const;
    void setDisplayId(quint32 displayId);

    float x() const;
    float y() const;
    float orientation() const;

    void setX(float x);
    void setY(float y);
    void setOrientation(float orientation);

    void update(int timeDelta);
    void render(QOpenGLShaderProgram *program, MVP mvp);
    void renderParticles(QOpenGLShaderProgram *program, MVP mvp);

private:
    void updateVisualKits();

    ModelScene *m_scene;

    quint32 m_displayId;
    float m_x, m_y, m_orientation;

    M2 *m_model;
    bool m_modelChanged;
    QString m_modelFileName;
    QHash<quint32, QString> m_textureFileNames;

    QHash<quint32, SpellVisualKit *> m_visualKits;
};

#endif
