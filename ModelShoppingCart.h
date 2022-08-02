#pragma once
#include "TrenchCoat.h"
#include "Repository.h"
#include <QAbstractTableModel>
#include <memory>

using std::unique_ptr;

class ModelShoppingCart : public QAbstractTableModel {

	Q_OBJECT
	unique_ptr<FileRepository<TrenchCoat>>& shopping_cart;

public:

	ModelShoppingCart(unique_ptr<FileRepository<TrenchCoat>>& shopping_cart, QAbstractTableModel* parent = Q_NULLPTR);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	void add(const TrenchCoat& trench_coat);

	void remove(const TrenchCoat& trench_coat);

	void open() const noexcept;

};
