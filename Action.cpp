#include "Action.h"

ActionAdd::ActionAdd(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& trench_coat) : model{ model }, trench_coat{ trench_coat } {}

void ActionAdd::undo() {
	this->model.get()->remove(this->trench_coat);
}

void ActionAdd::redo() {
	this->model.get()->add(this->trench_coat);
}

ActionAddShoppingCart::ActionAddShoppingCart(unique_ptr<ModelShoppingCart>& model, const TrenchCoat& trench_coat)
	: model{ model }, trench_coat{ trench_coat } {}

void ActionAddShoppingCart::undo() {
	this->model.get()->remove(this->trench_coat);
}

void ActionAddShoppingCart::redo() {
	this->model.get()->add(this->trench_coat);
}

ActionRemove::ActionRemove(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& trench_coat) : model{ model }, trench_coat{ trench_coat } {}

void ActionRemove::undo() {
	this->model.get()->add(this->trench_coat);
}

void ActionRemove::redo() {
	this->model.get()->remove(this->trench_coat);
}

ActionUpdate::ActionUpdate(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat)
	: model{ model }, old_trench_coat{ old_trench_coat }, new_trench_coat{ new_trench_coat } {}

void ActionUpdate::undo() {
	this->model.get()->update(new_trench_coat, old_trench_coat);
}

void ActionUpdate::redo() {
	this->model.get()->update(old_trench_coat, new_trench_coat);
}
