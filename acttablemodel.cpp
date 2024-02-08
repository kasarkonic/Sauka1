#include "acttablemodel.h"

ActTableModel::ActTableModel(Global &global, QObject *parent)
    : QAbstractTableModel{parent}
    , global (global)
{

}
int ActTableModel::rowCount(const QModelIndex &parent) const
{  
    return 2;
}

int ActTableModel::columnCount(const QModelIndex &parent) const
{   
    return 6;
}

QVariant ActTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:

       // qDebug() << "Update Display role" << row << col << global.actList[row].digital;
        switch (col) {
        case SensAddress:
            qDebug()<<"SensAddress "  << row << global.actList[row].address;
            return global.actList[row].address;
        case SensName:
            return global.actList[row].name;
        case DIvalue:
            qDebug()<<"DIvalue "  << row << global.actList[row].digital;
            return global.actList[row].digital;
        case ANvalue:
            qDebug()<<"ANvalue "  << row << global.actList[row].analog;
            return global.actList[row].analog;

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



QVariant ActTableModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        // qDebug() << "SensorTableModel::headerData" << section << orientation << role ;

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

void ActTableModel::updateData(int row)
{
    QModelIndex idx1 = createIndex(row,0);
    QModelIndex idx2 = createIndex(row,5);
    emit dataChanged(idx1, idx2, { Qt::DisplayRole });
}
