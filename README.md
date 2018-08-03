# Digital-Library
A digital library management system in C++ using boost Library
Based on Client-Server architecture.
Client is used to access/modify the information.
  -Manage library users – Admin and Student
Admin functionalities
  -Add new book to library
  -Modify book entry
  -Show list of all books
  -Show details of a single book
  -Mark book as borrowed
  -Show list of all borrowed books
  -Add new student to library
  -Modify student entry
  -Show list of all students
  -Show details of a single student
  -Delete a student
Student functionalities
  -Show details of single student
  -Show details of a single book

Server is used to hold all the library data
  -Manages client connection
  -Communicates with client using UDP network protocol
  -Data is kept in Maps and Vectors

