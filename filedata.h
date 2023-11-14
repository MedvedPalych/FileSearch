#ifndef FILEDATA_H
#define FILEDATA_H

#include <QAbstractTableModel>
#include <QFileInfoList>
#include "fileflags.h"

 class FileData : public QAbstractTableModel
{

public:
    FileData() {columns = 0; } // иначе мусор, т.к. конструктор еще не знает, сколько нам дали

    void fillData(const QFileInfoList&); // ссылка чтоб не копировать, конст чтоб не менять
    void setColumnCount(int columns) {this->columns = columns;}
    void setViewFlags(const FileFlags&);
    QVariant headerData(int, Qt::Orientation, int role=Qt::DisplayRole) const;
    QString getPath(const QModelIndex&);

    virtual ~FileData() {}

private:
    QList<QString> fileNames; // угловые скобки - это параметризация, шаблоны (template)
    QList<QString> filePaths;
    QList<int>     fileSizes;
    int columns;
    FileFlags flags; // флажочки!

public:
    // QAbstractItemModel interface - вставленные от базового класса методы
    int rowCount(const QModelIndex &parent = QModelIndex()) const;      // сколько надо отрисовать рядов
    int columnCount(const QModelIndex &parent = QModelIndex()) const;   // сколько надо колонн
    QVariant data(const QModelIndex &index, int role) const;// какая информация в таблице
    // QModelIndex - это класс для поиска данных в таблице
    // QVariant - это объединение любых данных инвариантно от их типа
    // для &parent поставили конструктор умолчаний в объявлении прям


};

#endif // FILEDATA_H
