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


	QList<QFuture<void>>futMassive;

	for (int val = 0; val < tcpMassive.length(); val++)
	{

	    futMassive.push_back(QtConcurrent::run(connection, futMassive[val]));


	}

	for (auto& future : futMassive) {
		future.waitForFinished();
	}

	//QFuture<void> future = QtConcurrent::map(tcpMassive.begin(), tcpMassive.end(), connection);

	//future.waitForFinished();




	return a.exec();
}