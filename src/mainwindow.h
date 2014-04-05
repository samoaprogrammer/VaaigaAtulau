#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit>
#include <QSettings>
#include <QtCore>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void on_webView_loadProgress(int progress);

    void on_lineEdit_returnPressed();

    void on_actionAmataga_triggered();

    void on_actionAluluma_triggered();

    void on_actionAlutua_triggered();

    void on_actionTapuni_le_Pololalame_triggered();

    void on_actionSeti_le_Polokalame_triggered();

    void on_loadVaaigaAtulau_settings();

    void on_actionFaafou_triggered();

private:
    Ui::MainWindow *ui;

    QString HomeUrlSettingValue;

};

#endif // MAINWINDOW_H
