#ifndef WOVWIDGET_H
#define WOVWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>

class Model;
class ModelScene;
class QLineEdit;
class SpellVisual;

class WovWidget : public QWidget
{
    Q_OBJECT

public:
    WovWidget(QWidget* parent = NULL);

    private slots:
        void addModel();
        void selectCaster();
        void selectTarget();
        void cast();

        void mousePressed(QMouseEvent *event);
        void mouseReleased(QMouseEvent *event);
        void mouseMoved(QMouseEvent *event);
        void wheelRotated(QWheelEvent *event);

private:
    ModelScene *m_scene;

    quint8 m_selection;
    Model *m_drag;

    int m_mouseX, m_mouseY;
    float m_worldX, m_worldY, m_worldZ;

    SpellVisual *m_visual;

    QLineEdit *m_displayEdit;
    QLineEdit *m_visualEdit;
};

#endif
