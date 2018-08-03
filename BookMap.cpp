#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "BookMap.h" 

BookMap::BookMap() :
	bookMap(),
	m_key(),
	m_bookTitle(),
	m_bookAuthor(),
	m_bookISBN(),
	m_bookType(),
	m_bookAvailability()

{};


BookMap::BookMap(int id, std::string title, std::string author, std::string isbn, std::string bookType, std::string availability) :
	bookMap(),
	m_key(id),
	m_bookTitle(title),
	m_bookAuthor(author),
	m_bookISBN(isbn),
	m_bookType(bookType),
	m_bookAvailability(availability)
{
	;
}

std::string BookMap::insertBook(std::shared_ptr<Book> &book) {

	std::map<int, std::vector<std::string>>::iterator itr = bookMap.find(book->bookId());
	if (itr == bookMap.end()) {
		bookMap[book->bookId()].push_back(book->getbookTitle());
		bookMap[book->bookId()].push_back(book->getbookAuthor());
		bookMap[book->bookId()].push_back(book->getbookISBN());
		bookMap[book->bookId()].push_back(book->getbookType());
		bookMap[book->bookId()].push_back(book->getbookAvailability());
		return "Book Added Successfully";
	}
	else
	{
		return "Book already exists";
	}
}


bool BookMap::deleteBook(int bookId) {
	bool isDelete;
	std::map<int, std::vector<std::string>>::iterator itr = bookMap.find(bookId);
	if (itr != bookMap.end()) {
		bookMap.erase(itr);
		return isDelete = true;
	}
	else isDelete = false;
}

std::map<int, std::vector<std::string>> BookMap::getAllBookDetails() {
	return bookMap;
}

std::vector<std::string> BookMap::getSingleBookDetails(int bookId) {
	try {
		std::vector<std::string> vec;
		std::map<int, std::vector<std::string>>::iterator it = bookMap.find(bookId);
		if (it != bookMap.end())
			return bookMap.at(bookId);
		else
			vec.push_back("Book Id not found");
	}
	catch (std::exception e) {
		//return book not found statement from here.
		std::cout << "Enter correct book Id. Requested book Id not found" << std::endl;
	}

}

std::vector<std::string> BookMap::editBook(std::shared_ptr<Book> &book) {
	std::vector<std::string> vector;

	std::map<int, std::vector<std::string>>::iterator itr = bookMap.find(book->bookId());
	if (itr != bookMap.end()) {
		vector.push_back(book->getbookTitle());
		vector.push_back(book->getbookAuthor());
		vector.push_back(book->getbookISBN());
		vector.push_back(book->getbookType());
		vector.push_back(book->getbookAvailability());
		itr->second = vector;
		return vector;
	}
	else {
		vector.push_back("No book found with requested id. Please enter correct id");
		return vector;
	}
}

std::string BookMap::markBookBorrowed(int bookId, std::string bookAvailability) {
	try {
		std::vector<std::string> vec;
		std::map<int, std::vector<std::string>>::iterator it = bookMap.find(bookId);
		if (it != bookMap.end()) {
			it->second[4] = bookAvailability;
			return "Book borrowed succesfully";
		}
		else {
			return "Book ID not found";
		}
	}
	catch (std::exception e) {
		std::cout << "unable to borrow book";
	}
}





