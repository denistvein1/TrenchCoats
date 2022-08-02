#include "GUIAdmin.h"

GUIAdmin::GUIAdmin(unique_ptr<ServiceTrenchCoat>& service, unique_ptr<ModelTrenchCoat>& model, QWidget* parent) : service{ service }, model{ model }, QWidget(parent) {
	initialize_gui();
	connect_signals_and_slots();
	ui.setupUi(this);
}

void GUIAdmin::initialize_gui() {
	this->layout = new QHBoxLayout{ this };

	QWidget* widget_buttons = new QWidget{};
	QVBoxLayout* v_layout_buttons = new QVBoxLayout{ widget_buttons };
	this->button_add = new QPushButton{ "Add" };
	this->button_update = new QPushButton{ "Update" };
	this->button_remove = new QPushButton{ "Remove" };
	v_layout_buttons->addWidget(this->button_add);
	v_layout_buttons->addWidget(this->button_update);
	v_layout_buttons->addWidget(this->button_remove);

	this->list_trench_coats = new QTableView{};
	this->list_trench_coats->setModel(this->model.get());
	this->list_trench_coats->setSelectionMode(QAbstractItemView::SingleSelection);

	this->layout->addWidget(widget_buttons);
	this->layout->addWidget(this->list_trench_coats);
	initialize_add_functionality();
	initialize_update_functionality();
	initialize_remove_functionality();
}

void GUIAdmin::initialize_add_functionality() {
	this->widget_add = new QWidget{};

	QVBoxLayout* v_layout_add = new QVBoxLayout{ this->widget_add };

	QWidget* widget_form_add = new QWidget{};
	QFormLayout* form_add = new QFormLayout{ widget_form_add };
	QLabel* label_quantity = new QLabel{ "Quantity: " };
	QLabel* label_size = new QLabel{ "Size: " };
	QLabel* label_price = new QLabel{ "Price: " };
	QLabel* label_color = new QLabel{ "Color: " };
	QLabel* label_photo = new QLabel{ "Photo: " };
	this->line_edit_add_quantity = new QLineEdit{};
	this->line_edit_add_size = new QLineEdit{};;
	this->line_edit_add_price = new QLineEdit{};;
	this->line_edit_add_color = new QLineEdit{};;
	this->line_edit_add_photo = new QLineEdit{};;
	form_add->addRow(label_quantity, this->line_edit_add_quantity);
	form_add->addRow(label_size, this->line_edit_add_size);
	form_add->addRow(label_price, this->line_edit_add_price);
	form_add->addRow(label_color, this->line_edit_add_color);
	form_add->addRow(label_photo, this->line_edit_add_photo);

	QWidget* widget_buttons_add = new QWidget{};
	QHBoxLayout* h_layout_buttons_add = new QHBoxLayout{ widget_buttons_add };
	this->button_add_done = new QPushButton{ "done" };
	this->button_add_cancel = new QPushButton{ "cancel" };
	h_layout_buttons_add->addWidget(this->button_add_done);
	h_layout_buttons_add->addWidget(this->button_add_cancel);

	v_layout_add->addWidget(widget_form_add);
	v_layout_add->addWidget(widget_buttons_add);

	this->widget_add->hide();
	this->layout->addWidget(this->widget_add);
}

void GUIAdmin::initialize_update_functionality() {
	this->widget_update = new QWidget{};

	QVBoxLayout* v_layout_update = new QVBoxLayout{ this->widget_update };

	QWidget* widget_form_update = new QWidget{};
	QFormLayout* form_update = new QFormLayout{ widget_form_update };
	QLabel* label_new_quantity = new QLabel{ "New quantity: " };
	QLabel* label_new_size = new QLabel{ "New size: " };
	QLabel* label_new_price = new QLabel{ "New price: " };
	QLabel* label_new_color = new QLabel{ "New color: " };
	QLabel* label_new_photo = new QLabel{ "New photo: " };
	this->line_edit_update_new_quantity = new QLineEdit{};
	this->line_edit_update_new_size = new QLineEdit{};
	this->line_edit_update_new_price = new QLineEdit{};
	this->line_edit_update_new_color = new QLineEdit{};
	this->line_edit_update_new_photo = new QLineEdit{};
	form_update->addRow(label_new_quantity, this->line_edit_update_new_quantity);
	form_update->addRow(label_new_size, this->line_edit_update_new_size);
	form_update->addRow(label_new_price, this->line_edit_update_new_price);
	form_update->addRow(label_new_color, this->line_edit_update_new_color);
	form_update->addRow(label_new_photo, this->line_edit_update_new_photo);

	QWidget* widget_buttons_update = new QWidget{};
	QHBoxLayout* h_layout_buttons_update = new QHBoxLayout{ widget_buttons_update };
	this->button_update_done = new QPushButton{ "done" };
	this->button_update_cancel = new QPushButton{ "cancel" };
	h_layout_buttons_update->addWidget(this->button_update_done);
	h_layout_buttons_update->addWidget(this->button_update_cancel);

	v_layout_update->addWidget(widget_form_update);
	v_layout_update->addWidget(widget_buttons_update);

	this->widget_update->hide();
	this->layout->addWidget(this->widget_update);
}

void GUIAdmin::initialize_remove_functionality() {
	this->widget_remove = new QWidget{};

	QHBoxLayout* h_layout_buttons_remove = new QHBoxLayout{ this->widget_remove };
	this->button_remove_done = new QPushButton{ "done" };
	this->button_remove_cancel = new QPushButton{ "cancel" };
	h_layout_buttons_remove->addWidget(button_remove_done);
	h_layout_buttons_remove->addWidget(button_remove_cancel);

	this->widget_remove->hide();
	this->layout->addWidget(this->widget_remove);
}


void GUIAdmin::add_button_handler() {
	this->widget_update->hide();
	this->widget_remove->hide();
	this->widget_add->show();
}

void GUIAdmin::add_done_button_handler() {
	int quantity;
	double size, price;
	string string_quantity = this->line_edit_add_quantity->text().toStdString();
	string string_size = this->line_edit_add_size->text().toStdString();
	string string_price = this->line_edit_add_price->text().toStdString();
	string string_photo = this->line_edit_add_color->text().toStdString();
	string string_color = this->line_edit_add_photo->text().toStdString();

	try {
		quantity = stoi(string_quantity);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid quantity");
		return;
	}
	try {
		size = stod(string_size);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid size");
		return;
	}
	try {
		price = stod(string_price);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid price");
		return;
	}

	TrenchCoat trench_coat{ quantity, size, price, string_photo, string_color };
	try {
		this->service.get()->add(trench_coat);

		emit update_list_user_signal();
		emit update_chart_signal();
	}
	catch (const exception& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	this->line_edit_add_quantity->clear();
	this->line_edit_add_size->clear();
	this->line_edit_add_price->clear();
	this->line_edit_add_color->clear();
	this->line_edit_add_photo->clear();
}

void GUIAdmin::add_cancel_button_handler() {
	this->line_edit_add_quantity->clear();
	this->line_edit_add_size->clear();
	this->line_edit_add_price->clear();
	this->line_edit_add_color->clear();
	this->line_edit_add_photo->clear();
	this->widget_add->hide();
}


void GUIAdmin::update_button_handler() {
	this->widget_add->hide();
	this->widget_remove->hide();
	this->widget_update->show();
}

void GUIAdmin::update_done_button_handler() {
	int row = this->list_trench_coats->currentIndex().row();
	const vector<TrenchCoat>& all_trench_coats = this->service.get()->get_all();
	if (row < 0 || row >= all_trench_coats.size()) {
		QMessageBox::critical(this, "Error", "Invalid trench coat");
		return;
	}

	int new_quantity;
	double new_size, new_price;

	string string_new_quantity = this->line_edit_update_new_quantity->text().toStdString();
	string string_new_size = this->line_edit_update_new_size->text().toStdString();
	string string_new_price = this->line_edit_update_new_price->text().toStdString();
	string string_new_color = this->line_edit_update_new_color->text().toStdString();
	string string_new_photo = this->line_edit_update_new_photo->text().toStdString();

	try {
		new_quantity = stoi(string_new_quantity);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid new quantity");
		return;
	}
	try {
		new_size = stoi(string_new_size);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid new size");
		return;
	}
	try {
		new_price = stoi(string_new_price);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid new price");
		return;
	}

	TrenchCoat new_trench_coat{ new_quantity, new_size, new_price, string_new_color, string_new_photo };
	try {
		this->service.get()->update(all_trench_coats.at(row), new_trench_coat);

		emit update_list_user_signal();
		emit update_chart_signal();
	}
	catch (const exception& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	this->line_edit_update_new_quantity->clear();
	this->line_edit_update_new_size->clear();
	this->line_edit_update_new_price->clear();
	this->line_edit_update_new_color->clear();
	this->line_edit_update_new_photo->clear();
}

void GUIAdmin::update_cancel_button_handler() {
	this->line_edit_update_new_quantity->clear();
	this->line_edit_update_new_size->clear();
	this->line_edit_update_new_price->clear();
	this->line_edit_update_new_color->clear();
	this->line_edit_update_new_photo->clear();
	this->widget_update->hide();
}


void GUIAdmin::remove_button_handler() {
	this->widget_add->hide();
	this->widget_update->hide();
	this->widget_remove->show();
}

void GUIAdmin::remove_done_button_handler() {
	int row = this->list_trench_coats->currentIndex().row();
	const vector<TrenchCoat>& all_trench_coats = this->service.get()->get_all();
	if (row < 0 || row >= all_trench_coats.size()) {
		QMessageBox::critical(this, "Error", "Invalid trench coat");
		return;
	}

	this->service.get()->remove(all_trench_coats.at(row));

	emit update_list_user_signal();
	emit update_chart_signal();
}

void GUIAdmin::remove_cancel_button_handler() {
	this->widget_remove->hide();
}


void GUIAdmin::connect_signals_and_slots() {
	QObject::connect(this->button_add, &QPushButton::clicked, this, &GUIAdmin::add_button_handler);
	QObject::connect(this->button_add_done, &QPushButton::clicked, this, &GUIAdmin::add_done_button_handler);
	QObject::connect(this->button_add_cancel, &QPushButton::clicked, this, &GUIAdmin::add_cancel_button_handler);

	QObject::connect(this->button_update, &QPushButton::clicked, this, &GUIAdmin::update_button_handler);
	QObject::connect(this->button_update_done, &QPushButton::clicked, this, &GUIAdmin::update_done_button_handler);
	QObject::connect(this->button_update_cancel, &QPushButton::clicked, this, &GUIAdmin::update_cancel_button_handler);

	QObject::connect(this->button_remove, &QPushButton::clicked, this, &GUIAdmin::remove_button_handler);
	QObject::connect(this->button_remove_done, &QPushButton::clicked, this, &GUIAdmin::remove_done_button_handler);
	QObject::connect(this->button_remove_cancel, &QPushButton::clicked, this, &GUIAdmin::remove_cancel_button_handler);
}


void GUIAdmin::undo() {
	if (this->service.get()->can_undo()) {
		this->service.get()->undo();
		emit update_list_user_signal();
		emit update_chart_signal();
	}
}

void GUIAdmin::redo() {
	if (this->service.get()->can_redo()) {
		this->service.get()->redo();
		emit update_list_user_signal();
		emit update_chart_signal();
	}
}
