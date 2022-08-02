#pragma once

#include "ui_GUIAdmin.h"
#include "ServiceTrenchCoat.h"
#include "ModelTrenchCoat.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <QMessageBox>
#include <QStringListModel>
#include <QTableView>

class GUIAdmin : public QWidget {

	Q_OBJECT
	Ui::GUIAdmin ui;

	unique_ptr<ServiceTrenchCoat>& service;
	unique_ptr<ModelTrenchCoat>& model;

	QTabWidget* tab_widget;

	QLayout* layout;

	QPushButton* button_add;
	QPushButton* button_remove;
	QPushButton* button_update;

	//QStringListModel* model;
	QTableView* list_trench_coats;

	//add functionality
	QWidget* widget_add;
	QLineEdit* line_edit_add_quantity;
	QLineEdit* line_edit_add_size;
	QLineEdit* line_edit_add_price;
	QLineEdit* line_edit_add_color;
	QLineEdit* line_edit_add_photo;
	QPushButton* button_add_done;
	QPushButton* button_add_cancel;

	//update functionality
	QWidget* widget_update;
	QLineEdit* line_edit_update_new_quantity;
	QLineEdit* line_edit_update_new_size;
	QLineEdit* line_edit_update_new_price;
	QLineEdit* line_edit_update_new_color;
	QLineEdit* line_edit_update_new_photo;
	QPushButton* button_update_done;
	QPushButton* button_update_cancel;

	//remove functionality
	QWidget* widget_remove;
	QPushButton* button_remove_done;
	QPushButton* button_remove_cancel;

	void initialize_gui();

	void initialize_add_functionality();

	void initialize_update_functionality();

	void initialize_remove_functionality();

	void connect_signals_and_slots();

signals:

	void update_list_user_signal();

	void update_chart_signal();

private slots:

	void add_button_handler();

	void add_done_button_handler();

	void add_cancel_button_handler();

	void update_button_handler();

	void update_done_button_handler();

	void update_cancel_button_handler();

	void remove_button_handler();

	void remove_done_button_handler();

	void remove_cancel_button_handler();

public slots:

public:

	GUIAdmin(unique_ptr<ServiceTrenchCoat>& service, unique_ptr<ModelTrenchCoat>& model, QWidget *parent = Q_NULLPTR);

	void undo();

	void redo();

};
