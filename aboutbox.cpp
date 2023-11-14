#include "aboutbox.h"
#include "ui_aboutbox.h"
#include <QPixmap>

AboutBox::AboutBox(QWidget *parent) : QDialog(parent), ui(new Ui::AboutBox)
{
    ui->setupUi(this);
    setFixedSize(400,300);

    QPixmap pic("../FileExample/FileIcon.png"); // картиночка в диалоговое окно
    ui->label_2->setPixmap(pic);                // в лейбл пихаем картинку
}

AboutBox::~AboutBox()
{
    delete ui;
}

void AboutBox::on_pushButton_clicked()
{
    close();
}

