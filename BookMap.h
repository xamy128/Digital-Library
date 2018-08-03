#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "Book.h"

class BookMap {
private:
	std::map<int, std::vector<std::string>> bookMap;
	int m_key;
	std::string  m_bookTitle, m_bookAuthor, m_bookISBN, m_bookType, m_bookAvailability;

	
public:
	BookMap();
	BookMap(int id, std::string title, std::string author, std::string isbn, std::string bookType, std::string availability);

	std::string insertBook(std::shared_ptr<Book> &book);

	bool deleteBook(int bookId);

	std::map<int, std::vector<std::string>> getAllBookDetails();

	std::vector<std::string> getSingleBookDetails(int bookId);

	std::vector<std::string> editBook(std::shared_ptr<Book> &book);

	std::string BookMap::markBookBorrowed(int bookId, std::string bookAvailability);
};