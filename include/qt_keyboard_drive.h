# pragma once
#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QDebug>

class KeyboardEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = (QKeyEvent*)(event);
            int key = keyEvent->key();
            int modifiers = keyEvent->modifiers();
            // Do something with the key press event
            qDebug() << "Key pressed: " << key << ", Modifiers: " << modifiers;
            // Return true to stop event propagation
            return true;
        }
        else
        {
            // Return false to allow other events to be processed
            return QObject::eventFilter(obj, event);
        }
    }
};
