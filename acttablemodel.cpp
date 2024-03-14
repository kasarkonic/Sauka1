#include "acttablemodel.h"

ActTableModel::ActTableModel(Global &global, QObject *parent)
    : QAbstractTableModel{parent}
    , global (global)
{

}
int ActTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return MAX_DIoutput;
}

int ActTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
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
            return row;
        case SensName:
            return global.DIoutput[row].name;
        case DIvalue:
            qDebug()<<"DIvalue "  << row << global.actList[row].digital;
            return global.DIoutput[row].Di;
        case ANvalue:
            qDebug()<<"ANvalue "  << row << global.actList[row].analog;
            return global.DIoutput[row].An;

        default:
            return QVariant();
        }

    case Qt::EditRole:
        switch (col) {
        case DIvalue:
            return QVariant();
            break;
        case ANvalue:
            return QVariant();
            break;
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
            case DIChange:
                return "Jauna DI";
            case ANchange:
                return "Jauna AN";
            default:
                return "Piedziņa";
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
    qDebug() << "ActTableModel::updateData " << row ;
    QModelIndex idx1 = createIndex(row,0);
    QModelIndex idx2 = createIndex(row,5);
    emit dataChanged(idx1, idx2, { Qt::DisplayRole });
}

