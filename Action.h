#pragma once
#include "ModelTrenchCoat.h"
#include "ModelShoppingCart.h"

class Action {

public:

	virtual void undo() = 0;

	virtual void redo() = 0;

	virtual ~Action() {}

};

class ActionAdd : public Action {

	TrenchCoat trench_coat;
	unique_ptr<ModelTrenchCoat>& model;

public:

	ActionAdd(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& trench_coat);

	void undo() override;

	void redo() override;

};

class ActionAddShoppingCart : public Action {

	TrenchCoat trench_coat;
	unique_ptr<ModelShoppingCart>& model;

public:

	ActionAddShoppingCart(unique_ptr<ModelShoppingCart>& model, const TrenchCoat& trench_coat);

	void undo() override;

	void redo() override;

};

class ActionRemove : public Action {

	TrenchCoat trench_coat;
	unique_ptr<ModelTrenchCoat>& model;

public:

	ActionRemove(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& trench_coat);

	void undo() override;

	void redo() override;

};

class ActionUpdate : public Action {

	TrenchCoat old_trench_coat, new_trench_coat;
	unique_ptr<ModelTrenchCoat>& model;

public:

	ActionUpdate(unique_ptr<ModelTrenchCoat>& model, const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat);

	void undo() override;

	void redo() override;

};
