#ifndef ISINDIR_H
#define ISINDIR_H

#include <QDialog>
#include "mainwindow.h"
class QString;

namespace Ui {
class IsInDir;
}

class IsInDir : public QDialog
{
    Q_OBJECT

public:
    explicit IsInDir(QWidget *parent = nullptr);

    bool InDir=false; // не хочу делать геттер

    ~IsInDir();

private slots:
    void on_searchDirBtn_clicked();

private:
    Ui::IsInDir *ui;
    MainWindow *frame; // берем это, чтобы дотянуться до окна из диалога
    FileInfo::FileSearchModel  fSearch;
};

#endif // ISINDIR_H
