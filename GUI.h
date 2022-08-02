#pragma once
#include "ui_GUI.h"
#include "GUIAdmin.h"
#include "GUIUser.h"
#include "GUIChart.h"
#include "GUIShoppingCart.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>

class GUI : public QWidget {

	Q_OBJECT
	Ui::GUI ui;

	string path_trench_coats, path_csv_shoppong_cart, path_html_shopping_cart;

	unique_ptr<Repository<TrenchCoat>> repository;
	unique_ptr<FileRepository<TrenchCoat>> file_repository;
	unique_ptr<ModelTrenchCoat> model_trench_coat;
	unique_ptr<ModelShoppingCart> model_shopping_cart;
	unique_ptr<ServiceTrenchCoat> service_trench_coat;
	unique_ptr<ServiceShoppingCart> service_shopping_cart;
	unique_ptr<GUIAdmin> gui_admin;
	unique_ptr<GUIUser> gui_user;
	unique_ptr<GUIShoppingCart> gui_shopping_cart;
	unique_ptr<GUIChart> gui_chart;

	QVBoxLayout* layout;

	QMenuBar* menu_bar;
	QMenu* menu_file;
	QMenu* menu_edit;
	QAction* action_exit;
	QAction* action_undo;
	QAction* action_redo;

	QWidget* widget_gui;
	QPushButton* button_csv;
	QPushButton* button_html;
	QTabWidget* tabs;

	void initialize_gui();

	void create_actions();

	void create_menus();

	void connect_signals_and_slots();

signals:

	void initialize_signal();

private slots:

	void initialize();

	void button_csv_handler();

	void button_html_handler();

	void undo();

	void redo();

	void quit();

public:

	GUI(QWidget* parent = Q_NULLPTR);

};
