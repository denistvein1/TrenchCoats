#include "ColorDelegate.h"

ColorDelegate::ColorDelegate(QWidget* parent) : QStyledItemDelegate{ parent } {}

void ColorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QString trench_coat = index.model()->data(index).toString();

	if (index.column() != 3) {
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}
	if (trench_coat.contains("black") || trench_coat.contains("negru")) {
		QPixmap pixmap("black.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("white") || trench_coat.contains("alb")) {
		QPixmap pixmap("white.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("blue") || trench_coat.contains("albastru")) {
		QPixmap pixmap("blue.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("red") || trench_coat.contains("rosu")) {
		QPixmap pixmap("red.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("green") || trench_coat.contains("verde")) {
		QPixmap pixmap("green.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("yellow") || trench_coat.contains("galben")) {
		QPixmap pixmap("yellow.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("pink") || trench_coat.contains("roz")) {
		QPixmap pixmap("pink.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("orange") || trench_coat.contains("portocaliu")) {
		QPixmap pixmap("orange.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("violet") || trench_coat.contains("purple") || trench_coat.contains("purpuriu")) {
		QPixmap pixmap("violet.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("aquamarine") || trench_coat.contains("bleumarin")) {
		QPixmap pixmap("aquamarine.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("brown") || trench_coat.contains("maro")) {
		QPixmap pixmap("brown.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("maroon") || trench_coat.contains("grena")) {
		QPixmap pixmap("maroon.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("beige") || trench_coat.contains("bej")) {
		QPixmap pixmap("beige.jpg");
		pixmap.scaled(sizeHint(option, index));
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("grey") || trench_coat.contains("gray") || trench_coat.contains("gri")) {
		QPixmap pixmap("grey.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
	else if (trench_coat.contains("azure") || trench_coat.contains("turquoise") || trench_coat.contains("azur")) {
		QPixmap pixmap("turquoise.jpg");
		painter->drawPixmap(option.rect, pixmap);
	}
}

QSize ColorDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	if (index.column() == 3) {
		return QSize(128, 128);
	}
	return QStyledItemDelegate::sizeHint(option, index);
}
