#pragma once
#include "TrenchCoat.h"
#include "Repository.h"
#include <QAbstractTableModel>
#include <memory>

using std::unique_ptr;

class ModelTrenchCoat : public QAbstractTableModel {

	Q_OBJECT
	unique_ptr<Repository<TrenchCoat>>& repository;

public:

	ModelTrenchCoat(unique_ptr<Repository<TrenchCoat>>& repository, QAbstractTableModel* parent = Q_NULLPTR);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	void add(const TrenchCoat& trench_coat);

	void update(const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat);

	void remove(const TrenchCoat& trench_coat);

	const vector<TrenchCoat> get_all() const;

};
