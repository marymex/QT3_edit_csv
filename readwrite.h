#ifndef READWRITE_H
#define READWRITE_H
#include<QString>
#include<QList>

void loadCSV(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers);

void saveTableToFile(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers);

#endif // READWRITE_H
