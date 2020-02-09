#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QMap>
#include <QSharedPointer>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = nullptr);

    quint16 createNewProcess(QString program, QStringList args);

signals:
    void newProcessData(quint16 processID, QByteArray output);

public slots:
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void handleNewDataAvailable();

private:
    quint16 m_idIndex;
    QThread m_thread;
    QMap<quint16, QSharedPointer<QProcess>> m_processes;
};

#endif // PROCESSMANAGER_H
