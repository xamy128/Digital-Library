#pragma once

#include <string>
#include <iostream>

class Book {
private:
	int m_bookId;
	std::string  m_bookTitle, m_bookAuthor, m_bookISBN, m_bookType, m_bookAvailability;

public:
	Book() :
		m_bookId()
		, m_bookTitle()
		, m_bookAuthor()
		, m_bookISBN()
		, m_bookType()
		, m_bookAvailability()
	{
		std::cout << "Book Default constructor called" << std::endl;
	}

	Book(Book &book) {
		m_bookId = book.m_bookId;
		m_bookTitle = book.m_bookTitle;
		m_bookAuthor = book.m_bookAuthor;
		m_bookISBN = book.m_bookISBN;
		m_bookType = book.m_bookType;
		m_bookAvailability = book.m_bookAvailability;
	}

	Book(int bookId, std::string bookTitle, std::string bookAuthor, std::string bookISBN, std::string bookType, std::string bookAvailability) :
		m_bookId(bookId), m_bookTitle(bookTitle), m_bookAuthor(bookAuthor), m_bookISBN(bookISBN), m_bookType(bookType), m_bookAvailability(bookAvailability)
	{

	}

	~Book()
	{
		std::cout << "Book destroyed" << std::endl;
	}

	//setters

	void setbookId(int bookId) {
		m_bookId = bookId;
	}

	void setbookTitle(std::string bookTitle) {
		m_bookTitle = bookTitle;
	}

	void setbookAuthor(std::string bookAuthor) {
		m_bookAuthor = bookAuthor;
	}

	void setbookISBN(std::string bookISBN) {
		m_bookISBN = bookISBN;
	}

	void setbookType(std::string bookType) {
		m_bookType = bookType;
	}

	void setbookAvailability(std::string bookAvailability) {
		m_bookAvailability = bookAvailability;
	}

	//getters

	int bookId() {
		return m_bookId;
	}

	std::string getbookTitle() {
		return m_bookTitle;
	}

	std::string getbookAuthor() {
		return m_bookAuthor;
	}

	std::string getbookISBN() {
		return m_bookISBN;
	}

	std::string getbookType() {
		return m_bookType;
	}

	std::string getbookAvailability() {
		return m_bookAvailability;
	}

};