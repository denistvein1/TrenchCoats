#pragma once
#include "DomainValidator.h"
#include "Action.h"

using std::make_unique;

/*This class represents a service class that
manages business logic for trench coats.*/
class ServiceTrenchCoat {

	//unique_ptr<Repository<TrenchCoat>>& repository;
	unique_ptr<ModelTrenchCoat>& model;
	vector<unique_ptr<Action>> actions_undo;
	vector<unique_ptr<Action>> actions_redo;

public:

	/*Constructor initializes repository.
	 Input: repository - constant reference to a FileRepository.
	 Output: An object of type Service.*/
	//ServiceTrenchCoat(Repository<TrenchCoat>& repository) noexcept;
	ServiceTrenchCoat(unique_ptr<ModelTrenchCoat>& model) noexcept;

	/*Add an trench_coat to the repository.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: - */
	void add(const TrenchCoat& trench_coat);

	/*Update old_trench_coat with new_trench_coat.
	Input: old_trench_coat - constant reference to a TrenchCoat.
		   new_trench_coat - constant reference to a TrenchCoat.
	Output: - */
	void update(const TrenchCoat& old_trench_coat, const TrenchCoat& new_trench_coat);

	/*Remove an trench_coat from the repository.
	Input: trench_coat - constant reference to a TrenchCoat.
	Output: - */
	void remove(const TrenchCoat& trench_coat);

	/*Return a vector containing all the trench coats found.
	Input: -
	Output: A constant vector containing
	all the trench coats found.*/
	const vector<TrenchCoat> get_all() const;

	bool can_undo() const;

	bool can_redo() const;

	void undo();

	void redo();

};