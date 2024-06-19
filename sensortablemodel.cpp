#include "sensortablemodel.h"


SensorTableModel::SensorTableModel(Global &global, QObject *parent)
    : QAbstractTableModel{parent}
    , global (global)
{}

int SensorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (MAX_DIinput + MAX_VIRUAL_INPUT);
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
            return row;
        case SensName:
           // if (row < MAX_DIinput){
               // return global.DIinput[row].name;
                return global.sensList[row].name;
           // }
           // else{
           //     return global.ANinput4_20[row - MAX_DIinput].name;

          //  }
        case DIvalue:
            if (row < MAX_DIinput){
                //return global.DIinput[row].Di;
                return global.sensList[row].digital;
            }
            else{
                //return global.ANinput4_20[row - MAX_DIinput].An;
                return "";
            }
        case ANvalue:
            if (row < MAX_DIinput){
                //return global.DIinput[row].Di;
                return "";
            }
            else{
                return global.sensList[row].analog;
            }
        case DIChange:
            if (row < MAX_DIinput){
                //return global.DIinput[row].Di;
                return global.sensList[row].digital;
            }
            else{
                //return global.ANinput4_20[row - MAX_DIinput].An;
                return "";
            }
        case  ANchange:
            if (row < MAX_DIinput){
                //return global.DIinput[row].Di;
                return "";
            }
            else{
                return global.sensList[row ].analog;
            }




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
void SensorTableModel::updateData(int row)
{
     qDebug() << "SensorTableModel::updateData " << row ;
    QModelIndex idx1 = createIndex(row,0);
    QModelIndex idx2 = createIndex(row,5);
    emit dataChanged(idx1, idx2, { Qt::DisplayRole });
}

