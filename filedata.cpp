#include "filedata.h"
#include <iostream>

// QAbstractItemModel interface

void FileData::fillData(const QFileInfoList &list)
{
    fileNames.clear();  // clear() - методы QList
    filePaths.clear();
    fileSizes.clear();

    foreach(QFileInfo file, list)
    {
        fileNames.append(file.fileName()); // append, file.fileName() - тоже из QList
        filePaths.append(file.filePath());
        fileSizes.append(file.size());
    }

    emit dataChanged(index(0,0), index(rowCount(), columnCount()));
    // index(0,0) - левый верх угол, второе - правый нижний
    emit layoutChanged(); // выпустить сигнал по изменению состояния
}

void FileData::setViewFlags(const FileFlags &flags)
{
    // в примере здесь на входе три булеана, а не объект!
    // не напороться
//    this->flags.name = flags.name;
//    this->flags.path = flags.path;
//    this->flags.size = flags.size;
    this->flags = flags;
}

QVariant FileData::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((orientation!=Qt::Horizontal) || (role!=Qt::DisplayRole))
        return QVariant(); // аналогично методу data даем пустой вариант, если не работаем

    int pos = 0;
    if (!flags.name) pos--;
    if (section == pos) return "Name";

    pos++;
    if (!flags.path) pos--;
    if (section == pos) return "Path";

    pos++;
    if (!flags.size) pos--;
    if (section == pos) return "Size";

    return QVariant(); // если не сработали if, то надо что-то выдать все равно (пустота)
}

QString FileData::getPath(const QModelIndex &index)
{
    return filePaths.at(index.row());
}

int FileData::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);           // заглушка чтобы не доставало предупреждение unused parent
    return fileNames.length();
}

int FileData::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns;         // нам их передают извне (в заголовочном реализовано)
}

QVariant FileData::data(const QModelIndex &index, int role) const
{
    if((role != Qt::DisplayRole) || (!index.isValid())) return QVariant();
    // если нам дали НЕ дисплей рол, то возвращаем пустые данные
    // проверка корректности индекса нам неизвестна, но надо проверить все равно!

    int pos = 0;
    if (!flags.name) pos--;
    if (index.column() == pos) return fileNames[index.row()];

    pos++;
    if (!flags.path) pos--;
    if (index.column() == pos) return filePaths[index.row()];

    pos++;
    if (!flags.size) pos--;
    if (index.column() == pos) return fileSizes[index.row()];

    return QVariant(); // если не сработали if, то надо что-то выдать все равно (пустота)
}

