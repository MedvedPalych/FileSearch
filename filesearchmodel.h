#ifndef FILESEARCHMODEL_H
#define FILESEARCHMODEL_H
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTextStream>

//class QString;       // реализация потом, это как бы extern
                       // заинклюдили в .cpp файле, чтобы не тащить везде с собой
//class QFileInfoList; // но это сложно, оставлю как идею

namespace FileInfo
{
    class FileSearchModel
    {
    public:
        FileSearchModel();
        FileSearchModel(QString);

        QFileInfoList getFileList() const {return fileList;}
        void setPath(QString path) {this->path = path;}
        void setName(QString name) {this->name = name;}
        virtual void search(void);
        virtual void searchFiles(void);

        virtual ~FileSearchModel() {}; // если будем наследоваться от этого, то виртуал
            // IDE не выделяет как ошибку отсутствие реализации конструктора!!!
    private:
        QString path;
        QString name;
        QFileInfoList fileList;
        //        QString *path;   // без указателя не сработает, ибо QString здесь не реализован!!!
        //        QFileInfoList *fileList; // для фишки с инклюдом в .cpp, не смог сделать
    }; //class

} // FileInfo

#endif // FILESEARCHMODEL_H
