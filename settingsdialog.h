#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_sizeCheck_stateChanged(int arg1);

    void on_sizeCheck_clicked();

    void on_pathCheck_clicked();

    void on_nameCheck_clicked();

private:
    Ui::SettingsDialog *ui;
    MainWindow *frame;
    int checkCount(void);
};

#endif // SETTINGSDIALOG_H
