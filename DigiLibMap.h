#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "DigiLib.h"
#include "StudentMap.h"
#include "BookMap.h"

class DigiLibMap {
private:
	std::map<int, std::vector<std::string>> digiLibMap;
	BookMap bMap;
	StudentMap sMap;
	std::string m_borrowDate;


public:
	DigiLibMap();

	std::string markBookBorrowed(std::shared_ptr<DigiLib> &borrow);

	std::map<int, std::vector<std::string>> getAllBorrowedBookDetails();

};