#include "ServiceTrenchCoat.h"

ServiceTrenchCoat::ServiceTrenchCoat(unique_ptr<ModelTrenchCoat>& model) noexcept : model{ model } {}

void ServiceTrenchCoat::add(const TrenchCoat& trench_coat) {
    ValidatorTrenchCoat::validate(trench_coat);
    this->model.get()->add(trench_coat);
    this->actions_undo.push_back(make_unique<ActionAdd>(this->model, trench_coat));
    this->actions_redo.clear();
}

void ServiceTrenchCoat::update(const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat) {
    ValidatorTrenchCoat::validate(new_trench_coat);
    this->model.get()->update(old_trench_coat, new_trench_coat);
    this->actions_undo.push_back(make_unique<ActionUpdate>(this->model, old_trench_coat, new_trench_coat));
    this->actions_redo.clear();
}

void ServiceTrenchCoat::remove(const TrenchCoat& trench_coat) {
    ValidatorTrenchCoat::validate(trench_coat);
    this->model.get()->remove(trench_coat);
    this->actions_undo.push_back(make_unique<ActionRemove>(this->model, trench_coat));
    this->actions_redo.clear();
}

const vector<TrenchCoat> ServiceTrenchCoat::get_all() const {
    return this->model.get()->get_all();
}

bool ServiceTrenchCoat::can_undo() const {
    return this->actions_undo.size();
}

bool ServiceTrenchCoat::can_redo() const {
    return this->actions_redo.size();
}

void ServiceTrenchCoat::undo() {
    if (this->actions_undo.size()) {
        this->actions_undo.at(this->actions_undo.size() - 1).get()->undo();
        this->actions_redo.push_back(move(this->actions_undo.at(this->actions_undo.size() - 1)));
        this->actions_undo.pop_back();
    }
}

void ServiceTrenchCoat::redo() {
    if (this->actions_redo.size()) {
        this->actions_redo.at(this->actions_redo.size() - 1).get()->redo();
        this->actions_undo.push_back(move(this->actions_redo.at(this->actions_redo.size() - 1)));
        this->actions_redo.pop_back();
    }
}
