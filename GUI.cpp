#include "GUI.h"

GUI::GUI(QWidget* parent) : QWidget(parent) {
	this->path_trench_coats = "trench_coats.csv";
	this->path_csv_shoppong_cart = "shopping_cart.csv";
	this->path_html_shopping_cart = "shopping_cart.html";
	//this->repository = make_unique<FileRepository<TrenchCoat>>(path_trench_coats);
	this->repository = make_unique<DatabaseRepository<TrenchCoat>>("localhost", "root", "mysql", "trenchcoatsdb");
	this->model_trench_coat = make_unique<ModelTrenchCoat>(this->repository);
	create_actions();
	create_menus();
	initialize_gui();
	connect_signals_and_slots();
	ui.setupUi(this);
}

void GUI::initialize_gui() {
	this->layout = new QVBoxLayout{ this };

	this->widget_gui = new QWidget{};
	QVBoxLayout* v_layout_gui = new QVBoxLayout{ this->widget_gui };

	QLabel* label_file_type_selection = new QLabel{ "Choose the file type: " };
	label_file_type_selection->setAlignment(Qt::AlignCenter);
	QWidget* widget_file_type_selection = new QWidget{};
	QHBoxLayout* h_layout_file_type_buttons = new	QHBoxLayout{ widget_file_type_selection };
	this->button_csv = new QPushButton{ "CSV" };
	this->button_html = new QPushButton{ "HTML" };
	h_layout_file_type_buttons->addWidget(this->button_csv);
	h_layout_file_type_buttons->addWidget(this->button_html);

	v_layout_gui->addWidget(label_file_type_selection);
	v_layout_gui->addWidget(widget_file_type_selection);

	this->layout->addWidget(this->menu_bar);
	this->layout->addWidget(this->widget_gui);
}

void GUI::create_actions() {
	this->action_exit = new QAction{ "Exit", this };
	this->action_exit->setShortcut(QKeySequence::Close);
	QObject::connect(this->action_exit, &QAction::triggered, this, &GUI::quit);

	this->action_undo = new QAction("Undo", this);
	this->action_undo->setShortcut(QKeySequence::Undo);
	QObject::connect(this->action_undo, &QAction::triggered, this, &GUI::undo);

	this->action_redo = new QAction("Redo", this);
	this->action_redo->setShortcut(QKeySequence::Redo);
	QObject::connect(this->action_redo, &QAction::triggered, this, &GUI::redo);
}

void GUI::create_menus() {
	this->menu_bar = new QMenuBar{ this };
	this->menu_bar->setFixedHeight(21);

	this->menu_file = this->menu_bar->addMenu("File");
	this->menu_file->addAction(this->action_exit);

	this->menu_edit = this->menu_bar->addMenu("Edit");
	this->menu_edit->addAction(this->action_undo);
	this->menu_edit->addAction(this->action_redo);
}

void GUI::button_csv_handler() {
	this->file_repository = make_unique<CSVFileRepository<TrenchCoat>>(this->path_csv_shoppong_cart);
	emit initialize_signal();
}

void GUI::button_html_handler() {
	this->file_repository = make_unique<HTLMFileRepository<TrenchCoat>>(this->path_html_shopping_cart);
	emit initialize_signal();
}

void GUI::initialize() {
	this->model_shopping_cart = make_unique<ModelShoppingCart>(this->file_repository);
	this->service_trench_coat = make_unique<ServiceTrenchCoat>(this->model_trench_coat);
	this->service_shopping_cart = make_unique<ServiceShoppingCart>(this->model_trench_coat, this->model_shopping_cart);
	this->gui_admin = make_unique<GUIAdmin>(this->service_trench_coat, this->model_trench_coat);
	this->gui_user = make_unique<GUIUser>(this->service_shopping_cart);
	this->gui_shopping_cart = make_unique<GUIShoppingCart>(this->service_shopping_cart, this->model_shopping_cart);
	this->gui_chart = make_unique<GUIChart>(this->service_trench_coat);

	QObject::connect(this->gui_admin.get(), &GUIAdmin::update_list_user_signal, this->gui_user.get(), &GUIUser::reset_iterator);
	QObject::connect(this->gui_admin.get(), &GUIAdmin::update_chart_signal, this->gui_chart.get(), &GUIChart::chart_config);
	QObject::connect(this->gui_user.get(), &GUIUser::update_chart_signal, this->gui_chart.get(), &GUIChart::chart_config);
	QObject::connect(this->gui_shopping_cart.get(), &GUIShoppingCart::update_chart_signal, this->gui_chart.get(), &GUIChart::chart_config);

	this->tabs = new QTabWidget{};
	this->tabs->addTab(this->gui_admin.get(), "TrenchCoats");
	this->tabs->addTab(this->gui_user.get(), "Shop");
	this->tabs->addTab(this->gui_shopping_cart.get(), "ShoppingCart");
	this->tabs->addTab(this->gui_chart.get(), "Chart");
	this->layout->addWidget(this->tabs);

	this->widget_gui->hide();
}

void GUI::connect_signals_and_slots() {
	QObject::connect(this->button_csv, &QPushButton::clicked, this, &GUI::button_csv_handler);
	QObject::connect(this->button_html, &QPushButton::clicked, this, &GUI::button_html_handler);
	QObject::connect(this, &GUI::initialize_signal, this, &GUI::initialize);
}

void GUI::undo() {
	string tab_name = this->tabs->currentWidget()->objectName().toStdString();
	if (tab_name == "GUIAdmin") {
		this->gui_admin.get()->undo();
	}
	else if (tab_name == "GUIShoppingCart") {
		this->gui_shopping_cart.get()->undo();
	}
}

void GUI::redo() {
	string tab_name = this->tabs->currentWidget()->objectName().toStdString();
	if (tab_name == "GUIAdmin") {
		this->gui_admin.get()->redo();
	}
	else if (tab_name == "GUIShoppingCart") {
		this->gui_shopping_cart.get()->redo();
	}
}

void GUI::quit() {
	QApplication::quit();
}
