#ifndef SENSORTABLEMODEL_H
#define SENSORTABLEMODEL_H

#include "global.h"
#include <QAbstractTableModel>

class SensorTableModel : public QAbstractTableModel
{
public:
    explicit SensorTableModel(Global &global, QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    void addRow(QString str1, QString str2, QString str3);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QString getColumnName(int column);






private:
    enum Columns {
        SensAddress,
        SensName,
        DIvalue,
        ANvalue,
        Button
    };
    Global &global;
    QList <QString> list1, list2, list3;
};

#endif // SENSORTABLEMODEL_H
