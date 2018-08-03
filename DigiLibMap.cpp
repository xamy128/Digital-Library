#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "DigiLibMap.h" 
#include "BookMap.h"

DigiLibMap::DigiLibMap() :

	digiLibMap(),
	bMap(),
	sMap(),
	m_borrowDate()

{};


std::string DigiLibMap::markBookBorrowed(std::shared_ptr<DigiLib> &borrow) {
	std::map<int, std::vector<std::string>>::iterator itr = digiLibMap.find(borrow -> getbookId());
	if (itr == digiLibMap.end()) {
		digiLibMap[borrow->getbookId()].push_back(borrow->getstudentId());
		digiLibMap[borrow->getbookId()].push_back(borrow->getborrowDate());
		return "Book Borrowed Successfully";
	}
	else
	{
		return "Book already borrowed";
	}

}

std::map<int, std::vector<std::string>> DigiLibMap::getAllBorrowedBookDetails()
{
	return digiLibMap;

}



