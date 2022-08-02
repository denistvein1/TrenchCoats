#include "ModelTrenchCoat.h"

ModelTrenchCoat::ModelTrenchCoat(unique_ptr<Repository<TrenchCoat>>& repository, QAbstractTableModel* parent) : repository{ repository }, QAbstractTableModel(parent) {}

int ModelTrenchCoat::rowCount(const QModelIndex& parent) const {
	return this->repository.get()->size();
}

int ModelTrenchCoat::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant ModelTrenchCoat::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();

	TrenchCoat trench_coat = this->repository.get()->get_all().at(row);

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

QVariant ModelTrenchCoat::headerData(int section, Qt::Orientation orientation, int role) const {
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

bool ModelTrenchCoat::insertRows(int row, int count, const QModelIndex& parent) {
	if (row < 0 || row > rowCount() || count <= 0) {
		return false;
	}
	beginInsertRows(parent, row, row + count - 1);
	endInsertRows();
	return true;
}

bool ModelTrenchCoat::removeRows(int row, int count, const QModelIndex& parent) {
	if (row < 0 || row > rowCount() || count <= 0) {
		return false;
	}
	beginRemoveRows(parent, row + count - 1, row);
	endRemoveRows();
	return true;
}

void ModelTrenchCoat::add(const TrenchCoat& trench_coat) {
	insertRow(rowCount());
	this->repository.get()->add(trench_coat);
}

void ModelTrenchCoat::update(const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat) {
	vector<TrenchCoat> all_trench_coats = this->repository.get()->get_all();
	auto it = find(all_trench_coats.begin(), all_trench_coats.end(), old_trench_coat);
	if (it != all_trench_coats.end()) {
		ptrdiff_t row = distance(all_trench_coats.begin(), it);
		dataChanged(index(row, 0), index(row, 4));
		this->repository.get()->update(old_trench_coat, new_trench_coat);
	}
}

void ModelTrenchCoat::remove(const TrenchCoat& trench_coat) {
	removeRow(0);
	this->repository.get()->remove(trench_coat);
}

const vector<TrenchCoat> ModelTrenchCoat::get_all() const {
	return this->repository.get()->get_all();
}
