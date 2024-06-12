#include "readwrite.h"
#include <QFile>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QTextStream>

void loadCSV(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //QMessageBox::warning(this, "Error", "Could not open file");
        throw std::runtime_error("Could not open file");
    }


    QTextStream stream(&file);
    data.clear();
    QString hh = stream.readLine();
    headers = hh.split(',');

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');
        QList<QString> cur;
        for(int i = 0; i < fields.size(); i++)
            cur.append(fields[i]);

        data.push_back(cur);
    }


    file.close();
}

void saveTableToFile(const QString &filePath, QList<QList<QString> >& data, QList<QString>& headers)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("Could not open file");
    }

    QTextStream stream(&file);
    stream << headers.join(',') << "\n";

    for (int row = 0; row < data.size(); ++row)
        stream << data[row].join(',') << "\n";

    file.close();
}
