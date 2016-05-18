#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QTimer>
#include <QMouseEvent>

#include "modelscene.h"
#include "model.h"
#include "particleemitter.h"
#include "camerashake.h"

ModelScene::ModelScene(QWidget *parent) : QOpenGLWidget(parent),
    m_rotationX(0.0f),
    m_rotationY(0.0f),
    m_distance(0.0f),
    m_program(0),
    m_particleProgram(0),
    m_gridBuffer(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);
}

void ModelScene::setRotationX(float rotation)
{
    m_rotationX = rotation;
}

void ModelScene::setRotationY(float rotation)
{
    m_rotationY = rotation;
}

void ModelScene::setDistance(float distance)
{
    m_distance = qMax(0.0f, distance);
}

float ModelScene::rotationX() const
{
    return m_rotationX;
}

float ModelScene::rotationY() const
{
    return m_rotationY;
}

float ModelScene::distance() const
{
    return m_distance;
}

Model * ModelScene::selectedModel()
{
    if (m_selection > 0 && m_selection <= m_models.size())
        return m_models[m_selection - 1];

    return 0;
}

float ModelScene::worldX() const
{
    return m_worldX;
}

float ModelScene::worldY() const
{
    return m_worldY;
}

float ModelScene::worldZ() const
{
    return m_worldZ;
}

void ModelScene::addModel(Model *model)
{
    if (!model)
        return;

    m_models << model;
}

void ModelScene::removeModel(Model *model)
{
    m_models.removeOne(model);
}

void ModelScene::addCameraShake(quint32 id)
{
    m_shakes << new CameraShake(id);
}

void ModelScene::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vs");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.fs");
    m_program->link();

    m_particleProgram = new QOpenGLShaderProgram();
    m_particleProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/particle.vs");
    m_particleProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/particle.fs");
    m_particleProgram->link();

    const GLubyte white[3] = {255, 255, 255};

    glBindTexture(GL_TEXTURE_2D, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, white); 

    m_time.start();
}

void ModelScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    MVP mvp;
    mvp.projection.perspective(32.25, float(width()) / float(height()), 1.0, 100.0);
    mvp.view.lookAt(QVector3D(0.0, 0.0, m_distance) + m_shake, QVector3D(0.0, 0.0, 0.0) + m_shake, QVector3D(0.0, 1.0, 0.0));
    mvp.model.rotate(rotationY(), 1.0, 0.0, 0.0);
    mvp.model.rotate(rotationX(), 0.0, 1.0, 0.0);
    mvp.model.rotate(-90, 1.0, 0.0, 0.0);

    m_program->bind();

    m_program->setUniformValue("light.position", QVector3D(0.0, 0.0, 1.0));
    m_program->setUniformValue("light.ambient", QVector4D(0.5, 0.5, 0.5, 1.0));
    m_program->setUniformValue("light.diffuse", QVector4D(1.0, 1.0, 1.0, 1.0));

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (int i = 0; i < m_models.size(); i++) {
        glStencilFunc(GL_ALWAYS, i + 1, ~0);

        if (m_selection == i + 1)
            m_program->setUniformValue("light.ambient", QVector4D(1.0, 1.0, 1.0, 1.0));
        else
            m_program->setUniformValue("light.ambient", QVector4D(0.5, 0.5, 0.5, 1.0));

        m_models[i]->render(m_program, mvp);
    }

    glDisable(GL_STENCIL_TEST);

    glReadPixels(m_mouseX, height() - m_mouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &m_selection);

    m_program->release();

    m_particleProgram->bind();

    for (int i = 0; i < m_models.size(); i++)
        m_models[i]->renderParticles(m_particleProgram, mvp);

    renderGrid(31, 1.0f, mvp);

    m_particleProgram->release();

    updateMouseCoordinates(mvp);
}

void ModelScene::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void ModelScene::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

void ModelScene::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}

void ModelScene::mouseMoveEvent(QMouseEvent *event)
{
    m_mouseX = event->x();
    m_mouseY = event->y();

    emit mouseMoved(event);
}

void ModelScene::wheelEvent(QWheelEvent *event)
{
    emit wheelRotated(event);
}

void ModelScene::update()
{
    int timeDelta = m_time.restart();

    for (int i = 0; i < m_models.size(); i++)
        m_models[i]->update(timeDelta);

    m_shake = QVector3D();

    for (int i = 0; i < m_shakes.size();) {
        if (m_shakes[i]->update(timeDelta)) {
            m_shake += m_shakes[i++]->getShake();
        } else {
            delete m_shakes[i];
            m_shakes.removeAt(i);
        }
    }

    //updateGL();
}

void ModelScene::renderGrid(int size, float step, MVP mvp)
{
    if (!m_gridBuffer) {
        ParticleVertex *vertices = new ParticleVertex[4 * size];

        for (int i = 0; i < size; i++) {
            ParticleVertex &v1 = vertices[4 * i + 0];
            ParticleVertex &v2 = vertices[4 * i + 1];
            ParticleVertex &v3 = vertices[4 * i + 2];
            ParticleVertex &v4 = vertices[4 * i + 3];

            v1.setPosition(QVector3D(i * step, 0.0f, 0.0f));
            v2.setPosition(QVector3D(i * step, (size - 1) * step, 0.0f));
            v3.setPosition(QVector3D(0.0f, i * step, 0.0f));
            v4.setPosition(QVector3D((size - 1) * step, i * step, 0.0f));

            QVector4D color(0.8f, 0.8f, 0.8f, 1.0f);
            v1.setColor(color);
            v2.setColor(color);
            v3.setColor(color);
            v4.setColor(color);

            QVector2D texcoord(0.0f, 0.0f);
            v1.setTexcoord(texcoord);
            v2.setTexcoord(texcoord);
            v3.setTexcoord(texcoord);
            v4.setTexcoord(texcoord);
        }

        m_gridBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_gridBuffer->create();
        m_gridBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_gridBuffer->bind();
        m_gridBuffer->allocate(vertices, 4 * size * sizeof(ParticleVertex));
        m_gridBuffer->release();

        delete[] vertices;
    }

    mvp.model.translate(-step * (size >> 1), -step * (size >> 1), 0.0f);

    m_particleProgram->setUniformValue("mvpMatrix", mvp.getMVPMatrix());

    glBindTexture(GL_TEXTURE_2D, 0);

    m_gridBuffer->bind();

    m_particleProgram->enableAttributeArray("position");
    m_particleProgram->setAttributeBuffer("position", GL_FLOAT, 0, 3, sizeof(ParticleVertex));

    m_particleProgram->enableAttributeArray("color");
    m_particleProgram->setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(float), 4, sizeof(ParticleVertex));

    m_particleProgram->enableAttributeArray("texcoord");
    m_particleProgram->setAttributeBuffer("texcoord", GL_FLOAT, 7 * sizeof(float), 2, sizeof(ParticleVertex));

    glDrawArrays(GL_LINES, 0, 4 * size);

    m_particleProgram->disableAttributeArray("position");
    m_particleProgram->disableAttributeArray("color");
    m_particleProgram->disableAttributeArray("texcoord");

    m_gridBuffer->release();
}

void ModelScene::updateMouseCoordinates(MVP mvp)
{
    float screenX = 2.0f * m_mouseX / width() - 1.0f;
    float screenY = 1.0f - 2.0f * m_mouseY / height();

    QVector4D ray0(screenX, screenY, -1.0f, 1.0f);
    QVector4D ray1(screenX, screenY,  1.0f, 1.0f);

    QMatrix4x4 invertedMVP = mvp.getMVPMatrix().inverted();

    ray0 = invertedMVP * ray0;
    ray1 = invertedMVP * ray1;

    if (ray0.w() == 0.0f)
        ray0 = QVector4D();
    else
        ray0 /= ray0.w();

    if (ray1.w() == 0.0f)
        ray1 = QVector4D();
    else
        ray1 /= ray1.w();

    QVector4D ray = (ray1 - ray0).normalized();
    QVector4D normal(0.0f, 0.0f, 1.0f, 0.0f);
    QVector4D plane(0.0f, 0.0f, 0.0f, 1.0f);

    float t = QVector4D::dotProduct(normal, plane - ray0) / QVector4D::dotProduct(normal, ray);

    QVector4D point = ray0 + t * ray;

    m_worldX = point.x();
    m_worldY = point.y();
    m_worldZ = point.z();
}
