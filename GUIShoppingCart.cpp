#include "GUIShoppingCart.h"

GUIShoppingCart::GUIShoppingCart(unique_ptr<ServiceShoppingCart>& service, unique_ptr<ModelShoppingCart>& model, QWidget* parent)
	: service{ service }, model{ model }, QWidget(parent) {
	ui.setupUi(this);
	inititlize_gui();
}

void GUIShoppingCart::inititlize_gui() {
	this->ui.list_shopping_cart->setModel(this->model.get());
	this->ui.list_shopping_cart->setItemDelegate(new ColorDelegate{});
	this->ui.list_shopping_cart->setSelectionMode(QAbstractItemView::SingleSelection);

}

void GUIShoppingCart::undo() {
	if (this->service.get()->can_undo()) {
		this->service.get()->undo();
		emit update_chart_signal();
	}
}

void GUIShoppingCart::redo() {
	if (this->service.get()->can_redo()) {
		this->service.get()->redo();
		emit update_chart_signal();
	}
}