#pragma once

#include <string>
#include <iostream>

class Admin {
private:
	int m_adminId;
	std::string  m_firstName, m_lastName;

public:
	Admin() :
		m_adminId()
		, m_firstName()
		, m_lastName()
	
	{
		std::cout << "Default constructor called" << std::endl;
	}

	Admin(Admin &admin) {
		m_adminId = admin.m_adminId;
		m_firstName = admin.m_firstName;
		m_lastName = admin.m_lastName;
		
	}

	Admin(int adminId, std::string firstName, std::string lastName) :
		m_adminId(adminId), m_firstName(firstName), m_lastName(m_lastName)
	{

	}

	~Admin()
	{
		std::cout << "Admin destroyed" << std::endl;
	}

	void editStudentId(int adminId) {
		m_adminId = adminId;
	}

	void editFirstName(std::string firstName) {
		m_firstName = firstName;
	}

	void editLastName(std::string lastName) {
		m_lastName = lastName;
	}

	int getAdminId() {
		return m_adminId;
	}

	std::string getFirstName() {
		return m_firstName;
	}

	std::string getLastName() {
		return m_lastName;
	}

};