#ifndef NUEVATAREA_H
#define NUEVATAREA_H

#include <QDebug>
#include <QObject>
#include <QRunnable>

class nuevaTarea:public QObject, public QRunnable
{
    Q_OBJECT
public:
    nuevaTarea();

    signals:
        void Resultado(int numero);

protected:
    void run();
};

#endif // NUEVATAREA_H
