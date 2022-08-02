#pragma once
#include <fstream>
#include <vector>
#include <windows.h>
#include <mysql.h>
#include "Exception.h"

using std::vector;
using std::find;
using std::ifstream;
using std::ofstream;
using std::ios;

/*This class represents a repository of elements
stored in a vector.*/
template <typename T>
class Repository {

	vector<T> elements;

	/*Search for element in the vector and returns
	its the position if found or -1 otherwise.
	Input: element - reference to a constant object of type T.
	Output: an integer representing the position of the element
	if it was found or -1 otherwise.*/
	int find_element(const T& element) const;

public:

	/*Add an element to the repository.
	Input: element - a generic element.
	Output: - */
	virtual void add(const T& element);

	/*Update old_element to new_element if possible.
	Input: old_element - a generic element.
		   new_element - a generic element.
	Output: - */
	virtual void update(const T& old_element, const T& new_element);

	/*Remove an element from the repository.
	Input: element - a generic element.
	Output: - */
	virtual void remove(const T& element);

	/*Return a vector containing all the elements
	found in repository.
	Input: -
	Output: A constant to a vector containing
	all the elements found in repository.*/
	virtual const vector<T> get_all() const;

	virtual int size() const;

	/*Destructor.*/
	virtual ~Repository() {}

};

template<typename T>
int Repository<T>::find_element(const T& element) const {
	auto it = find(this->elements.begin(), this->elements.end(), element);
	if (it == this->elements.end()) {
		return -1;
	}
	return static_cast<int>(distance(this->elements.begin(), it));
}

template <typename T>
void Repository<T>::add(const T& element) {
	const int position = find_element(element);
	if (position != -1) {
		throw Exception(2, "Element already exists");
	}
	else {
		this->elements.push_back(element);
	}
}

template <typename T>
void Repository<T>::update(const T& old_element, const T& new_element) {
	const int position_old_element = find_element(old_element);
	const int position_new_element = find_element(new_element);
	if (position_old_element == -1) {
		throw Exception(2, "Old element not found");
	}
	if (position_new_element != -1) {
		throw Exception(2, "New element already exists");
	}
	this->elements.at(position_old_element) = new_element;
}

template <typename T>
void Repository<T>::remove(const T& element) {
	const int position = find_element(element);
	if (position == -1) {
		throw Exception(2, "Element not found");
	}
	this->elements.erase(this->elements.begin() + position);
}

template <typename T>
const vector<T> Repository<T>::get_all() const {
	return this->elements;
}

template<typename T>
int Repository<T>::size() const {
	return (int)this->elements.size();
}

template <typename T>
class DatabaseRepository : public Repository<T> {

	const string TABLE_TRENCH_COATS = "trenchcoats";
	const string COLUMN_QUANTITY = "quantity";
	const string COLUMN_SIZE = "size";
	const string COLUMN_PRICE = "price";
	const string COLUMN_COLOR = "color";
	const string COLUMN_PHOTO = "photo";

	int sz;
	MYSQL* connection;

	/*Create table.
	Input: -
	Output: - */
	void create_table(const string& table) const;

public:

	/*Constructor for DatabaseRepository.
	Input: host - a string representing the database host
		   user - a string representing the database user
		   password - a string representing the database password
		   database - a string representing the database name
	Output: A DatabaseRepository object.*/
	DatabaseRepository(const string& host, const string& user, const string& password, const string& database);

	/*Check if element is in the database.
	Input: element - a generic element.
	Output: true if element is in the database,
	false otherwise*/
	bool contains(const T& element) const;

	/*Add an element to the database.
	Input: element - a generic element.
	Output: - */
	void add(const T& element) override;

	/*Update old_element to new_element.
	Input: old_element - a generic element.
		   new_element - a generic element.
	Output: - */
	void update(const T& old_element, const T& new_element) override;

	/*Remove an element from the database.
	Input: element - a generic element.
	Output: - */
	void remove(const T& element) override;

	/*Return a vector containing all the elements
	found in database.
	Input: -
	Output: A constant to a vector containing
	all the elements found in database.*/
	const vector<T> get_all() const override;

	int size() const override;

	/*Destructor.*/
	~DatabaseRepository();

};

template <typename T>
DatabaseRepository<T>::DatabaseRepository(const string& host, const string& user, const string& password, const string& database) {
	this->connection = mysql_init(nullptr);
	this->connection = mysql_real_connect(this->connection, host.c_str(), user.c_str(),
		password.c_str(), database.c_str(), 0, nullptr, 0);
	create_table(TABLE_TRENCH_COATS);
	sz = (int)get_all().size();
}

template<typename T>
void DatabaseRepository<T>::create_table(const string& table) const {
	string query{ "CREATE TABLE IF NOT EXISTS " + table +
	" (" + COLUMN_QUANTITY + " INT, " +
	COLUMN_SIZE + " DOUBLE, " +
	COLUMN_PRICE + " DOUBLE, " +
	COLUMN_COLOR + " TEXT, " +
	COLUMN_PHOTO + " TEXT)" };
	mysql_query(this->connection, query.c_str());
}

template<typename T>
bool DatabaseRepository<T>::contains(const T& element) const {
	MYSQL_RES* result = nullptr;
	bool results_found{ false };
	string query{ "SELECT * FROM " + TABLE_TRENCH_COATS + " WHERE " + COLUMN_SIZE + "=" + to_string(element.get_size()) + " AND " +
	COLUMN_COLOR + "='" + element.get_color() + "' AND  " + COLUMN_PHOTO + "='" + element.get_photo() + "'" };
	mysql_query(this->connection, query.c_str());
	result = mysql_store_result(this->connection);
	if (mysql_num_rows(result)) {
		results_found = true;
	}
	mysql_free_result(result);
	return results_found;
}

template<typename T>
void DatabaseRepository<T>::add(const T& element) {
	if (contains(element)) {
		throw Exception(2, "Element already exists");
	}
	string query{ "INSERT INTO " + TABLE_TRENCH_COATS +
	" (" + COLUMN_QUANTITY + ", " +
	COLUMN_SIZE + ", " +
	COLUMN_PRICE + ", " +
	COLUMN_COLOR + ", " +
	COLUMN_PHOTO + ") " +
	"VALUES (" + to_string(element.get_quantity()) + ", " + to_string(element.get_size()) + ", " +
	to_string(element.get_price()) + ", '" + element.get_color() + "', '" + element.get_photo() + "')" };
	mysql_query(this->connection, query.c_str());
	this->sz++;
}

template<typename T>
void DatabaseRepository<T>::update(const T& old_element, const T& new_element) {
	if (!contains(old_element)) {
		throw Exception(2, "Old element not found");
	}
	string query{ "UPDATE " + TABLE_TRENCH_COATS + " SET " +
	COLUMN_QUANTITY + "=" + to_string(new_element.get_quantity()) + ", " +
	COLUMN_SIZE + "=" + to_string(new_element.get_size()) + ", " +
	COLUMN_PRICE + "=" + to_string(new_element.get_price()) + ", " +
	COLUMN_COLOR + "='" + new_element.get_color() + "', " +
	COLUMN_PHOTO + "='" + new_element.get_photo() +
	"' WHERE " + COLUMN_SIZE + "=" + to_string(old_element.get_size()) +
	" AND " + COLUMN_COLOR + "='" + old_element.get_color() +
	"' AND " + COLUMN_PHOTO + "='" + old_element.get_photo() + "'" };
	mysql_query(this->connection, query.c_str());
}

template<typename T>
void DatabaseRepository<T>::remove(const T& element) {
	if (!contains(element)) {
		throw Exception(2, "Element not found");
	}
	string query{ "DELETE FROM " + TABLE_TRENCH_COATS + " WHERE " + COLUMN_SIZE + "=" + to_string(element.get_size()) + " AND " +
	COLUMN_COLOR + "='" + element.get_color() + "' AND  " + COLUMN_PHOTO + "='" + element.get_photo() + "'" };
	mysql_query(this->connection, query.c_str());
	this->sz--;
}

template<typename T>
const vector<T> DatabaseRepository<T>::get_all() const {
	vector<TrenchCoat> trench_coats;
	MYSQL_RES* result = nullptr;
	MYSQL_ROW rows{};
	string query{ "SELECT * FROM " + TABLE_TRENCH_COATS };
	mysql_query(this->connection, query.c_str());
	result = mysql_store_result(this->connection);
	if (result) {
		while (true) {
			rows = mysql_fetch_row(result);
			if (!rows) {
				break;
			}
			TrenchCoat trench_coat{ std::stoi(rows[0]), std::stod(rows[1]), std::stod(rows[2]), rows[3], rows[4] };
			trench_coats.push_back(trench_coat);
		}
	}
	mysql_free_result(result);
	return trench_coats;
}

template<typename T>
int DatabaseRepository<T>::size() const {
	return this->sz;
}

template <typename T>
DatabaseRepository<T>::~DatabaseRepository() {
	mysql_close(this->connection);
}

/*This class represents a repository of elements
stored in a file.*/
template <typename T>
class FileRepository : public Repository<T> {


protected:

	string path;

	/*Write to file the elements from the repository.
	Input: -
	Output: - */
	virtual void write() const;

	/*Clears the content of the file.
	Input: -
	Output: - */
	void clear() const;

public:

	/*Constructor for FileRepository.
	Input: path - string representing the file path.
	Output: A FileRepository object.*/
	FileRepository(const string& path, bool readable = true);

	/*Add an element to the repository and to the file.
	Input: element - a generic element.
	Output: - */
	void add(const T& element) override;

	/*Update old_element to new_element.
	Input: old_element - a generic element.
		   new_element - a generic element.
	Output: - */
	void update(const T& old_element, const T& new_element) override;

	/*Remove an element from the repository and from the file.
	Input: element - a generic element.
	Output: - */
	void remove(const T& element) override;

	/*Read from file and adds the elements found to the
	repository.
	Input: -
	Output: - */
	void read();

	/*Open the file from path with a default application.
	Input: -
	Output: - */
	void open() const noexcept;

	/*Destructor.*/
	virtual ~FileRepository() {}

};

template <typename T>
FileRepository<T>::FileRepository(const string& path, bool readable) {
	this->path = path;
	if (readable) {
		read();
	}
}

template <typename T>
void FileRepository<T>::add(const T& element) {
	Repository<T>::add(element);
	ofstream file;
	file.open(this->path.c_str(), ios::app);
	file << element << '\n';
	file.close();
}

template <typename T>
void FileRepository<T>::update(const T& old_element, const T& new_element) {
	Repository<T>::update(old_element, new_element);
	write();
}

template <typename T>
void FileRepository<T>::remove(const T& element) {
	Repository<T>::remove(element);
	write();
}

template <typename T>
void FileRepository<T>::write() const {
	ofstream file;
	file.open(this->path.c_str());
	for (const auto& element : Repository<T>::get_all()) {
		file << element << '\n';
	}
	file.close();
}

template <typename T>
void FileRepository<T>::clear()const {
	ofstream file;
	file.open(this->path.c_str(), ios::trunc);
	file.close();
}

template<typename T>
void FileRepository<T>::read() {
	ifstream file;
	file.open(this->path.c_str());
	T element;
	while (file >> element) {
		Repository<T>::add(element);
	}
	file.close();
}

template <typename T>
void FileRepository<T>::open()const noexcept {
	ShellExecuteA(nullptr, nullptr, this->path.c_str(), nullptr, nullptr, SW_SHOW);
}

/*This class represents a repository of elements
stored in a csv file.*/
template <typename T>
class CSVFileRepository : public FileRepository<T> {

public:

	/*Constructor for CSVFileRepository.
	Input: path - string representing the file path.
	Output: A CSVFileRepository object.*/
	CSVFileRepository(const string& path);

	/*Function is disabled for this class.*/
	void read() = delete;

};

template <typename T>
CSVFileRepository<T>::CSVFileRepository(const string& path) : FileRepository<T>(path, false) {
	FileRepository<T>::clear();
}

/*This class represents a repository of elements
stored in a html file.*/
template <typename T>
class HTLMFileRepository : public FileRepository<T> {


	/*Write to file the elements from the repository.
	Input: -
	Output: - */
	void write() const override;

public:

	/*Constructor for a HTLMFileRepository.
	Input: path - string representing the file path.
	Output: A HTLMFileRepository object.*/
	HTLMFileRepository(const string& path);

	/*Add an element to the repository and to the file.
	Input: element - a generic element.
	Output: - */
	void add(const T& element) override;

	/*Update old_element to new_element.
	Input: old_element - a generic element.
		   new_element - a generic element.
	Output: - */
	void update(const T& old_element, const T& new_element) override;

	/*Remove an element from the repository and from the file.
	Input: element - a generic element.
	Output: - */
	void remove(const T& element) override;

	/*Function is disabled for this class.*/
	void read() = delete;

};

template <typename T>
HTLMFileRepository<T>::HTLMFileRepository(const string& path) : FileRepository<T>(path, false) {
	FileRepository<T>::clear();
}

template <typename T>
void HTLMFileRepository<T>::add(const T& element) {
	Repository<T>::add(element);
	write();
}

template <typename T>
void HTLMFileRepository<T>::update(const T& old_element, const T& new_element) {
	Repository<T>::update(old_element, new_element);
	write();
}

template <typename T>
void HTLMFileRepository<T>::remove(const T& element) {
	Repository<T>::remove(element);
	write();
}

template <typename T>
void HTLMFileRepository<T>::write() const {
	ofstream file;
	file.open(FileRepository<T>::path.c_str());
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>TrenchCoat</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Quantity</td>\n";
	file << "<td>Size</td>\n";
	file << "<td>Price</td>\n";
	file << "<td>Color</td>\n";
	file << "<td>Photo link</td>\n";
	file << "</tr>\n";
	for (const auto& element : Repository<T>::get_all()) {
		file << "<tr>\n";
		file << "<td>" << element.get_quantity() << "</td>\n";
		file << "<td>" << element.get_size() << "</td>\n";
		file << "<td>" << element.get_price() << "</td>\n";
		file << "<td style=\"color:" << element.get_color() << ";\">" << element.get_color() << "</td>\n";
		file << "<td><a href=\"" << element.get_photo() << "\">Link</a></td>\n";
		file << "</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}
