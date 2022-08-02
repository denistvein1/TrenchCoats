#include "TrenchCoat.h"

TrenchCoat::TrenchCoat() {
	this->quantity = MIN_QUANTITY;
	this->size = MIN_SIZE;
	this->price = MIN_PRICE;
	this->color = string{ "" };
	this->photo = string{ "" };
}

TrenchCoat::TrenchCoat(double size, const string& color, const string& photo) : TrenchCoat{} {
	this->size = size;
	this->color = color;
	for_each(this->color.begin(), this->color.end(), [](char& c) {c = static_cast<char>(tolower(c)); });
	this->photo = photo;
}

TrenchCoat::TrenchCoat(int quantity, double size, double price, const string& color, const string& photo) : TrenchCoat{ size, color, photo } {
	this->quantity = quantity;
	this->price = price;
}

int TrenchCoat::get_quantity() const noexcept {
	return this->quantity;
}

double TrenchCoat::get_size() const noexcept {
	return this->size;
}

double TrenchCoat::get_price() const noexcept {
	return this->price;
}

const string& TrenchCoat::get_color() const noexcept {
	return this->color;
}

const string& TrenchCoat::get_photo() const noexcept {
	return this->photo;
}

bool TrenchCoat::operator==(const TrenchCoat& trench_coat) const noexcept {
	return this->size == trench_coat.get_size() &&
		this->color == trench_coat.get_color() &&
		this->photo == trench_coat.get_photo();
}

bool TrenchCoat::operator!=(const TrenchCoat& trench_coat) const noexcept {
	return !(*this == trench_coat);
}

string TrenchCoat::to_str() const {
	return string{ "quantity: " + to_string(this->quantity)
		+ ", size: " + to_string(this->size)
		+ ", price: " + to_string(this->price)
		+ ", color: " + this->color
		+ ", photo: " + this->photo };
}

vector<string> tokenize(string line, char delimiter) {
	vector<string> result;
	stringstream ss(line);
	string token;
	while (getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

istream& operator>>(istream& is, TrenchCoat& trench_coat) {
	string line;
	getline(is, line);
	vector<string> result = tokenize(line, ',');
	if (result.size() != 5) {
		return is;
	}
	trench_coat.quantity = stoi(result[0]);
	trench_coat.size = stod(result[1]);
	trench_coat.price = stod(result[2]);
	trench_coat.color = result[3];
	trench_coat.photo = result[4];
	return is;
}

void TrenchCoat::open() const noexcept {
	ShellExecuteA(nullptr, nullptr, get_photo().c_str(), nullptr, nullptr, SW_SHOW);
}

ostream& operator<<(ostream& os, const TrenchCoat& trench_coat) {
	os << trench_coat.get_quantity() << ','
		<< trench_coat.get_size() << ','
		<< trench_coat.get_price() << ','
		<< trench_coat.get_color() + ','
		<< trench_coat.get_photo();
	return os;
}
