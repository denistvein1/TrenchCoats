#pragma once

#include "ui_GUIShoppingCart.h"
#include "ServiceShoppingCart.h"
#include "ModelShoppingCart.h"
#include "ColorDelegate.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>

class GUIShoppingCart : public QWidget {
	Q_OBJECT
	Ui::GUIShoppingCart ui;
	unique_ptr<ServiceShoppingCart>& service;
	unique_ptr<ModelShoppingCart>& model;

	void inititlize_gui();

signals:

	void update_chart_signal();

public:

	GUIShoppingCart(unique_ptr<ServiceShoppingCart>& service, unique_ptr<ModelShoppingCart>& model, QWidget* parent = Q_NULLPTR);

public slots:

	void undo();

	void redo();

};
