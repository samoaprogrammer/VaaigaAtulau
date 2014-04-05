#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();
    
private slots:
    void on_pushButton_clicked();
    void default_Settings();
    void current_stored_settings();
    void on_pushButton_2_clicked();
    void on_checkBox_toggled(bool checked);
    void on_Sock5Toggle_toggled(bool checked);
    void on_HTTPToggle_toggled(bool checked);

    void on_pushButton_3_clicked();

private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
