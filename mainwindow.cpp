#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutbox.h"
#include "settingsdialog.h"
#include "isindir.h"
#include <QMessageBox>
#include <iostream>
#include <QItemSelection>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFileFlags();
    ui->tableView->setModel(&fileData); // таблица основана на НАШЕЙ модели
     // с тейбл мы НЕ БУДЕМ!!! работать напрямую, все будет через НАШУ fileData

    connect(&fileData, SIGNAL(dataChanged(QModelIndex, QModelIndex)), ui->tableView, SLOT(update()));
    // привязали изменение данных fileData к обновлению TableView
    // это как плюсик в меню слотов и сигналов (проброска)
    // SIGNAL - макрос, а dataChanged - сигнал QAbstractTableModel (мы от него наследуем)
    // было dataChanged(), писало ошибку No such Signal
    // dataChanged(QModelIndex, QModelIndex)) убрало её
}

void MainWindow::SetFileNameVisible(bool name)
{
    flags.name = name;
}

void MainWindow::SetFilePathVisible(bool path)
{
    flags.path = path;
}

void MainWindow::SetFileSizeVisible(bool size)
{
    flags.size = size;
}

void MainWindow::setFileFlags(FileFlags &flags)
{
    this -> flags = flags;
}

void MainWindow::setFileFlags(void)
{
    flags.name = flags.path = flags.size = true;
}

void MainWindow::showResults()
{
    fileData.setColumnCount(flagsCount()); // создали flagsCount() спецом для этого
    fileData.setViewFlags(flags); // эти флаги - это флаги MainWindow (!!! ВОЗМОЖНЫ ОШИБКИ!!!)
    fileData.fillData(fSearch.getFileList());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox mBox;
        mBox.setWindowTitle("Путь не указан!");
        mBox.setText("Нельзя оставлять путь пустым, работаем с путем по умолчанию!");
        mBox.setIcon(QMessageBox::Information);
        mBox.setStandardButtons(QMessageBox::Ok);
        mBox.exec();                // пока не закроем бокс, остальное в блок
        ui->lineEdit->setText(".");
    }

    fSearch.setPath(ui->lineEdit->text());
    fSearch.search();

    showResults();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutBox about;
    about.exec();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionSaveRes_triggered()
{
    QFile resFile("results.txt");        // результаты поиска файлов в файл
    if (resFile.open(QIODevice::Append))
     {
        QTextStream stream(&resFile);
        foreach(QFileInfo file, fSearch.getFileList())
            stream << (file.fileName() + "\n");          // в файл
        resFile.flush();
        resFile.close();
     }
}

void MainWindow::on_actionIsInDir_triggered()
{
    IsInDir dialog(this);
    dialog.exec();

}

int MainWindow::flagsCount()
{
    int i=0;
    if (flags.name) i++;
    if (flags.path) i++;
    if (flags.size) i++;
    return i;
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
//    QFile file("myfile.txt");        // файл создается через пихание в конструктор
//    if (file.open(QIODevice::Append))
//     {
//        QTextStream stream(&file);
//        //stream          // из файла
//        file.flush();
//        file.close();
//    }
        std::cout << index.row() << " . " << index.column() <<std::endl; // ОТЛАДКА
//        ui->plainText->setPlainText((fileData.data(index, Qt::DisplayRole)).toString());
        ui->plainText->setPlainText(fileData.getPath(index));
}

