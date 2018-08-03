#include "UdpServer.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/map.hpp>
#include "Student.h"
#include "Book.h"
#include "DigiLib.h"



UdpServer::UdpServer(boost::asio::io_service &io_service)
	: m_ioService(io_service)
	, m_socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), c_serverPort))
	, m_buffer()
	, m_senderEndpoint()
	, m_studentMap()
	,m_bookMap()
	,m_digiLibMap()
{
	doReceive();
}

UdpServer::~UdpServer() {
}

void UdpServer::onReceive(boost::system::error_code ec, std::size_t bytes_received)
{
	if (!ec && bytes_received > 0)
	{	
		std::string const message(m_buffer.data(), bytes_received);
		parseMessage(message, m_senderEndpoint);
	}
	doReceive();
}
void UdpServer::doReceive() {
	m_socket.async_receive_from(
		boost::asio::buffer(m_buffer, c_maxLength),
		m_senderEndpoint,
		std::bind(&UdpServer::onReceive, this, std::placeholders::_1, std::placeholders::_2));
}

void UdpServer::parseMessage(std::string const &message, boost::asio::ip::udp::endpoint const &sender)
{
	std::vector<std::string> dataVector;
	std::string const &messageType = message.substr(0, 1);
	if (messageType == "R") {
		// register a new client
		std::string const &clientname = message.substr(1);
		registerClient(clientname, sender);
	}
	else {

		dataVector = parseData(message);
		processData(dataVector);
	}
}


void UdpServer::processData( std::vector<std::string> vec) {
	int roleId = convertStringToInt(vec[1]);
	int taskId = convertStringToInt(vec[2]);

	switch (roleId) {
	case 1:
		adminData(taskId,vec);
		break;
	case 2:
		studentData(taskId,vec);
		break;

	}
}

template<class input>
void UdpServer::serializeData(input &vector) {
	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << vector;
	sendMessageToClients(archive_stream.str());
}

void UdpServer::studentData(int &taskId, std::vector<std::string> & vec) {
    std::vector<std::string> studentDetails;
    std::vector<std::string> bookDetails;

    switch(taskId) {
	case 1: // get details of single student
	studentDetails = m_studentMap.getSingleStudentDetails(convertStringToInt(vec.at(3)));
	serializeData(studentDetails);
	break;
    
    case 2: // display single book
    bookDetails = m_bookMap.getSingleBookDetails(convertStringToInt(vec.at(3)));
    serializeData(bookDetails);
    break;
    }

}

void UdpServer::adminData(int &taskId,std::vector<std::string> & vec) {
	std::vector<std::string> studentDetails;
	std::map<int, std::vector<std::string>> allStudents;
	std::shared_ptr<Student> studentPtr;
	std::shared_ptr<Student> newstudent;
	std::vector<std::string> bookDetails;
	std::map<int, std::vector<std::string>> allBooks;
	std::shared_ptr<Book> bookPtr;
	std::shared_ptr<Book> newbook;
	std::map<int, std::vector<std::string>> allBorrowedBooks;
	std::string response;
	std::string response2;
	std::shared_ptr<DigiLib> borrowPtr;

	switch(taskId) {
	case 1: // get all students
		allStudents = m_studentMap.getAllStudentDetails();
		serializeData(allStudents);
		break;

	case 2: // get details of single student
	studentDetails = m_studentMap.getSingleStudentDetails(convertStringToInt(vec.at(3)));
	serializeData(studentDetails);
	break;

	case 3: // edit student
	studentPtr=std::make_shared<Student>(convertStringToInt(vec.at(3)), vec.at(4), vec.at(5), vec.at(6));
	studentDetails=m_studentMap.editStudent(studentPtr);
	serializeData(studentDetails);
	break;

	case 4: //delete student
		if (m_studentMap.deleteStudent(convertStringToInt(vec.at(3))))
			sendMessageToClients("Student deleted successfully.");
		else
		{
			sendMessageToClients("No student found with requested id. Please enter correct id.");

		}
		break;
	case 5: // add student
		newstudent = std::make_shared<Student>(convertStringToInt(vec.at(3)), vec.at(4), vec.at(5), vec.at(6));
		response=m_studentMap.insertStudent(newstudent);
		sendMessageToClients(response);
		break;

	case 6: // get all books
		allBooks = m_bookMap.getAllBookDetails();
		serializeData(allBooks);
		break;

	case 7: // add new book
		newbook = std::make_shared<Book>(convertStringToInt(vec.at(3)), vec.at(4), vec.at(5), vec.at(6), vec.at(7), vec.at(8));
		response = m_bookMap.insertBook(newbook);
		sendMessageToClients(response);
		break;

	case 8: // edit book
		bookPtr = std::make_shared<Book>(convertStringToInt(vec.at(3)), vec.at(4), vec.at(5), vec.at(6), vec.at(7), vec.at(8));
		bookDetails = m_bookMap.editBook(bookPtr);
		serializeData(bookDetails);
		break;

	case 9: // mark book as borrowed
		response2 = m_bookMap.markBookBorrowed(convertStringToInt(vec.at(3)), vec.at(4));
		//sendMessageToClients(response2);
		borrowPtr = std::make_shared<DigiLib>(convertStringToInt(vec.at(3)), vec.at(5), vec.at(6));
		response = m_digiLibMap.markBookBorrowed(borrowPtr);
		sendMessageToClients(response);
		break;

	case 10: // get all borrowed books
		allBooks = m_digiLibMap.getAllBorrowedBookDetails();
		serializeData(allBooks);
		break;

	case 11: // display single book
		bookDetails = m_bookMap.getSingleBookDetails(convertStringToInt(vec.at(3)));
		serializeData(bookDetails);
		//sendMessageToClients(studentDetails);
		break;
	}
}


template<typename Out>
void UdpServer::split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> UdpServer::parseData( std::string st) {
	std::vector<std::string> elems;
	split(st,',', std::back_inserter(elems));
	return elems;
}

void UdpServer::registerClient(std::string const &clientName, boost::asio::ip::udp::endpoint const &sender)
{
	//std::cout << "Register new client " << clientName << " with endpoint " << sender << std::endl;
	m_registeredClients[clientName] = sender;
}


template<class input>
void UdpServer::sendMessageToClients(input const &text)
{
	//std::cout << "Will send the message " << text << " to all clients." << std::endl;
	//for (auto const &it : m_registeredClients)
	//{
		m_socket.send_to(boost::asio::buffer(text), m_senderEndpoint);
	//}

}

int UdpServer::convertStringToInt(std::string &num) {
	try {
		int data = boost::lexical_cast<int>(num);
		return data;
	}
	catch (boost::bad_lexical_cast const&) {
		std::cout << "Error: input string was not valid" << std::endl;
	}

}
