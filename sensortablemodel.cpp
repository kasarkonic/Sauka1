#include "sensortablemodel.h"


SensorTableModel::SensorTableModel(Global &global, QObject *parent)
    : QAbstractTableModel{parent}
    , global (global)
{}

int SensorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 20;
}

int SensorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

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
            //default:
            //  break;
            //}
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
    return QVariant();
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
            case DIChange:
                return "Jauna DI";
            case ANchange:
                return "Jauna AN";
            default:
                return "Sensors";
            }

        case Qt::SizeHintRole:
            return QSize( 200, 50 );

        default:
            return QVariant ();
        }

    }

    return QVariant ();
}

