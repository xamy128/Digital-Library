#include <iostream>
#include <string>
#include <memory>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/map.hpp>

#include "UdpClient.h"
	
	UdpClient::UdpClient(std::string address, boost::asio::io_service &io_service):
	m_roleId(),
		m_taskId(),
		m_address(address),
		m_receiver_endpoint(boost::asio::ip::address_v4::from_string(address),2000),
	    m_io_service(),
		m_sender_endpoint(),
		m_socket(io_service),
		recv_buf()
	{
		std::cout << "**Welcome to Digital Library**" << std::endl;
		connectToServer();
		
	}


	void UdpClient::connectToServer() {

		std::string  send_buf = "R";

		m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);
		roleMenu();
	}

	void UdpClient::roleMenu() {

		do {
			std::cout << "Please choose you role:" << std::endl << "1. Press 1 for Admin" << std::endl << "2. Press 2 for student" << std::endl;
			std::cin >> m_roleId;
		}

		while (m_roleId != 1 && m_roleId != 2);

		switch (m_roleId) {
		case 1:
			showAdminMenu();
			break;

		case 2:
			showStudentMenu();
			break;

		}
	}


	void UdpClient::showAdminMenu() {
		std::cout << "Please choose from the menu below:" << std::endl;
		std::cout << "1. List of all students" << std::endl;
		std::cout << "2. Show single student detail" << std::endl;
		std::cout << "3. Modify student detail" << std::endl;
		std::cout << "4. Delete a student" << std::endl;
		std::cout << "5. Add new student" << std::endl;
		std::cout << "6. Show list of all books" << std::endl;
		std::cout << "7. Add new book" << std::endl;
		std::cout << "8. Modify a book" << std::endl;
		std::cout << "9. Mark book as borrowed" << std::endl;
		std::cout << "10. Show list of borrowed books" << std::endl;
		std::cout << "11. Show single book detail" << std::endl;
		std::cout << "12. To return" << std::endl;

		std::cin >> m_taskId;

		switch (m_taskId) {
		case 1:
			getAllStudentDetail();
			break;
		case 2:
			getStudent();
			break;
		case 3:
			editStudent();
			break;
		case 4:
			deleteStudent();
			break;
		case 5:
			addStudent();
			break;

		case 6:
			showAllBooks();
			break;
		case 7:
			addBook();
			break;
		case 8:
			editBook();
			break;
		case 9:
			markBookBorrowed();
			break;
		case 10:
			showAllBorrowedBooks();
			break;
		case 11:
			showSingleBook();
			break;
		case 12:
			roleMenu();
			break;

		}

	}

	void UdpClient::showStudentMenu() {
		std::cout << "Please choose from the menu below:" << std::endl;
		std::cout << "1. Show my details" << std::endl;
		std::cout << "2. Show single book details" << std::endl;
        
        std::cin >> m_taskId;

		switch (m_taskId) {
		case 1:
			getStudent();
			break;
		case 2:
			showSingleBook();
			break;
        }
    }

	//EDIT STUDENT
	void UdpClient::editStudent() {
		std::vector<std::string> vector;
		int studentId;
		std::string firstName, lastName,  department;
		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		//send_buf = ;

		do {
			std::cout << "Enter student id" << std::endl;
			std::cin >> studentId;

		} while (studentId<0 && studentId>999999);
		
		std::cout << "Enter student new information" << std::endl;
		std::cout << "Enter student firstName" << std::endl;
		std::cin >> firstName;

		std::cout << "Enter student lastName" << std::endl;
		std::cin >> lastName;

		std::cout << "Enter student department" << std::endl;
		std::cin >> department;

		send_buf = send_buf + "," + std::to_string(studentId) + "," + firstName + "," + lastName + "," + department;


		//m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << "Student information edited successfully. New student details are:" << std::endl;

		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> vector;
			displaySingleStudent(studentId,vector);
			Iscontinue();
		}
		catch (std::exception&)
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}


	}

	//DELETE STUDENT
	void UdpClient::deleteStudent() {
		int studentId;
		std::vector<std::string> vector;
		//send_buf = ;

		do {
			std::cout << "Enter student id" << std::endl;
			std::cin >> studentId;

		} while (studentId<0 && studentId>999999);

		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId) + "," + std::to_string(studentId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << received_message << std::endl;
		
		Iscontinue();
		//else
		//other data
	}

	//ADD STUDENT
	void UdpClient::addStudent() {
		int studentId;
		std::string firstName,lastName,department;
		std::string  send_buf = "E";
		send_buf.append(","+std::to_string(m_roleId) + "," +std::to_string(m_taskId));
		//send_buf = ;

		do {
			std::cout << "Enter student id" << std::endl;
			std::cin >> studentId;

		} while (studentId<0 && studentId>999999 );

		std::cout << "Enter student firstName" << std::endl;
		std::cin >> firstName;

		std::cout << "Enter student lastName" << std::endl;
		std::cin >> lastName;

		std::cout << "Enter student department" << std::endl;
		std::cin >> department;

		send_buf = send_buf + ","+std::to_string(studentId)+"," + firstName + "," + lastName + "," + department;


		//m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << "received from server: \"" << received_message << "\"" << std::endl;

		Iscontinue();
	}

	//GETSTUDENT
	void UdpClient::getStudent() {
		int studentId;
		std::vector<std::string> vector;
		//send_buf = ;

		do {
			std::cout << "Enter student id" << std::endl;
			std::cin >> studentId;

		} while (studentId<0 && studentId>999999);

		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId)+ "," + std::to_string(studentId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		//std::cout << "received from server: \"" << received_message << "\"" << std::endl;
		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> vector;
			displaySingleStudent(studentId, vector);
			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}
	}

	//GET ALL STUDENTS
	void UdpClient::getAllStudentDetail(){
		std::map<int, std::vector<std::string>> map;
		//send_buf = ;

	std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		//std::cout << "received from server: \"" << received_message << "\"" << std::endl;
		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> map;
			displayAllStudentData(map);
		
			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}
	}
	
	//DISPLAY ALL STUDENT DATA
	void UdpClient::displayAllStudentData(std::map<int, std::vector<std::string>> map) {
		std::map<int, std::vector<std::string>>::iterator itr;
		std::cout << "List of all students" << std::endl;
		std::cout << "StudentID		First Name		Last Name		Department" << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
		for (itr = map.begin();itr != map.end();itr++) {
			std::cout << itr->first << "               ";
			for (std::vector<std::string>::iterator it = itr->second.begin();it != itr->second.end();it++) {
				std::cout << *it << "		         ";
			}
            std::cout << std::endl;
		}
        std::cout << "------------------------------------------------------------------------------" << std::endl;
		
	}

	//DISPLAY SINGLE STUDENT DATA
	void UdpClient::displaySingleStudent(int studentId, std::vector<std::string> &vector) 
    {
		std::cout << "StudentID		 First Name		 Last Name		  Department" << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        std::cout << studentId << "             ";
			for (std::vector<std::string>::iterator it = vector.begin();it != vector.end();it++) {
				std::cout << *it << "		";
		}
        std::cout << std::endl;
		
	}


	//GET ALL BOOKS

	void UdpClient::showAllBooks() {
		std::map<int, std::vector<std::string>> bMap;
		//send_buf = ;

		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		//std::cout << "received from server: \"" << received_message << "\"" << std::endl;
		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> bMap;
			displayAllBookData(bMap);

			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}
	}

	void UdpClient::displayAllBookData(std::map<int, std::vector<std::string>> bMap) {
		std::map<int, std::vector<std::string>>::iterator itr;
		std::cout << "List of all books" << std::endl;
		std::cout << "BookID		Book Title          Book Author	         Book ISBN		 Book Type	   Book Availability" << std::endl;
		std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
		for (itr = bMap.begin(); itr != bMap.end(); itr++) {
			std::cout << itr->first << "                   "; 
			for (std::vector<std::string>::iterator it = itr->second.begin(); it != itr->second.end(); it++) {
				std::cout << *it << "                    ";
			}
			std::cout << std::endl;
		}

		std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
	}



	//SHOW SINGLE BOOK
	void UdpClient::showSingleBook() {
		int bookId;
		std::vector<std::string> vector;
		//send_buf = ;

		do {
			std::cout << "Enter Book Id" << std::endl;
			std::cin >> bookId;

		} while (bookId<0 && bookId>999999);

		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId) + "," + std::to_string(bookId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		//std::cout << "received from server: \"" << received_message << "\"" << std::endl;
		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> vector;
				displaySingleBook(bookId, vector);
			//archive >> vector;
			//displaySingleBook(vector);
			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}
	}

	//ADD NEW BOOK

	void UdpClient::addBook() {
		int bookId;
		std::string bookTitle, bookAuthor, bookISBN, bookType, bookAvailability;
		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		//send_buf = ;

		do {
			std::cout << "Enter Book Id" << std::endl;
			std::cin >> bookId;

		} while (bookId<0 && bookId>999999);

		std::cout << "Enter Book Title" << std::endl;
		std::cin >> bookTitle;

		std::cout << "Enter Book Author Name" << std::endl;
		std::cin >> bookAuthor;

		std::cout << "Enter Book ISBN" << std::endl;
		std::cin >> bookISBN;

		std::cout << "Enter Book Type" << std::endl;
		std::cin >> bookType;

		std::cout << "Enter Book Availability (Yes/No)" << std::endl;
		std::cin >> bookAvailability;

		send_buf = send_buf + "," + std::to_string(bookId) + "," + bookTitle + "," + bookAuthor + "," + bookISBN + "," + bookType + "," + bookAvailability;


		//m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << "received from server: \"" << received_message << "\"" << std::endl;

		Iscontinue();
	}

	// EDIT BOOK

	void UdpClient::editBook() {
		std::vector<std::string> vector;
		int bookId;
		std::string bookTitle, bookAuthor, bookISBN, bookType, bookAvailability;
		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		//send_buf = ;

		do {
			std::cout << "Enter Book Id" << std::endl;
			std::cin >> bookId;

		} while (bookId<0 && bookId>999999);

		std::cout << "Enter book new information" << std::endl;
		std::cout << "Enter book Title" << std::endl;
		std::cin >> bookTitle;

		std::cout << "Enter book Author" << std::endl;
		std::cin >> bookAuthor;

		std::cout << "Enter book ISBN" << std::endl;
		std::cin >> bookISBN;

		std::cout << "Enter book Type" << std::endl;
		std::cin >> bookType;

		std::cout << "Enter book Availability" << std::endl;
		std::cin >> bookAvailability;

		send_buf = send_buf + "," + std::to_string(bookId) + "," + bookTitle + "," + bookAuthor + "," + bookISBN + "," + bookType + "," + bookAvailability;


		//m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << "Book information edited successfully. New Book details are:" << std::endl;

		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> vector;
			displaySingleBook(bookId, vector);
			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}


	}

	void UdpClient::displaySingleBook(int bookId, std::vector<std::string> &vector) 
	{
		std::cout << "BookID		Book Title          Book Author	         Book ISBN		 Book Type	   Book Availability" << std::endl;
		std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << bookId << "             ";
		for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++) {
			std::cout << *it << "		        ";
		}
		std::cout << std::endl;
		
	}


	//MARK BOOK AS BORROWED
	void UdpClient::markBookBorrowed() {
		std::vector<std::string> vector;
		int bookId, studentId;
		std::string bookAvailability, borrowDate;
		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		//send_buf = ;

		do {
			std::cout << "Enter Book Id" << std::endl;
			std::cin >> bookId;

		} while (bookId < 0 && bookId>999999);

		do {
			std::cout << "Book Availability (Yes/No) : " << std::endl;
			std::cin >> bookAvailability;
		} while (bookAvailability != "Yes" && bookAvailability != "yes" && bookAvailability != "No" && bookAvailability != "no");

		if (bookAvailability == "No" || bookAvailability == "no") {

			do {
				std::cout << "Enter Student Id of the borrower" << std::endl;
				std::cin >> studentId;
			} while (studentId < 0 && studentId>999999);

				std::cout << "Enter Borrow Date (DD/MM/YY)" << std::endl;
				std::cin >> borrowDate;
		}

		else {
			showAdminMenu(); //going back to previous menu
		}

		send_buf = send_buf + "," + std::to_string(bookId) + "," + bookAvailability + "," + std::to_string(studentId) + "," + borrowDate;


		//m_socket.open(boost::asio::ip::udp::v4());

		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		std::cout << "Book marked as borrowed successfully." << std::endl;
		Iscontinue();

	}

	//GET ALL BORROWED BOOKS
	void UdpClient::showAllBorrowedBooks() {
		std::map<int, std::vector<std::string>> borrowMap;
		//send_buf = ;

		std::string  send_buf = "E";
		send_buf.append("," + std::to_string(m_roleId) + "," + std::to_string(m_taskId));
		m_socket.send_to(boost::asio::buffer(send_buf), m_receiver_endpoint);

		size_t const len = m_socket.receive_from(
			boost::asio::buffer(recv_buf), m_sender_endpoint);

		std::string const received_message(recv_buf.data(), len);
		//std::cout << "received from server: \"" << received_message << "\"" << std::endl;
		try
		{
			std::string archive_data(received_message);
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> borrowMap;
			displayAllBorrowedBookData(borrowMap);

			Iscontinue();
		}
		catch (std::exception& )
		{
			// Unable to decode data.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			return;
		}
	}

	void UdpClient::displayAllBorrowedBookData(std::map<int, std::vector<std::string>> borrowMap) {
		std::map<int, std::vector<std::string>>::iterator itr;
		std::cout << "List of all borrowed books" << std::endl;
		std::cout << "BookID		Student ID          BorrowDate" << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		for (itr = borrowMap.begin(); itr != borrowMap.end(); itr++) {
			std::cout << itr->first << "           ";
			for (std::vector<std::string>::iterator it = itr->second.begin(); it != itr->second.end(); it++) {
				std::cout << *it << "		";
			}
		}
		std::cout << std::endl;
	}

	// CONTINUE??
	void UdpClient::Iscontinue() {
		char ch = 'h';


		do {
			std::cout << "Do you wish to continue? Press 'y' or 'n' " << std::endl;
			std::cin >> ch;

		} while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N');

		if (ch == 'y' || ch == 'Y') {
			if (m_roleId == 1)
				showAdminMenu();

			if (m_roleId == 2)
				showStudentMenu();
			//show student menu
		}

		else
			roleMenu();


	}