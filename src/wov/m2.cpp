#include <QUrl>
#include <QRegularExpression>>

#include "m2.h"
#include "wovdbc.h"
#include "mpq/MPQ.h"

M2::M2(const QString &fileName, QOpenGLFunctions* funcs)
    : m_loaded(false),
      m_initialized(false),
      m_animating(true),
      m_animation(0),
      m_time(0),
      m_animationState(-1),
      m_animationOneshot(-1),
      m_funcs(funcs)
{
    m_data = MPQ::readFile(fileName);

    if (m_data.size() == 0) {
        qCritical("Cannot load model '%s'", qPrintable(fileName));
        return;
    }

    m_header = reinterpret_cast<M2Header *>(m_data.data());

    if (strncmp(m_header->magic, M2_MAGIC, 4) != 0) {
        qCritical("File '%s' is not a valid M2 file!", qPrintable(fileName));
        return;
    }

    m_sequences = reinterpret_cast<quint32 *>(m_data.data() + m_header->sequencesOffset);

    m_vertices = reinterpret_cast<M2Vertex *>(m_data.data() + m_header->verticesOffset);

    m_views = reinterpret_cast<M2View *>(m_data.data() + m_header->viewsOffset);

    quint16 *indices = reinterpret_cast<quint16 *>(m_data.data() + m_views[0].indicesOffset);
    quint16 *triangles = reinterpret_cast<quint16 *>(m_data.data() + m_views[0].trianglesOffset);

    m_indicesCount = m_views[0].trianglesCount;
    m_indices = new quint16[m_indicesCount];

    for (quint32 i = 0; i < m_indicesCount; i++)
        m_indices[i] = indices[triangles[i]];

    m_submeshes = reinterpret_cast<M2Submesh *>(m_data.data() + m_views[0].submeshOffset);
    m_textureUnits = reinterpret_cast<M2TextureUnit *>(m_data.data() + m_views[0].textureUnitsOffset);

    m_renderFlags = reinterpret_cast<M2RenderFlags *>(m_data.data() + m_header->renderFlagsOffset);

    m_textureLookup = reinterpret_cast<quint16 *>(m_data.data() + m_header->textureLookupOffset);

    M2Texture *textures = reinterpret_cast<M2Texture *>(m_data.data() + m_header->texturesOffset);

    for (quint32 i = 0; i < m_header->texturesCount; i++) {
        QString fileName(m_data.data() + textures[i].fileNameOffset);

        m_textures << new Texture(m_funcs);

        if (textures[i].type == 0)
            m_textures[i]->load(fileName);
    }

    m_textureAnimationLookup = reinterpret_cast<qint16 *>(m_data.data() + m_header->textureAnimationLookupOffset);

    M2TextureAnimation *textureAnimations = reinterpret_cast<M2TextureAnimation *>(m_data.data() + m_header->textureAnimationsOffset);

    for (quint32 i = 0; i < m_header->textureAnimationsCount; i++)
        m_textureAnimations << TextureAnimation(textureAnimations[i], m_sequences, m_data);

    m_replaceableTextures = reinterpret_cast<qint16 *>(m_data.data() + m_header->textureReplaceOffset);

    M2Bone *bones = reinterpret_cast<M2Bone *>(m_data.data() + m_header->bonesOffset);

    for (quint32 i = 0; i < m_header->bonesCount; i++)
        m_bones << Bone(bones[i], m_sequences, m_data);

    for (quint32 i = 0; i < m_header->bonesCount; i++) {
        if (bones[i].parent != -1)
            m_bones[i].parent = &m_bones[bones[i].parent];
    }

    m_animations = reinterpret_cast<M2Animation *>(m_data.data() + m_header->animationsOffset);

    qint16 *animationsLookup = reinterpret_cast<qint16 *>(m_data.data() + m_header->animationLookupOffset);

    for (quint32 i = 0; i < m_header->animationLookupCount; i++) {
        if (animationsLookup[i] != -1)
            m_animationsLookup[i] = animationsLookup[i];
    }

    M2Color *colors = reinterpret_cast<M2Color *>(m_data.data() + m_header->colorsOffset);

    for (quint32 i = 0; i < m_header->colorsCount; i++) {
        m_colors << AnimatedValue<QVector3D>(colors[i].color, m_sequences, m_data);
        m_opacities << AnimatedValue<quint16>(colors[i].opacity, m_sequences, m_data);
    }

    m_transparencyLookup = reinterpret_cast<qint16 *>(m_data.data() + m_header->transparencyLookupOffset);

    M2AnimationBlock *transparencies = reinterpret_cast<M2AnimationBlock *>(m_data.data() + m_header->transparencyOffset);

    for (quint32 i = 0; i < m_header->transparencyCount; i++)
        m_transparencies << AnimatedValue<quint16>(transparencies[i], m_sequences, m_data);

    M2Attachment *attachments = reinterpret_cast<M2Attachment *>(m_data.data() + m_header->attachmentsOffset);

    qint16 *attachmentLookup = reinterpret_cast<qint16 *>(m_data.data() + m_header->attachmentLookupOffset);

    for (quint32 i = 0; i < m_header->attachmentLookupCount; i++) {
        if (attachmentLookup[i] != -1)
            m_attachments[i] = &attachments[attachmentLookup[i]];
    }

    M2RibbonEmitter *ribbonEmitters = reinterpret_cast<M2RibbonEmitter *>(m_data.data() + m_header->ribbonEmittersOffset);

    for (quint32 i = 0; i < m_header->ribbonEmittersCount; i++)
        m_ribbonEmitters << new RibbonEmitter(ribbonEmitters[i], m_sequences, m_data, m_funcs);

    M2ParticleEmitter *particleEmitters = reinterpret_cast<M2ParticleEmitter *>(m_data.data() + m_header->particleEmittersOffset);

    for (quint32 i = 0; i < m_header->particleEmittersCount; i++)
        m_particleEmitters << new ParticleEmitter(particleEmitters[i], m_sequences, m_data, m_funcs);

    m_loaded = true;
}

void M2::initialize()
{
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(m_vertices, m_header->verticesCount * sizeof(M2Vertex));
    m_vertexBuffer->release();

    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer->bind();
    m_indexBuffer->allocate(m_indices, m_indicesCount * sizeof(GLushort)); 
    m_indexBuffer->release();

    m_initialized = true;
}

void M2::bindBuffers(QOpenGLShaderProgram *program)
{
    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    int offset = 0;

    program->enableAttributeArray("position");
    program->setAttributeBuffer("position", GL_FLOAT, offset, 3, sizeof(M2Vertex));

    offset += 3 * sizeof(float);

    program->enableAttributeArray("boneweights");
    program->setAttributeBuffer("boneweights", GL_UNSIGNED_BYTE, offset, 4, sizeof(M2Vertex));

    offset += 4 * sizeof(quint8);

    program->enableAttributeArray("boneindices");
    program->setAttributeBuffer("boneindices", GL_UNSIGNED_BYTE, offset, 4, sizeof(M2Vertex));

    offset += 4 * sizeof(quint8);

    program->enableAttributeArray("normal");
    program->setAttributeBuffer("normal", GL_FLOAT, offset, 3, sizeof(M2Vertex));

    offset += 3 * sizeof(float);

    program->enableAttributeArray("texcoord");
    program->setAttributeBuffer("texcoord", GL_FLOAT, offset, 2, sizeof(M2Vertex));
}

void M2::releaseBuffers(QOpenGLShaderProgram *program)
{
    program->disableAttributeArray("position");
    program->disableAttributeArray("boneweights");
    program->disableAttributeArray("boneindices");
    program->disableAttributeArray("normal");
    program->disableAttributeArray("texcoord");

    m_vertexBuffer->release();
    m_indexBuffer->release();
}

void M2::render(QOpenGLShaderProgram *program, MVP mvp)
{
    if (!m_loaded)
        return;

    if (!m_initialized)
        initialize();

    program->setUniformValue("mvpMatrix", mvp.getMVPMatrix());
    program->setUniformValue("normalMatrix", mvp.getNormalMatrix());

    QMatrix4x4 *boneMatrices = new QMatrix4x4[m_bones.size()];

    for (int i = 0; i < m_bones.size(); i++)
        boneMatrices[i] = m_bones[i].getMatrix(m_animation, m_time, mvp);

    program->setUniformValueArray("bones", boneMatrices, m_bones.size());

    delete[] boneMatrices;

    bindBuffers(program);

    //glAlphaFunc(GL_GREATER, 0.3f);
    m_funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (quint32 i = 0; i < m_views[0].textureUnitsCount; i++) {
        M2RenderFlags flags = m_renderFlags[m_textureUnits[i].renderFlagIndex];

        switch (flags.blending) {
            case BM_OPAQUE:
                m_funcs->glDisable(GL_BLEND);
                m_funcs->glDisable(GL_ALPHA_TEST);
                break;
            case BM_TRANSPARENT:
                m_funcs->glDisable(GL_BLEND);
                m_funcs->glEnable(GL_ALPHA_TEST);
                break;
            case BM_ALPHA_BLEND:
                m_funcs->glEnable(GL_BLEND);
                m_funcs->glDisable(GL_ALPHA_TEST);
                break;
            case BM_ADDITIVE:
                m_funcs->glEnable(GL_BLEND);
                m_funcs->glBlendFunc(GL_SRC_COLOR, GL_ONE);
                m_funcs->glDisable(GL_ALPHA_TEST);
                break;
            case BM_ADDITIVE_ALPHA:
                m_funcs->glEnable(GL_BLEND);
                m_funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                m_funcs->glDisable(GL_ALPHA_TEST);
                break;
            case BM_MODULATE:
            default:
                m_funcs->glEnable(GL_BLEND);
                m_funcs->glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
                m_funcs->glDisable(GL_ALPHA_TEST);
                break;
        }

        bool lighting = (flags.flags & RENDER_FLAG_UNLIT) == 0;

        if (flags.flags & RENDER_FLAG_TWO_SIDED)
            m_funcs->glDisable(GL_CULL_FACE);
        else
            m_funcs->glEnable(GL_CULL_FACE);

        if (flags.flags & RENDER_FLAG_NO_Z_WRITE)
            m_funcs->glDepthMask(GL_FALSE);
        else
            m_funcs->glDepthMask(GL_TRUE);

        m_textures[m_textureLookup[m_textureUnits[i].textureIndex]]->bind();

        QMatrix4x4 textureMatrix;

        qint16 textureAnimation = m_textureAnimationLookup[m_textureUnits[i].textureAnimationId];

        if (textureAnimation != -1 && animating())
            textureMatrix = m_textureAnimations[textureAnimation].getMatrix(m_animation, m_time);

        program->setUniformValue("textureMatrix", textureMatrix);

        float opacity = 1.0f;
        QVector4D emission;

        qint16 colorIndex = m_textureUnits[i].colorIndex;

        if (colorIndex != -1) {
            QVector3D c = m_colors[colorIndex].getValue(m_animation, m_time);
            float o = m_opacities[colorIndex].getValue(m_animation, m_time) / 32767.0f;

            opacity = 0.0f;
            emission = QVector4D(c, o);
        }

        qint16 transparency = m_transparencyLookup[m_textureUnits[i].transparencyIndex];

        if (transparency != -1) {
            float t = m_transparencies[transparency].getValue(m_animation, m_time) / 32767.0f;

            opacity *= t;
            emission.setW(emission.w() * t);
        }

        program->setUniformValue("material.opacity", opacity);
        program->setUniformValue("material.emission", emission);

        program->setUniformValue("lighting", lighting);

        quint32 submesh = m_textureUnits[i].submeshIndex;

        m_funcs->glDrawElements(GL_TRIANGLES, m_submeshes[submesh].trianglesCount, GL_UNSIGNED_SHORT, (const GLvoid *)(m_submeshes[submesh].startingTriangle * sizeof(GLushort)));
    }

    m_funcs->glDepthMask(GL_TRUE);

    //glAlphaFunc(GL_ALWAYS, 0.0f);
    m_funcs->glBlendFunc(GL_ONE, GL_ZERO);

    releaseBuffers(program);

    renderAttachments(program, mvp);
}

void M2::renderParticles(QOpenGLShaderProgram *program, MVP viewProjection)
{
    for (int i = 0; i < m_ribbonEmitters.size(); i++) {
        qint32 texture = m_ribbonEmitters[i]->getTextureId();

        if (texture != -1)
            m_textures[texture]->bind();

        m_ribbonEmitters[i]->render(program, viewProjection);
    }

    for (int i = 0; i < m_particleEmitters.size(); i++) {
        qint16 texture = m_particleEmitters[i]->getTextureId();

        if (texture != -1)
            m_textures[texture]->bind();

        m_particleEmitters[i]->render(program, viewProjection);
    }

    renderAttachmentsParticles(program, viewProjection);
}

void M2::renderAttachments(QOpenGLShaderProgram *program, MVP mvp)
{
    QMultiHash<quint32, M2 *>::iterator it = m_attachedModels.begin();

    while (it != m_attachedModels.end()) {
        float *position = m_attachments[it.key()]->position;
        qint32 bone = m_attachments[it.key()]->bone;

        MVP attachmentMVP = mvp;

        if (bone >= 0 && bone < m_bones.size())
            attachmentMVP.model *= m_bones[bone].getMatrix(m_animation, m_time, mvp);

        attachmentMVP.model.translate(position[0], position[1], position[2]);

        it.value()->render(program, attachmentMVP);
        it++;
    }
}

void M2::renderAttachmentsParticles(QOpenGLShaderProgram *program, MVP viewProjection)
{
    QMultiHash<quint32, M2 *>::iterator it = m_attachedModels.begin();

    while (it != m_attachedModels.end()) {
        it.value()->renderParticles(program, viewProjection);
        it++;
    }
}

void M2::update(int timeDelta, QMatrix4x4 model)
{
    if (!m_initialized)
        return;

    if (animating() && animation() != -1) {
        m_time += timeDelta;

        if (m_time >= m_animations[m_animation].endTime) {
            if (m_animationOneshot != -1) {
                m_animationOneshot = -1;
                switchAnimation();
            } else {
                if (m_animations[m_animation].flags & ANIMATION_STOP_AT_END)
                    m_time = m_animations[m_animation].endTime - 1;
                else
                    switchAnimation();
            }
        }

        updateEmitters(timeDelta, model);
    }

    updateAttachments(timeDelta, model);
}

void M2::updateEmitters(int timeDelta, QMatrix4x4 model)
{
    for (int i = 0; i < m_ribbonEmitters.size(); i++) {
        qint32 bone = m_ribbonEmitters[i]->getBoneId();
        QMatrix4x4 boneMatrix;
        if (bone != -1)
            boneMatrix = m_bones[bone].getMatrix(m_animation, m_time, MVP());

        m_ribbonEmitters[i]->update(m_animation, m_time, model * boneMatrix);
    }

    for (int i = 0; i < m_particleEmitters.size(); i++) {
        qint16 bone = m_particleEmitters[i]->getBoneId();
        QMatrix4x4 boneMatrix;
        if (bone != -1)
            boneMatrix = m_bones[bone].getMatrix(m_animation, m_time, MVP());

        m_particleEmitters[i]->update(m_animation, m_time, timeDelta / 1000.0f, model * boneMatrix);
    }
}

void M2::updateAttachments(int timeDelta, QMatrix4x4 model)
{
    QMultiHash<quint32, M2 *>::iterator it = m_attachedModels.begin();

    while (it != m_attachedModels.end()) {
        QMatrix4x4 matrix = model;

        float *position = m_attachments[it.key()]->position;
        qint32 bone = m_attachments[it.key()]->bone;

        if (bone >= 0 && bone < m_bones.size())
            matrix *= m_bones[bone].getMatrix(m_animation, m_time, MVP());

        matrix.translate(position[0], position[1], position[2]);

        it.value()->setAnimating(animating());
        it.value()->update(timeDelta, matrix);
        it++;
    }
}

void M2::setAnimation(qint32 animation, bool forceOneshot)
{
    if (!m_loaded)
        return;

    if (animation == -1) {
        m_animationState = -1;
        return;
    }

    qint16 id = m_animationsLookup.value(animation, -1);
    if (id == -1)
        return;

    quint32 flags = m_animations[id].flags;

    if (forceOneshot || ((flags & ANIMATION_NO_LOOP) && !(flags & ANIMATION_STOP_AT_END)))
        m_animationOneshot = animation;
    else
        m_animationState = animation;

    switchAnimation();
}

void M2::switchAnimation()
{
    if (animation() == -1)
        return;

    m_animation = m_animationsLookup.value(animation());

    quint16 roll = rand() % 0x7FFF;

    while (m_animations[m_animation].nextAnimation != -1 && m_animations[m_animation].chance < roll) {
        roll -= m_animations[m_animation].chance;
        m_animation = m_animations[m_animation].nextAnimation;
    }

    m_time = m_animations[m_animation].startTime;
}

qint32 M2::animation() const
{
    if (m_animationOneshot != -1)
        return m_animationOneshot;
    else
        return m_animationState;
}

void M2::setAnimating(bool animating)
{
    m_animating = animating;
}

bool M2::animating() const
{
    return m_animating;
}

void M2::setTexture(quint32 type, QString fileName)
{
    if (!m_loaded)
        return;

    if (type >= m_header->textureReplaceCount || m_replaceableTextures[type] == -1)
        return;

    m_textures[m_replaceableTextures[type]]->load(fileName);
}

bool M2::attachModel(quint32 attachmentId, M2 *model)
{
    if (!m_attachments.contains(attachmentId))
        return false;

    m_attachedModels.insert(attachmentId, model);

    return true;
}

bool M2::detachModel(quint32 attachmentId, M2 *model)
{
    QMultiHash<quint32, M2 *>::iterator it = m_attachedModels.find(attachmentId, model);

    if (it != m_attachedModels.end()) {
        m_attachedModels.erase(it);

        return true;
    }

    return false;
}
