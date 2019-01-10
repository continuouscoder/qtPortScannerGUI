#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "QDebug"
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->results->setText("");
    QString host = ui ->lineEditHost->text();
    QString startPort = ui ->lineEditStartPort->text();
    quint16 startPortInt = startPort.toUShort();
    QString endPort = ui ->lineEditEndPort->text();
    quint16 endPortInt = endPort.toUShort();
    QString timeout = ui ->lineEditTimeout->text();
    quint16 timeoutInt = timeout.toUShort();
    qInfo() << host;

    QFuture<void> future = QtConcurrent::run([=]() {   // Austin showed me this was how to run the scan in a separate thread from the app.
         QTcpSocket socket;
        // Code in this block will run in another thread
        for(quint16 i = startPortInt; i < endPortInt; i++){

                socket.connectToHost(host, i);
                if(socket.waitForConnected(timeoutInt)){
                    qInfo() << "Open Port: " << i;
                    QString openPort = QString::number(i);
                    ui->results->append("Port: " + openPort);
                    socket.disconnectFromHost();
                    QApplication::processEvents();  // Austin showed me this processed events across blocking thread
                }
        }
        ui->results->append("Scan Complete");
        qInfo() << "Scan Complete";
    });


}

