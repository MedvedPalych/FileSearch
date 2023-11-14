#include "isindir.h"
#include "ui_isindir.h"
#include <iostream> // отладка

IsInDir::IsInDir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IsInDir)
{
    ui->setupUi(this);
    setFixedSize(400,150); // (W, H)
    ui->resultLbl->setText("");

    // -----------ОЧЕНЬ ВАЖНЫЙ КОД---------------
    frame = qobject_cast<MainWindow*>(parent); // приводим указатель к указателю
    // потому что владелец нашего диалога - это QWidget, а мы хотим работать с MainWindow
}

IsInDir::~IsInDir()
{
    delete ui;
}

void IsInDir::on_searchDirBtn_clicked()
{
    InDir=false;
    if (!ui->lineEdit->text().isEmpty()) // только если строка не пустая
    {
        fSearch.setPath(".");
        fSearch.search();
//        foreach(QFileInfo file, fSearch.getFileList())
//        {
//           std::cout<<file.fileName().toStdString()<<std::endl; // отладка
//           std::cout<<ui->lineEdit->text().toStdString()<<std::endl; // отладка
//        }
        foreach(QFileInfo file, fSearch.getFileList())
            if (file.fileName().toStdString() == ui->lineEdit->text().toStdString())
                InDir=true;
        if (InDir) ui->resultLbl->setText("Есть такой файл!");
        else       ui->resultLbl->setText("Нет такого файла!");
    }
}

