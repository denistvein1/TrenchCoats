#pragma once
#include "TrenchCoat.h"
#include "Exception.h"

/*Validator class for a TrenchCoat.*/
class ValidatorTrenchCoat {

	/*Validates the quantity attribute of trench_coat.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: -
	Exception: throw exception if quantity is not valid.*/
	static void validate_quantity(const TrenchCoat& trench_coat);

	/*Validates the size attribute of trench_coat.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: -
	Exception: throw exception if size is not valid.*/
	static void validate_size(const TrenchCoat& trench_coat);

	/*Validates the price attribute of trench_coat.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: -
	Exception: throw exception if price is not valid.*/
	static void validate_price(const TrenchCoat& trench_coat);

	/*Validates the color attribute of trench_coat.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: -
	Exception: throw exception if color is not valid.*/
	static void validate_color(const TrenchCoat& trench_coat);

	/*Validates the photo attribute of trench_coat.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: -
	Exception: throw exception if photo is not valid.*/
	static void validate_photo(const TrenchCoat& trench_coat);

public:

	/*Validate function for a TrenchCoat attributes.
	Input: trench_coat - reference to a constant TrenchCoat.
	Output: -
	Exception: if the attributes are invalid.*/
	static void validate(const TrenchCoat& trench_coat);

};