#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filesearchmodel.h"
#include "fileflags.h"
#include "filedata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void SetFileNameVisible(bool);  // методы флажков
    void SetFilePathVisible(bool);  // прям тут, а не внутри
    void SetFileSizeVisible(bool);  // класса флажков
    void setFileFlags(FileFlags&);
    void setFileFlags(void);

    void showResults(void);

    // так удобней, ибо важно не к чему они принадлежат, а откуда будем вызывать
    bool isFileNameVisible(void) const {return flags.name;} // геттеры
    bool isFilePathVisible(void) const {return flags.path;} // всегда
    bool isFileSizeVisible(void) const {return flags.size;} // конст

    virtual ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionSettings_triggered();

    void on_actionSaveRes_triggered();

    void on_actionIsInDir_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    FileInfo::FileSearchModel  fSearch;
    FileFlags flags;       // зачем тут писать класс/структ?
  //struct FileFlags flags;// потому что раньше надо было для структуры так писать (пример)
    FileData fileData;

    int flagsCount(void); // для подсчета переданных нам колонн (мы же не знаем, сколько дали)

}; // MainWindow
#endif // MAINWINDOW_H
