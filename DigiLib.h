#pragma once

#include <string>
#include <iostream>
#include "Book.h"
#include "Student.h"

class DigiLib {
private:
	int b_bookId;
	std::string b_studentId,b_borrowDate;
	Book book;
	Student student;
	


public:
	DigiLib() :
		b_bookId()
		, b_studentId()
		, b_borrowDate()
		, book()
		, student()


	{
		std::cout << "DigiLib Default constructor called" << std::endl;
	}

	DigiLib(DigiLib &digilib) {
		b_bookId = digilib.b_bookId;
		b_studentId = digilib.b_studentId;
		b_borrowDate = digilib.b_borrowDate;		

	}

	DigiLib(int bookId, std::string studentId, std::string borrowDate) :
		b_bookId(bookId),b_studentId(studentId), b_borrowDate(borrowDate)
	{

	}

	~DigiLib()
	{
		std::cout << "DigiLib destroyed" << std::endl;
	}

	//setters

	void setborrowDate(std::string borrowDate) {
		b_borrowDate = borrowDate;
	}


	//getters

	int getbookId() {
		return b_bookId;
	}

	std::string getstudentId() {
		return b_studentId;
	}

	Book getbook() {
		return book;
	}

	Student getstudent() {
		return student;
	}

	std::string getborrowDate() {
		return b_borrowDate;
	}

};