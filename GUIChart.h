#pragma once

#include "ui_GUIChart.h"
#include "ServiceTrenchCoat.h"
#include <unordered_map>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QVBoxLayout>
#include <QMessageBox>

using std::unordered_map;

class GUIChart : public QWidget {

	Q_OBJECT
	Ui::GUIChart ui;

	unique_ptr<ServiceTrenchCoat>& service;

	QVBoxLayout* layout;

	QChartView* chart_view;


public:

	GUIChart(unique_ptr<ServiceTrenchCoat>& service, QWidget *parent = Q_NULLPTR);

	void initialize_gui();

public slots:

	void chart_config();

};
