/*
 *IGONA POLOKALAME: VaaigaAtulau
 *TUSI-POLOKALAME: SUETENA FAATUUALA LOIA
 *TAUSAGA-TUSI:    2013
 *
 *FAMATALAGA I LE POLOKALAME:
 *      O le nei polokalame e fai ma se fesosoai Mo nisi o tagata samoa o loo fia
 *      faafesotai ma isi tagata o le lalolagi. Ma suesue ai mataupu i manaona o tagata
 *      I mea o loo fia suesue ina.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include "QtCore"
#include "QMessageBox"
#include "settingsdialog.h"
#include "QProgressBar"
#include "QToolBar"
#include "QNetworkProxy"

QProgressBar *loadbar;
QNetworkProxy sockproxy;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QToolBar *addressBarFloat;
    addressBarFloat = new QToolBar("AddressBar",this);
    addressBarFloat->setFloatable(true);
    MainWindow::addToolBar(addressBarFloat);



    ui->setupUi(this);
    on_loadVaaigaAtulau_settings();
    setCentralWidget(ui->webView);
    loadbar = new QProgressBar(statusBar());
    statusBar()->addPermanentWidget(loadbar);
    addressBarFloat->addWidget(ui->AddessBarWidget);

    //This sets the proxy to be used
    /*
     *Note to use setting area to implement this and also pull settings
     *for proxy and other network proxy settings
     *
     *note things to add
     *[1] Add feature to read proxy settings from Windows proxy settings
     *[2] Add feature to have httpproxy support
    */
    //ONLY REMOVE THIS IF ITS IN BETA VERSIONS
    //THIS IS THE PROXY SETTING FOR THE APPLICATION
//            sockproxy.setType(QNetworkProxy::Socks5Proxy);
//            sockproxy.setHostName("127.0.0.1");
//            sockproxy.setPort(7070);
//            QNetworkProxy::setApplicationProxy(sockproxy);
    //This has been implemented in the on_loadVaaigaAtulau_settings() function.

    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::AutoLoadImages,true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){ui->webView->load(QUrl(ui->lineEdit->text()));}
void MainWindow::on_webView_loadProgress(int progress)
{
    loadbar->setValue(progress);
    ui->lineEdit->setText(ui->webView->url().toString());
}

void MainWindow::on_lineEdit_returnPressed(){on_pushButton_clicked();}

void MainWindow::on_actionAmataga_triggered()
{
    on_loadVaaigaAtulau_settings();
    QString urlString = MainWindow::HomeUrlSettingValue;
    ui->lineEdit->setText(urlString);ui->webView->load(QUrl(urlString));
}

void MainWindow::on_actionAluluma_triggered(){
    ui->webView->forward();
}

void MainWindow::on_actionAlutua_triggered(){
    ui->webView->back();
}

void MainWindow::on_actionTapuni_le_Pololalame_triggered(){
    exit(0);
}

void MainWindow::on_actionSeti_le_Polokalame_triggered()
{
    settingsDialog sVaaigaAtulau;
    sVaaigaAtulau.setModal(true);
    sVaaigaAtulau.exec();
}

void MainWindow::on_loadVaaigaAtulau_settings(){

    QSettings thisappsettin("SFMSLDevelopement","VaaigaAtulau");
    thisappsettin.beginGroup("VaaigaAtulauSettings");

    QString HomeURL = thisappsettin.value("homeUrl").toString();
    QString ProxyServerUse = thisappsettin.value("ProxyServer").toString();
    QString ProxyTypeUse   = thisappsettin.value("ProxyType").toString();
    int Enableproxy = thisappsettin.value("EnableProxy").toInt();
    int ProxyPortUse = thisappsettin.value("ProxyPort").toInt();

    thisappsettin.endGroup();

    MainWindow::HomeUrlSettingValue.append(HomeURL);

    if(Enableproxy == 1){
        sockproxy.setHostName(ProxyServerUse);
        sockproxy.setPort(ProxyPortUse);
    }

    if (QString::compare(ProxyTypeUse,"sock5")){
        sockproxy.setType(QNetworkProxy::Socks5Proxy);
        QNetworkProxy::setApplicationProxy(sockproxy);
    }
}

void MainWindow::on_actionFaafou_triggered()
{
    ui->webView->reload();
}
