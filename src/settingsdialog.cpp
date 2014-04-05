#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "QMessageBox"

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    current_stored_settings();
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

//Sefe Suiga Functions
void settingsDialog::on_pushButton_clicked()
{
    QSettings thisappsettin("SFMSLDevelopement","VaaigaAtulau");
    thisappsettin.beginGroup("VaaigaAtulauSettings");
    thisappsettin.setValue("homeUrl",ui->homUrlLineIN->text());               //[Value] homeURL
    thisappsettin.setValue("ProxyServer",ui->proxyserverLineIn->text());      //[Value] ProxyServer
    thisappsettin.setValue("ProxyPort",ui->proxyPortLineIN->text());          //[Value] ProxyPort

    if(ui->useproxy->isChecked()){                                            //[Value] EnableProxy
        thisappsettin.setValue("EnableProxy",1);
    }else if(!ui->useproxy->isChecked()){
        thisappsettin.setValue("EnableProxy",0);
    }

    if(ui->Sock5Toggle->isChecked()){                                         //[Value] ProxyType
        thisappsettin.setValue("ProxyType","sock5");
    }else if(ui->HTTPToggle->isChecked()){
        thisappsettin.setValue("ProxyType","HTTP");
    }



    thisappsettin.endGroup();

    QMessageBox::information(this,"Teu ina o suiaga fou","O loo iai suiga o loo suia nei ma loo ua uma ona sefe mo oe.");
}

//Faafoi Suiga Functions
void settingsDialog::default_Settings(){

    QString defaulthomeUrl = "http://www.google.com";
    QSettings thisappsettin("SFMSLDevelopement","VaaigaAtulau");
    thisappsettin.beginGroup("VaaigaAtulauSettings");
    thisappsettin.setValue("homeUrl",defaulthomeUrl);
    thisappsettin.endGroup();

    QMessageBox::information(this,"Toe Faafoi I le Atmataga","Ua Toe faafoi nei Suia O le Polokalame i ona "
                             "suiga na amata ai mai le amataga.");

}
void settingsDialog::on_pushButton_2_clicked()
{
    QString valueHomeUrl;
    default_Settings();

    QSettings thisappsettin("SFMSLDevelopement","VaaigaAtulau");
    thisappsettin.beginGroup("VaaigaAtulauSettings");
    valueHomeUrl.append(thisappsettin.value("homeUrl").toByteArray());
    thisappsettin.endGroup();

    ui->homUrlLineIN->setText(valueHomeUrl);

}

//loadstored value
void settingsDialog::current_stored_settings(){

    QString valHomeUrl;
    QString valProxyServer;
    QString valProxyType;
    int valProxyPort;
    int valEnableProxy;

    QSettings thisappsettin("SFMSLDevelopement","VaaigaAtulau");

    thisappsettin.beginGroup("VaaigaAtulauSettings");
    valHomeUrl.append(thisappsettin.value("homeUrl").toByteArray());
    valProxyServer = thisappsettin.value("ProxyServer").toByteArray();
    valProxyType = thisappsettin.value("ProxyType").toInt();
    valProxyPort = thisappsettin.value("ProxyPort").toInt();
    valEnableProxy = thisappsettin.value("EnableProxy").toInt();


    thisappsettin.endGroup();

    ui->homUrlLineIN->setText(valHomeUrl);
    ui->proxyPortLineIN->setText(QString::number(valProxyPort));
    ui->proxyserverLineIn->setText(valProxyServer);

    if(QString::compare(valProxyType,"sock5")){
        ui->Sock5Toggle->setChecked(true);
    }

    if(valEnableProxy == 1){
        ui->useproxy->setDisabled(false);
        ui->useproxy->setChecked(true);

    }

}

//Use Proxy or not
void settingsDialog::on_checkBox_toggled(bool checked)
{
    //Disabling Proxy control in setting Dialog
    if(checked == true){
        ui->proxyserverLineIn->setDisabled(false);              //This area of code can be improved by using a FOR LOOP
        ui->proxyPortLineIN->setDisabled(false);                //This is to make it more beautiful.
        ui->Sock5Toggle->setDisabled(false);
        ui->HTTPToggle->setDisabled(false);

    //Enabling Proxy Control in Setting Dialog
    }else if (checked == false){
        ui->proxyserverLineIn->setDisabled(true);
        ui->proxyPortLineIN->setDisabled(true);
        ui->Sock5Toggle->setDisabled(true);
        ui->HTTPToggle->setDisabled(true);
    }

}

void settingsDialog::on_Sock5Toggle_toggled(bool checked)
{
    if(checked){
        ui->HTTPToggle->setDisabled(true);
    }else if(!checked){
        ui->HTTPToggle->setDisabled(false);
    }else{
        ;; //do_nothing
    }
}

void settingsDialog::on_HTTPToggle_toggled(bool checked)
{
    if(checked){
        ui->Sock5Toggle->setDisabled(true);
    }else if(!checked){
        ui->Sock5Toggle->setDisabled(false);
    }else{
        ;; //do_nothing
    }
}

void settingsDialog::on_pushButton_3_clicked()
{
    on_pushButton_clicked();
    settingsDialog::close();
}
