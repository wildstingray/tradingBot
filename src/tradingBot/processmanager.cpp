#include "processmanager.h"

ProcessManager::ProcessManager(QObject *parent) : QObject(parent)
{
    m_thread.start();
    m_idIndex = 0;
}

quint16 ProcessManager::createNewProcess(QString program, QStringList args)
{
    if (program.isEmpty())
        return 0;

    QSharedPointer<QProcess> process(new QProcess);
    process->setProcessChannelMode(QProcess::MergedChannels);
//    process->moveToThread(&m_thread);
    connect(&m_thread, &QThread::finished, process.data(), &QObject::deleteLater);
    connect(process.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &ProcessManager::handleProcessFinished);
    connect(process.data(), &QProcess::readyRead, this, &ProcessManager::handleNewDataAvailable);

    process->start(program, args);

    m_idIndex++;
    m_processes.insert(m_idIndex, process);
    return m_idIndex;
}

void ProcessManager::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode)
    Q_UNUSED(exitStatus)
    handleNewDataAvailable();
}

void ProcessManager::handleNewDataAvailable()
{
    QMap<quint16, QSharedPointer<QProcess>>::iterator it = m_processes.begin();
    QList<quint16> keysToBeRemoved;

    while (it != m_processes.end())
    {
        QByteArray output = it.value()->readAllStandardOutput();
        emit newProcessData(it.key(), output);

        if (it.value()->state() == QProcess::NotRunning)
        {
            keysToBeRemoved.append(it.key());
        }

        it++;
    }

    for (int i = 0; i < keysToBeRemoved.length(); i++)
    {
        m_processes.remove(keysToBeRemoved.at(i));
    }
}
