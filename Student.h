#pragma once

#include <string>
#include <iostream>

class Student {
private:
	int m_studentId;
	std::string  m_firstName, m_lastName, m_department;

public:
	Student():
		m_studentId()
		,m_firstName()
		, m_lastName()
		, m_department()
	{
		std::cout << "Default constructor called" << std::endl;
	}

	Student(Student &student) {
		m_studentId = student.m_studentId;
		m_firstName = student.m_firstName;
		m_lastName = student.m_lastName;
		m_department = student.m_department;
	}

	Student(int studentId, std::string firstName, std::string lastName, std::string department) :
		m_studentId(studentId), m_firstName(firstName), m_lastName(lastName), m_department(department)
	{

	}

	~Student() 
	{
		//std::cout << "Student destroyed" << std::endl;
	}

	void editStudentId(int studentId) {
		m_studentId = studentId;
	}

	void editFirstName(std::string firstName) {
		m_firstName = firstName;
	}

	void editLastName(std::string lastName) {
		m_lastName = lastName;
	}

	void editDepartment(std::string department) {
		m_department = department;
	}

	int studentId() {
		return m_studentId;
	}

	std::string getFirstName() {
		return m_firstName;
	}

	std::string getLastName() {
		return m_lastName;
	}

	std::string getDepartment() {
		return m_department;
	}

};