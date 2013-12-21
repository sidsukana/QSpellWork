#ifndef ANIMATED_VALUE_H
#define ANIMATED_VALUE_H

#include <QList>
#include <QPair>
#include <QQuaternion>
#include <QDateTime>

enum InterpolationType {
    INTERPOLATION_NONE,
    INTERPOLATION_LINEAR,
    INTERPOLATION_HERMITE
};

template <class T>
inline T getKey(const char *data, quint32 index)
{
    const T *values = reinterpret_cast<const T *>(data);

    return values[index];
}

template <>
inline QVector3D getKey(const char *data, quint32 index)
{
    const float *values = reinterpret_cast<const float *>(data);

    return QVector3D(values[3 * index], values[3 * index + 1], values[3 * index + 2]);
}

template <>
inline QQuaternion getKey(const char *data, quint32 index)
{
    const float *values = reinterpret_cast<const float *>(data);

    return QQuaternion(values[4 * index + 3], values[4 * index], values[4 * index + 1], values[4 * index + 2]);
}

template <class T>
class AnimatedValue
{
public:
    AnimatedValue(const M2AnimationBlock &animation, const quint32 *sequences, const QByteArray &data)
    {
        m_type = animation.type;

        if (animation.sequence != -1)
            m_sequenceTime = sequences[animation.sequence];
        else
            m_sequenceTime = -1;

        if (animation.rangesCount) {
            const quint32 *ranges = reinterpret_cast<const quint32 *>(data.data() + animation.rangesOffset);

            for (quint32 i = 0; i < animation.rangesCount; i++)
                m_ranges << qMakePair(ranges[i * 2 + 0], ranges[i * 2 + 1]);
        } else {
            m_ranges << qMakePair(quint32(0), animation.keysCount - 1);
        }

        const qint32 *times = reinterpret_cast<const qint32 *>(data.data() + animation.timesOffset);

        for (quint32 i = 0; i < animation.timesCount; i++)
            m_times << times[i];

        const char *keys = data.data() + animation.keysOffset;

        switch (m_type) {
            case INTERPOLATION_NONE:
            case INTERPOLATION_LINEAR:
                for (quint32 i = 0; i < animation.keysCount; i++)
                    m_keys << getKey<T>(keys, i);

                break;
            case INTERPOLATION_HERMITE:
                for (quint32 i = 0; i < animation.keysCount; i++) {
                    m_keys << getKey<T>(keys, 3 * i);
                    m_in << getKey<T>(keys, 3 * i + 1);
                    m_out << getKey<T>(keys, 3 * i + 2);
                }

                break;
        }
    }

    bool isValid() {
        return !m_keys.isEmpty();
    }

    T getValue(quint32 animation, qint32 time) {
        if (!isValid())
            return T();

        if (m_type == INTERPOLATION_NONE && m_keys.size() == 1)
            return m_keys[0];

        if (m_sequenceTime != -1) {
            animation = 0;

            if (m_sequenceTime == 0)
                time = 0;
            else
                time = QDateTime::currentMSecsSinceEpoch() % m_sequenceTime;
        }

        QPair<quint32, quint32> range = m_ranges[animation];

        if (range.first == range.second)
            return m_keys[range.first];

        quint32 interval = 0;

        for (quint32 i = range.first; i < range.second; i++) {
            if (m_times[i] <= time && time < m_times[i + 1]) {
                interval = i;
                break;
            }
        }

        float t = 0.0f;

        if (time >= m_times[interval])
            t = float(time - m_times[interval]) / float(m_times[interval + 1] - m_times[interval]);

        if (t >= 1.0f)
            t = 1.0f;

        switch (m_type) {
            default:
            case INTERPOLATION_NONE:
                return m_keys[interval];
            case INTERPOLATION_LINEAR:
                return m_keys[interval] * (1.0f - t) + m_keys[interval + 1] * t;
            case INTERPOLATION_HERMITE:
                // TODO implement
                return m_keys[interval];
        }
    }

private:
    quint16 m_type;
    qint32 m_sequenceTime;
    QList<QPair<quint32, quint32> > m_ranges;
    QList<qint32> m_times;
    QList<T> m_keys;
    QList<T> m_in, m_out;
};

#endif
