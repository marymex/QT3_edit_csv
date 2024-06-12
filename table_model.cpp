#include "table_model.h"
#include <QStandardItem>


table_model::table_model(const QList<QList<QString> >& ddata, const QList<QString>& hheaders, QObject *parent)
    : QAbstractTableModel(parent), _data(ddata), _headers(hheaders)
{
    //_data = ddata;
    /*for (int row = 0; row < ddata.size(); row++)
    {
        for(int col = 0; col < ddata[0].size(); col++)
        {
            QStandardItem *item = new QStandardItem(ddata[row][col]);
            this->setItem(row, col, item);
        }
    }*/
}


QVariant table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return _headers.at(section);
    else
        return section + 1;
}

int table_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _data.size();
}

int table_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (_data.size()==0)
        return 0;

    return _data[0].count();
}

QVariant table_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();


    return _data[index.row()][index.column()] ;
}
