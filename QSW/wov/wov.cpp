#include <math.h>

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include "wov.h"
#include "modelscene.h"
#include "spellvisual.h"

WovWidget::WovWidget(QWidget* parent) : QWidget(parent), m_selection(0), m_drag(0),  m_visual(0)
{
    m_scene = new ModelScene;
    m_scene->setRotationX(-45.0f);
    m_scene->setRotationY(20.0f);
    m_scene->setDistance(20.0f);

    m_visual = new SpellVisual();

    m_displayEdit = new QLineEdit(this);
    m_displayEdit->setPlaceholderText("Display ID");

    QPushButton *addButton = new QPushButton("Add", this);

    m_visualEdit = new QLineEdit(this);
    m_visualEdit->setPlaceholderText("Visual");

    QPushButton *casterButton = new QPushButton("Set caster", this);
    QPushButton *targetButton = new QPushButton("Set target", this);
    QPushButton *castButton = new QPushButton("Cast", this);

    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(m_displayEdit);
    controlLayout->addWidget(addButton);
    controlLayout->addWidget(m_visualEdit);
    controlLayout->addWidget(casterButton);
    controlLayout->addWidget(targetButton);
    controlLayout->addWidget(castButton);
    controlLayout->addStretch(1);

    QGroupBox *controlBox = new QGroupBox("Model Control");
    controlBox->setLayout(controlLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(controlBox);
    layout->addWidget(m_scene);

    setLayout(layout);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addModel()));
    connect(casterButton, SIGNAL(clicked()), this, SLOT(selectCaster()));
    connect(targetButton, SIGNAL(clicked()), this, SLOT(selectTarget()));
    connect(castButton, SIGNAL(clicked()), this, SLOT(cast()));

    connect(m_scene, SIGNAL(mousePressed(QMouseEvent *)), this, SLOT(mousePressed(QMouseEvent *)));
    connect(m_scene, SIGNAL(mouseReleased(QMouseEvent *)), this, SLOT(mouseReleased(QMouseEvent *)));
    connect(m_scene, SIGNAL(mouseMoved(QMouseEvent *)), this, SLOT(mouseMoved(QMouseEvent *)));
    connect(m_scene, SIGNAL(wheelRotated(QWheelEvent *)), this, SLOT(wheelRotated(QWheelEvent *)));
}

void WovWidget::addModel()
{
    Model *model = new Model(m_scene);
    model->setDisplayId(m_displayEdit->text().toUInt());
    m_scene->addModel(model);
}

void WovWidget::selectCaster()
{
    m_selection |= 0x1;
}

void WovWidget::selectTarget()
{
    m_selection |= 0x2;
}

void WovWidget::cast()
{
    m_visual->setVisual(m_visualEdit->text().toUInt());
    m_visual->start();
}

void WovWidget::mousePressed(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_drag = m_scene->selectedModel();
}

void WovWidget::mouseReleased(QMouseEvent *event)
{
    Model *model = m_scene->selectedModel();

    if (event->button() == Qt::LeftButton) {
        if (m_selection & 0x1)
            m_visual->setCaster(model);

        if (m_selection & 0x2)
            m_visual->setTarget(model);

        m_selection = 0;
    } else if (event->button() == Qt::RightButton) {
        m_scene->removeModel(model);
    }

    m_drag = 0;
}

void WovWidget::mouseMoved(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (m_drag) {
            float x = m_drag->x() + m_scene->worldX() - m_worldX;
            float y = m_drag->y() + m_scene->worldY() - m_worldY;

            if (fabs(x) <= 10.0f)
                m_drag->setX(x);

            if (fabs(y) <= 10.0f)
                m_drag->setY(y);
        } else {
            m_scene->setRotationX(m_scene->rotationX() + 360.0f * (event->x() - m_mouseX) / width());
            m_scene->setRotationY(m_scene->rotationY() + 360.0f * (event->y() - m_mouseY) / height());
        }
    }

    m_mouseX = event->x();
    m_mouseY = event->y();

    m_worldX = m_scene->worldX();
    m_worldY = m_scene->worldY();
    m_worldZ = m_scene->worldZ();
}

void WovWidget::wheelRotated(QWheelEvent *event)
{
    if (m_drag)
        m_drag->setOrientation(m_drag->orientation() + event->delta() / 8.0f);
    else
        m_scene->setDistance(m_scene->distance() - event->delta() / 120.0f);
}
