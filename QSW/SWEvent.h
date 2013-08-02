#ifndef EVENT_H
#define EVENT_H

#include <QtCore/QEvent>
#include <QtCore/QVariant>
#include <QtCore/QVector>

class Event : public QEvent
{
    public:
        enum Events
        {
            EVENT_SEND_SPELL  = QEvent::User + 1,
            EVENT_SEND_MODEL  = QEvent::User + 2,
            EVENT_SEND_CSPELL = QEvent::User + 3,
            EVENT_SEND_TEXT   = QEvent::User + 4,
            EVENT_SEND_ACTION = QEvent::User + 5
        };
        Event(QEvent::Type type) : QEvent(type) {}
        ~Event() {};

        void addValue(const QVariant& value) { m_values << value; }

        QVariant getValue(int index) const
        {
            if (m_values.isEmpty() ||
                m_values.size() - 1 < index)
                return QVariant();

            return m_values[index];
        }

        int getCount() const { return m_values.size(); }

    private:
        QVector<QVariant> m_values;
};

#endif // EVENTMGR_H
