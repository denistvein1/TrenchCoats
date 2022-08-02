#include "GUIChart.h"

GUIChart::GUIChart(unique_ptr<ServiceTrenchCoat>& service, QWidget* parent) : service{ service }, QWidget(parent) {
	initialize_gui();
	ui.setupUi(this);
}

void GUIChart::initialize_gui() {
	this->layout = new QVBoxLayout{ this };

	this->chart_view = new QChartView{};

	chart_config();

	this->layout->addWidget(chart_view);
}

void GUIChart::chart_config() {
	unordered_map<int, int> sizes;
	QBarSeries* series = new QBarSeries{};

	for (const auto& trench_coat : this->service.get()->get_all()) {
		sizes[trench_coat.get_size()]++;
	}

	for (const auto& pair : sizes) {
		QBarSet* set = new QBarSet(to_string(pair.first).c_str());
		*set << pair.second;
		series->append(set);
	}

	QChart* chart = new QChart{};
	chart->addSeries(series);
	chart->setTitle("Trench coats by size");
	chart->setAnimationOptions(QChart::AllAnimations);
	QStringList categories;
	categories << "Sizes";
	QBarCategoryAxis* axis = new QBarCategoryAxis{};
	axis->append(categories);
	chart->createDefaultAxes();
	chart->setAxisX(axis, series);
	chart->legend()->setVisible(true);

	this->chart_view->setChart(chart);
}
