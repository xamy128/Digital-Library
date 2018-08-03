#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "Student.h"

class StudentMap {
private:
	std::map<int, std::vector<std::string>> studentMap;
	int m_key;
	std::string m_firstName;
	std::string m_lastName;
	std::string m_department;


public:
	StudentMap();
	StudentMap(int id, std::string firstName, std::string lastName, std::string department);
	
	std::string insertStudent(std::shared_ptr<Student> &student);

	bool StudentMap::deleteStudent(int studentId);

	std::map<int, std::vector<std::string>> getAllStudentDetails();
    
	std::vector<std::string> getSingleStudentDetails(int studentId);

	std::vector<std::string> editStudent(std::shared_ptr<Student> &student);

};