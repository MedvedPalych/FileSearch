#include "filesearchmodel.h"
#include <QDir>                 // для класса не надо, поэтому тут подключаем

namespace FileInfo
{
    FileSearchModel::FileSearchModel() : FileSearchModel(".") // точка - текущая директория, пустые кавычки - неопределнность
    {
        // для Qt текущая директория - это папка build
    }

    FileSearchModel::FileSearchModel(QString path)
    {
        this->path = path;
//        this->path = new QString(path); // потому что path - указатель
    }

    void FileSearchModel::search(void)
    {
        if (path.isEmpty()) return;         // не работаем с пустым путем

        QDir dir(path);
        fileList = dir.entryInfoList();
    }

    void FileSearchModel::searchFiles(void)
    {
        if (path.isEmpty()) return;

        QDir dir(path);
        dir.setFilter(QDir::Files); // ищем только файлы
        fileList = dir.entryInfoList();
    }
} //Fileinfo
