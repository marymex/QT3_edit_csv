#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include<QList>
#include<QString>

class table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit table_model(const QList<QList<QString> >& mdata, const QList<QString>& hheaders, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    const QList<QList<QString> >& _data;
    const QList<QString>& _headers;
};

#endif // TABLE_MODEL_H
