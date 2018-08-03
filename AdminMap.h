#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

class AdminMap {
private:
	std::map<int, std::vector<std::string> > adminMap;
	int m_key;
	std::string m_firstName;
	std::string m_lastName;

	void insertAdmin(int key, std::string firstName, std::string lastName) {
		std::map<int, std::vector<std::string>>::iterator itr;
		adminMap[key].push_back(firstName);
		adminMap[key].push_back(lastName);

	}

	void showAllAdmins() {
		std::map<int, std::vector<std::string>>::iterator itr;
		std::cout << "List of all admins" << std::endl;
		for (itr = adminMap.begin();itr != adminMap.end();itr++) {
			std::cout << itr->first << ": ";
			for (std::vector<std::string>::iterator it = itr->second.begin();it != itr->second.end();it++) {
				std::cout << *it << ",";
			}
		}
	}


	void showSingleAdmin(int adminId) {
		std::map<int, std::vector<std::string>>::iterator itr = adminMap.find(adminId);
		std::cout << "Admin Details are:" << std::endl;
		if (itr != adminMap.end()) {
			std::cout << itr->first << ": ";
			for (std::vector<std::string>::iterator it = itr->second.begin();it != itr->second.end();it++) {
				std::cout << *it << ",";
			}
		}
	}

	void deleteAdmin(int adminId) {
		std::map<int, std::vector<std::string>>::iterator itr = adminMap.find(adminId);
		if (itr != adminMap.end())
			adminMap.erase(itr);
	}


	std::map<int, std::vector<std::string>> getAllStudentAdmins() {
		return adminMap;
	}

	std::vector<std::string> getSingleAdminDetails(int adminId) {
		std::map<int, std::vector<std::string>>::iterator it = adminMap.find(adminId);
		return it->second;
	}
};