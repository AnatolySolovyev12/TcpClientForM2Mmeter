#include "TcpClient.h"
#include <QCoreApplication>
#include <QtConcurrent>
#include <QFuture>
#include <QThread>

QString ip = "172.16.64.";
quint16 port = 8888;

void connection(TcpClient* client, int id)
{
    client->connectToServer(ip + QString::number(id), port);
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QList<TcpClient*> tcpMassive;
    QList<QFuture<void>> futMassive;

    for (int counter = 0; counter < 5; counter++)
    {
        TcpClient* client = new TcpClient(nullptr); // ������� TcpClient ��� ��������
        QThread* thread = new QThread(); // ������� ����� �����
        client->moveToThread(thread); // ���������� TcpClient � ����� �����

        // ���������� ������ ���������� ������ � �������� �������
        QObject::connect(thread, &QThread::finished, client, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        // ��������� �����
        thread->start();

        // ��������� ���������� � ����� ������
        futMassive.push_back(QtConcurrent::run(connection, client, counter));
    }

    for (auto& future : futMassive) {
        future.waitForFinished();
    }

    return a.exec();
}