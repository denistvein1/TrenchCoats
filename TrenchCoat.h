#pragma once
#include <string>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <sstream>

constexpr int MIN_QUANTITY = 1;
constexpr int MAX_QUANTITY = 1000;
constexpr double MIN_SIZE = 10.0;
constexpr double MAX_SIZE = 200.0;
constexpr double MIN_PRICE = 10.0;
constexpr double MAX_PRICE = 10000.0;
constexpr int MIN_PHOTO_LENGTH = 10;

using std::string;
using std::to_string;
using std::for_each;
using std::istream;
using std::ostream;
using std::vector;
using std::stringstream;

/*TrenchCoat class that stores properties related
to a trench coat along with some basic functions
like getters, setters, etc.*/
class TrenchCoat {

	int quantity;
	double size, price;
	string color, photo;

public:

	/*Default constructor for TrenchCoat. Sets the attributes
	to some default values.
	Input: -
	Output: A new TrenchCoat object.*/
	TrenchCoat();

	/*Initializes attributes.
	Input: size - real number >= 10.0.
		   color - string containing a color.
		   photo - string containing a link with length >= 10.
	Output: A new TrenchCoat object.*/
	TrenchCoat(double size, const string& color, const string& photo);

	/*Initializes attributes.
	Input: quantity - integer > 0.
		   size/price - real number >= 10.0.
		   color - string containing a color.
		   photo - string containing a link with length >= 10.
	Output: A new TrenchCoat object.*/
	TrenchCoat(int quantity, double size, double price, const string& color, const string& photo);

	/*Return the attribute quantity.
	Input: -
	Output: an integer representing the quantity
	attribute of the this object.*/
	int get_quantity() const noexcept;

	/*Return the attribute size.
	Input: -
	Output: a float representing the size
	attribute of the this object.*/
	double get_size() const noexcept;

	/*Return the attribute price.
	Input: -
	Output: a float representing the price
	attribute of the this object.*/
	double get_price() const noexcept;

	/*Return the attribute color.
	Input: -
	Output: a string representing the color
	attribute of the this object.*/
	const string& get_color() const noexcept;

	/*Return the attribute photo.
	Input: -
	Output: a string representing the photo
	attribute of the this object.*/
	const string& get_photo() const noexcept;

	/*Compare this object with trench_coat.
	Input: trench_coat - a reference to a const TrenchCoat object.
	Output: 1 if the objects are the same(apart from quantity and price),
	0 otherwise.*/
	bool operator==(const TrenchCoat& trench_coat) const noexcept;

	/*Compare this object with trench_coat.
	Input: trench_coat - a reference to a const TrenchCoat object.
	Output: 1 if the objects are different(apart from quantity and price),
	0 otherwise.*/
	bool operator!=(const TrenchCoat& trench_coat) const noexcept;

	/*Overload extraction operator to read a TrenchCoat.
	Input: is - istream object
		   trench_coat - TrenchCoat object.
	Output: a reference to an istream.*/
	friend istream& operator>>(istream& is, TrenchCoat& trench_coat);

	/*Overload insertion operator to write a TrenchCoat.
	Input: os - ostream object
		   trench_coat - TrenchCoat object.
	Output: a reference to an ostream.*/
	friend ostream& operator<<(ostream& os, const TrenchCoat& trench_coat);

	/*Returns a string representation of this object.
	Input: -
	Output: string representing this object.*/
	string to_str() const;

	/*Open the photo in browser.
	Input: -
	Output: - */
	void open() const noexcept;
};
