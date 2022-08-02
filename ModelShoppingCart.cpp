#include "ModelShoppingCart.h"

ModelShoppingCart::ModelShoppingCart(unique_ptr<FileRepository<TrenchCoat>>& shopping_cart, QAbstractTableModel* parent) : shopping_cart{ shopping_cart } {}

int ModelShoppingCart::rowCount(const QModelIndex& parent) const {
	return this->shopping_cart.get()->size();
}

int ModelShoppingCart::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant ModelShoppingCart::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();

	TrenchCoat trench_coat = this->shopping_cart.get()->get_all().at(row);

	if (role == Qt::DisplayRole) {
		if (column == 0) {
			return QString::number(trench_coat.get_quantity());
		}
		else if (column == 1) {
			return QString::number(trench_coat.get_size());
		}
		else if (column == 2) {
			return QString::number(trench_coat.get_price());
		}
		else if (column == 3) {
			return QString::fromStdString(trench_coat.get_color());
		}
		else if (column == 4) {
			return QString::fromStdString(trench_coat.get_photo());
		}
	}
	return QVariant{};
}

QVariant ModelShoppingCart::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return "Quantity";
			}
			else if (section == 1) {
				return "Size";
			}
			else if (section == 2) {
				return "Price";
			}
			else if (section == 3) {
				return "Color";
			}
			else if (section == 4) {
				return "Photo";
			}
		}
		if (orientation == Qt::Vertical) {
			return QString::number(section + 1);
		}
	}
	return QVariant{};
}

bool ModelShoppingCart::insertRows(int row, int count, const QModelIndex& parent) {
	if (row < 0 || row > rowCount() || count <= 0) {
		return false;
	}
	beginInsertRows(parent, row, row + count - 1);
	endInsertRows();
	return true;
}

bool ModelShoppingCart::removeRows(int row, int count, const QModelIndex& parent) {
	if (row < 0 || row > rowCount() || count <= 0) {
		return false;
	}
	beginRemoveRows(parent, row + count - 1, row);
	endRemoveRows();
	return true;
}

void ModelShoppingCart::add(const TrenchCoat& trench_coat) {
	insertRow(rowCount());
	this->shopping_cart.get()->add(trench_coat);
}

void ModelShoppingCart::remove(const TrenchCoat& trench_coat) {
	removeRow(0);
	this->shopping_cart.get()->remove(trench_coat);
}

void ModelShoppingCart::open() const noexcept {
	this->shopping_cart.get()->open();
}
