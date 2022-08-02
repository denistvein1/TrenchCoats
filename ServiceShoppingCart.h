#pragma once
#include "Action.h"

using std::make_unique;
using std::for_each;

/*This class represents a service class that
manages business logic for a shopping cart.*/
class ServiceShoppingCart
{

	unique_ptr<ModelTrenchCoat>& model_trench_coat;
	unique_ptr<ModelShoppingCart>& model_shopping_cart;
	vector<unique_ptr<Action>> actions_undo;
	vector<unique_ptr<Action>> actions_redo;

	double total;

public:

	/*Constructor initializes repository.
	 Input: repository - constant reference to a FileRepository.
	 Output: An object of type ServiceShoppingCart.*/
	ServiceShoppingCart(unique_ptr<ModelTrenchCoat>& model_trench_coat, unique_ptr<ModelShoppingCart>& model_shopping_cart) noexcept;

	/*Add an trench_coat to the shopping_cart.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: - */
	void add(const TrenchCoat& trench_coat);

	/*Return a vector containing all the trench coats found
	with the given size.
	Input: size - double.
	Output: A constant to a vector containing
	all the trench coats found with the given size.*/
	const vector<TrenchCoat> get_all_by_size(double size) const;

	/*Shows the shopping cart.
	Input: -
	Output: - */
	void open_shopping_cart() const noexcept;

	/*Return a vector containing all the trench coats found
	in repository.
	Input: -
	Output: A constant vector containing
	all the trench coats found in repository.*/
	const vector<TrenchCoat> get_repository() const;

	/*Return the total price of the trench coats from the shopping_cart.
	Input: -
	Output: double representing the sum.*/
	double get_total() const noexcept;

	bool can_undo() const;

	bool can_redo() const;

	void undo();

	void redo();

};
