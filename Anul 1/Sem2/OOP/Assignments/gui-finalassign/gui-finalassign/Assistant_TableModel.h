#pragma once
#include <qabstractitemmodel.h>

#include "Repository.h"

class Assistant_TableModel : public QAbstractTableModel, public Observer {
private:
	Repository& repository;

public:
	Assistant_TableModel(Repository& repo, QObject* parent = nullptr);

	void update() override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	Qt::ItemFlags flags(const QModelIndex& index) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

