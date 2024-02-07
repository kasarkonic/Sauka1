#include "sensortablemodel.h"

SensorTableModel::SensorTableModel(Global &global, QObject *parent)
    : QAbstractTableModel{parent}
    , global (global)
{
    //setheaderData(SensAddress, Qt::Horizontal, "AAA", Qt::DisplayRole);
    bool ok = setHeaderData(1, Qt::Horizontal, "A");
    qDebug() << "header = "<< ok;
}

int SensorTableModel::rowCount(const QModelIndex &parent) const
{
    return 20;
}

int SensorTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}
/*
void SensorTableModel::addRow(QString str1, QString str2, QString str3)
{
    beginInsertRows( QModelIndex(), 0, 2 );
    list1.append(str1);
    list2.append(str2);
    list3.append(str3);
    endInsertRows();
}
*/
QVariant SensorTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        switch (col) {
        case SensAddress:
            return global.sensList[row].address;
        case SensName:
            return global.sensList[row].name;
        case DIvalue:
            return global.sensList[row].digital;
        case ANvalue:
            return global.sensList[row].analog;

        default:
            return QVariant();
        }

    case Qt::EditRole:
        switch (col) {
        case DIvalue:
            break;
        case ANvalue:
            break;
        default:
            break;
        }


    case Qt::DecorationRole:
        // if (col == PictureColumn) {
        //      return getToolPicture(row);
        //  } else {
        return QVariant();
        //  }
        //  case Qt::EditRole:
        //      return Units::splitInTwoLines(
        //         index.data(Qt::DisplayRole).toString());
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        //  case Qt::BackgroundRole:
        //      return QBrush(getBackgroundColor(row));
    default:
        return QVariant();
    }
}





QVariant SensorTableModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        qDebug() << "SensorTableModel::headerData" << section << orientation << role ;

        switch (role) {
        case Qt::DisplayRole:       
            switch (section) {
            case SensAddress:
                return "Adrese";
                 case SensName:
                     return "Nosaukumse";
                 case DIvalue:
                     return "Vērtība Di";
                  case ANvalue:
                      return "Vērtība AI";
            default:
                return "SensAddress";
            }

        case Qt::SizeHintRole:
            return QSize( 200, 50 );

        default:
            return QVariant ();
        }

    }

    return QVariant ();
}


//QString SensorTableModel::getColumnName(int column)
//{
//        return COLUMN_NAMES[column];
//}
