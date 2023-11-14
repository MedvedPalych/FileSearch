#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // -----------ОЧЕНЬ ВАЖНЫЙ КОД---------------
    frame = qobject_cast<MainWindow*>(parent); // приводим указатель к указателю
    // потому что владелец нашего диалога - это QWidget, а мы хотим работать с MainWindow
    ui->nameCheck->setChecked(frame->isFileNameVisible());
    ui->pathCheck->setChecked(frame->isFilePathVisible());
    ui->sizeCheck->setChecked(frame->isFileSizeVisible());
}

int SettingsDialog::checkCount()
{
    int i=0;
    if (ui->nameCheck->isChecked()) i++;
    if (ui->pathCheck->isChecked()) i++;
    if (ui->sizeCheck->isChecked()) i++;
    return i;
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{

        frame->SetFileNameVisible(ui->nameCheck->isChecked());
        frame->SetFilePathVisible(ui->pathCheck->isChecked());
        frame->SetFileSizeVisible(ui->sizeCheck->isChecked());
    // чтобы табличка перезаполнилась при нажатии этой кнопки,
    // а не только "поиск", нужно запустить филлдату (там emit)
    // чтобы не лезть напрямую в филлдату, у нас есть showResults()
        frame->showResults();

}



void SettingsDialog::on_sizeCheck_clicked()
{
    if (checkCount() < 1)
    {
        ui->buttonBox->setDisabled(1);
        ui->stopLbl->setText("Стоп! Необходимо хотя бы одно поле!");
    } else
    {
        ui->buttonBox->setDisabled(0);
        ui->stopLbl->setText(" ");
    }
}


void SettingsDialog::on_pathCheck_clicked()
{
    if (checkCount() < 1)
    {
        ui->buttonBox->setDisabled(1);
        ui->stopLbl->setText("Стоп! Необходимо хотя бы одно поле!");
    } else
    {
        ui->buttonBox->setDisabled(0);
        ui->stopLbl->setText(" ");
    }
}


void SettingsDialog::on_nameCheck_clicked()
{
    if (checkCount() < 1)
    {
        ui->buttonBox->setDisabled(1);
        ui->stopLbl->setText("Стоп! Необходимо хотя бы одно поле!");
    } else
    {
        ui->buttonBox->setDisabled(0);
        ui->stopLbl->setText(" ");
    }
}


void SettingsDialog::on_sizeCheck_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
}

