#include "Assistant_TableModel.h"

Assistant_TableModel::Assistant_TableModel(Repository& repo, QObject* parent) :
    QAbstractTableModel(parent),
    repository{ repo }
{}

void Assistant_TableModel::update() {
    this->beginResetModel();
    this->endResetModel();
}

int Assistant_TableModel::rowCount(const QModelIndex& parent) const {
    return this->repository.getRepositoryCount();
}

int Assistant_TableModel::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant Assistant_TableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();

    Material material = this->repository.getAllMaterials()[row];

    int column = index.column();

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (column)
    {
    case 0:
        return QString::fromStdString(material.getID());
    case 1:
        return QString::fromStdString(material.getSize().toString());
    case 2:
        return material.getQuantityOfMicrofragments();
    case 3:
        return material.getRadioactivityLevel();
    case 4:
        return QString::fromStdString(material.getDigitizedScan());
    default:
        break;
    }
}

Qt::ItemFlags Assistant_TableModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable;
}

QVariant Assistant_TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0:
        return QString("ID");
    case 1:
        return QString("Size");
    case 2:
        return QString("Microfragments");
    case 3:
        return QString("Radioactivity");
    case 4:
        return QString("Digitized Scan");
    default:
        return QVariant();
    }
}
