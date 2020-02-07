#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = nullptr);

signals:

};

#endif // PROCESSMANAGER_H
