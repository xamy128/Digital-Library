#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <map>
#include <vector>


class UdpClient {
private:
	std::string m_address;
	int m_roleId;
	int m_taskId;
	boost::asio::ip::udp::endpoint m_receiver_endpoint;
	boost::asio::ip::udp::socket m_socket;
	boost::asio::io_service m_io_service;
	boost::asio::ip::udp::endpoint m_sender_endpoint;
	std::array<char, 128> recv_buf;


public:
	
	UdpClient(std::string address, boost::asio::io_service &io_service);
	
	void roleMenu();

	void showAdminMenu();
    
    void showStudentMenu();

	void addStudent();

	void getAllStudentDetail();

	void connectToServer();

	void getStudent();

	void displayAllStudentData(std::map<int,std::vector<std::string>> map);

	void displaySingleStudent(int studentId, std::vector<std::string> &vector);

	void deleteStudent();

	void editStudent();

	void showAllBooks();

	void showSingleBook();

	void displayAllBookData(std::map<int, std::vector<std::string>> bMap);

	void displaySingleBook(int bookId, std::vector<std::string> &vector);

	void addBook();

	void editBook();

	void markBookBorrowed();

	void showAllBorrowedBooks();

	void displayAllBorrowedBookData(std::map<int, std::vector<std::string>> borrowMap);

	void Iscontinue();

};
