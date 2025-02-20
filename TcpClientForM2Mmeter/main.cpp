#include "TcpClient.h"
#include <QCoreApplication>
#include <QtConcurrent>

#include <QFuture>

QString ip = "172.16.64.";

int ipFour = 0;
quint16 port = 8888;

void connection(TcpClient* any)
{
	

	any->connectToServer(ip + QString::number(ipFour++), port);


};

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	//TcpClient client;



	QList<TcpClient*>tcpMassive;
	
	for (int counter = 0; counter != 5; counter++)
	{
		tcpMassive.push_back(new TcpClient());
	}

	//QFuture<void> future = QtConcurrent::run(TcpClient::connectToServer, );

	QFuture<void> future = QtConcurrent::map(tcpMassive, connection);

	future.waitForFinished();

	return a.exec();
}