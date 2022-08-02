#include "ServiceShoppingCart.h"

ServiceShoppingCart::ServiceShoppingCart(unique_ptr<ModelTrenchCoat>& model_trench_coat, unique_ptr<ModelShoppingCart>& model_shopping_cart)
noexcept : model_trench_coat{ model_trench_coat }, model_shopping_cart{ model_shopping_cart }, total{ 0.0 } {}

void ServiceShoppingCart::add(const TrenchCoat& trench_coat) {
	this->model_shopping_cart.get()->add(trench_coat);
	this->total += trench_coat.get_quantity() * trench_coat.get_price();
	this->model_trench_coat.get()->remove(trench_coat);
	this->actions_undo.push_back(make_unique<ActionAddShoppingCart>(this->model_shopping_cart, trench_coat));
	this->actions_undo.push_back(make_unique<ActionRemove>(this->model_trench_coat, trench_coat));
	this->actions_redo.clear();
}

const vector<TrenchCoat> ServiceShoppingCart::get_all_by_size(double size) const {
	if (size == 0.0) {
		return get_repository();
	}
	vector<TrenchCoat> found_trench_coats{};
	vector<TrenchCoat> all_trench_coats = this->model_trench_coat.get()->get_all();
	for_each(all_trench_coats.begin(), all_trench_coats.end(), [&found_trench_coats, size](const TrenchCoat& trench_coat) {if (trench_coat.get_size() == size)  found_trench_coats.push_back(trench_coat);  });
	return found_trench_coats;
}

void ServiceShoppingCart::open_shopping_cart() const noexcept {
	this->model_shopping_cart.get()->open();
}

const vector<TrenchCoat> ServiceShoppingCart::get_repository() const {
	return this->model_trench_coat.get()->get_all();
}

double ServiceShoppingCart::get_total() const noexcept {
	return this->total;
}

bool ServiceShoppingCart::can_undo() const {
	return this->actions_undo.size();
}

bool ServiceShoppingCart::can_redo() const {
	return this->actions_redo.size();
}

void ServiceShoppingCart::undo() {
	if (can_undo()) {
		this->actions_undo.at(this->actions_undo.size() - 1).get()->undo();
		this->actions_redo.push_back(move(this->actions_undo.at(this->actions_undo.size() - 1)));
		this->actions_undo.pop_back();
		this->actions_undo.at(this->actions_undo.size() - 1).get()->undo();
		this->actions_redo.push_back(move(this->actions_undo.at(this->actions_undo.size() - 1)));
		this->actions_undo.pop_back();
	}
}

void ServiceShoppingCart::redo() {
	if (can_redo()) {
		this->actions_redo.at(this->actions_redo.size() - 1).get()->redo();
		this->actions_undo.push_back(move(this->actions_redo.at(this->actions_redo.size() - 1)));
		this->actions_redo.pop_back();
		this->actions_redo.at(this->actions_redo.size() - 1).get()->redo();
		this->actions_undo.push_back(move(this->actions_redo.at(this->actions_redo.size() - 1)));
		this->actions_redo.pop_back();
	}
}
