#include "GUIUser.h"

GUIUser::GUIUser(unique_ptr<ServiceShoppingCart>& service, QWidget* parent) : service{ service }, QWidget(parent) {
	initialize_gui();
	connect_signals_and_slots();
	ui.setupUi(this);
}

void GUIUser::initialize_gui() {
	this->layout = new QVBoxLayout{ this };

	QWidget* widget_form_total = new QWidget{};
	QHBoxLayout* h_layout_form_total = new QHBoxLayout{ widget_form_total };
	QWidget* widget_form = new QWidget{};
	QFormLayout* form = new	QFormLayout{ widget_form };
	QLabel* label_size = new QLabel{ "Size: " };
	this->line_edit_size = new QLineEdit{};
	QSize size_line_edit;
	size_line_edit.setHeight(30);
	size_line_edit.setWidth(100);
	this->line_edit_size->setMaximumSize(size_line_edit);
	form->addRow(label_size, line_edit_size);
	QLabel* label_total = new QLabel{ "Total: " };
	this->label_total_price = new QLabel{ "0" };
	h_layout_form_total->addWidget(widget_form);
	h_layout_form_total->addWidget(label_total);
	h_layout_form_total->addWidget(this->label_total_price);

	this->button_search = new QPushButton{ "Search" };

	this->list_trench_coats = new QListWidget{};
	this->list_trench_coats->setSelectionMode(QAbstractItemView::SingleSelection);

	QWidget* widget_buy_next = new QWidget{};
	QHBoxLayout* h_layout_buy_next = new QHBoxLayout{ widget_buy_next };
	this->button_buy = new QPushButton{ "Buy" };
	this->button_next = new QPushButton{ "Next" };
	h_layout_buy_next->addWidget(this->button_buy);
	h_layout_buy_next->addWidget(this->button_next);

	this->button_print_shopping_cart = new QPushButton{ "See shopping cart" };

	this->layout->addWidget(widget_form_total);
	this->layout->addWidget(this->button_search);
	this->layout->addWidget(this->list_trench_coats);
	this->layout->addWidget(widget_buy_next);
	this->layout->addWidget(this->button_print_shopping_cart);
}

void GUIUser::search_button_handler() {
	string string_size = this->line_edit_size->text().toStdString();

	try {
		size = stod(string_size);
	}
	catch (const exception&) {
		QMessageBox::critical(this, "Error", "Invalid size");
		return;
	}

	vector<TrenchCoat> temp = this->service.get()->get_all_by_size(size);
	if (!temp.size()) {
		stringstream message;
		message << "No trench coats found with size " << size;
		QMessageBox::critical(this, "Error", message.str().c_str());
		return;
	}
	all = temp;
	it = all.begin();
	emit update_list_signal();
}

void GUIUser::next_button_handler() {
	if (!this->list_trench_coats->selectedItems().size()) {
		QMessageBox::critical(this, "Error", "Select a trench coat first");
		return;
	}
	it++;
	if (it == all.end()) {
		it = all.begin();
	}
	emit update_list_signal();
}

void GUIUser::buy_button_handler() {
	if (!this->list_trench_coats->selectedItems().size()) {
		QMessageBox::critical(this, "Error", "Select a trench coat first");
		return;
	}
	this->service.get()->add(*it);
	emit update_chart_signal();
	stringstream total;
	total << this->service.get()->get_total();
	this->label_total_price->setText(QString::fromStdString(total.str()));
	all = this->service.get()->get_all_by_size(size);
	it = all.begin();
	if (all.begin() == all.end()) {
		this->list_trench_coats->clear();
		stringstream message;
		message << "No more trench coats with size " << size;
		QMessageBox::warning(this, "Warning", message.str().c_str());
		return;
	}
	emit update_list_signal();
}

void GUIUser::print_shopping_cart_button_handler() {
	this->service.get()->open_shopping_cart();
}

void GUIUser::display_current_trench_coat() {
	if (this->list_trench_coats->count() > 0) {
		this->list_trench_coats->clear();
	}
	QString current_item = QString::fromStdString((*it).to_str());
	QListWidgetItem* item = new QListWidgetItem{ current_item };
	this->list_trench_coats->addItem(item);
	this->list_trench_coats->setCurrentRow(0);
	//(*it).open();
}

void GUIUser::connect_signals_and_slots() {
	QObject::connect(this->button_search, &QPushButton::clicked, this, &GUIUser::search_button_handler);
	QObject::connect(this->button_next, &QPushButton::clicked, this, &GUIUser::next_button_handler);
	QObject::connect(this->button_buy, &QPushButton::clicked, this, &GUIUser::buy_button_handler);
	QObject::connect(this->button_print_shopping_cart, &QPushButton::clicked, this, &GUIUser::print_shopping_cart_button_handler);
	QObject::connect(this, &GUIUser::update_list_signal, this, &GUIUser::display_current_trench_coat);
}

void GUIUser::reset_iterator() {
	all = this->service.get()->get_all_by_size(size);
	it = all.begin();
	if (all.begin() == all.end()) {
		this->list_trench_coats->clear();
	}
	else {
		emit update_list_signal();
	}
}
