#pragma once

#include "ui_GUIUser.h"
#include "ServiceShoppingCart.h"
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QAbstractItemView>
#include <QMessageBox>

class GUIUser : public QWidget {
	Q_OBJECT

	Ui::GUIUser ui;
	unique_ptr<ServiceShoppingCart>& service;

	double size;
	vector<TrenchCoat> all;
	vector<TrenchCoat>::iterator it;

	QLayout* layout;

	QLineEdit* line_edit_size;

	QLabel* label_total_price;

	QPushButton* button_search;
	QPushButton* button_buy;
	QPushButton* button_next;
	QPushButton* button_print_shopping_cart;

	QListWidget* list_trench_coats;

	void initialize_gui();

	void connect_signals_and_slots();

signals:

	void update_list_signal();

	void update_chart_signal();

private slots:

	void search_button_handler();

	void next_button_handler();

	void buy_button_handler();

	void print_shopping_cart_button_handler();

	void display_current_trench_coat();

public slots:

	void reset_iterator();

public:

	GUIUser(unique_ptr<ServiceShoppingCart>& service, QWidget *parent = Q_NULLPTR);

};
