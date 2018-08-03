#include <iostream>
#include <string>
#include <map>
#include "stdafx.h"
#include "Student.h"
#include "StudentMap.h"
#include "BookMap.h"
#include "Book.h"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "BoostUnitTest.h"

Student fh(9, "Khushbu", "Vadadoriya", "IE");
StudentMap sp(9, "Khushbu", "Vadadoriya", "IE");
Book bk(1, "ITPM", "Dr. K", "123456", "Management", "Y");
BookMap b(1, "ITPM", "Dr. K", "123456", "Management", "Y");

BOOST_AUTO_TEST_SUITE(BoostUnitTest)
BOOST_AUTO_TEST_CASE(check_constructor_Student)
{

	BOOST_CHECK_EQUAL(fh.getFirstName(), "Khushbu");
	BOOST_CHECK_EQUAL(fh.getLastName(), "Vadadoriya");
	BOOST_CHECK_EQUAL(fh.getDepartment(), "IE");
}

BOOST_AUTO_TEST_CASE(check_change_name)
{
	fh.editStudentId(1);
	BOOST_CHECK_EQUAL(fh.studentId(), 1);
	fh.editFirstName("Bansari");
	BOOST_CHECK_EQUAL(fh.getFirstName(), "Bansari");
	fh.editLastName("Vadgama");
	BOOST_CHECK_EQUAL(fh.getLastName(), "Vadgama");
	fh.editDepartment("Mechanical");
	BOOST_CHECK_EQUAL(fh.getDepartment(), "Mechanical");
}
BOOST_AUTO_TEST_CASE(check_construct_invalid_phone)
{
	BOOST_CHECK(fh.studentId() < 1000000);
	BOOST_TEST_MESSAGE("Student Id must be entered between 1 to 999999");
}
BOOST_AUTO_TEST_CASE(Check_delete_Student)
{
	sp.deleteStudent(9);
	bool x = sp.deleteStudent(9);
	BOOST_CHECK_NE(x, true);
	BOOST_TEST_MESSAGE("Student Deleted");
}
BOOST_AUTO_TEST_CASE(check_constructor_Book)
{
	BOOST_CHECK_EQUAL(bk.bookId(), 1);
	BOOST_CHECK_EQUAL(bk.getbookTitle(), "ITPM");
	BOOST_CHECK_EQUAL(bk.getbookAuthor(), "Dr. K");
	BOOST_CHECK_EQUAL(bk.getbookISBN(), "123456");
	BOOST_CHECK_EQUAL(bk.getbookType(), "Management");
	BOOST_CHECK_EQUAL(bk.getbookAvailability(), "Y");
}
BOOST_AUTO_TEST_CASE(check_change_Book_name)
{
	bk.setbookId(2);
	BOOST_CHECK_EQUAL(bk.bookId(), 2);
	BOOST_CHECK_EQUAL(bk.getbookTitle(), "ITPM");
	bk.setbookTitle("Advance C++");
	BOOST_REQUIRE_EQUAL(bk.getbookTitle(), "Advance C++");
	bk.setbookAuthor("Dr. A");
	BOOST_CHECK_EQUAL(bk.getbookAuthor(), "Dr. A");
	bk.setbookISBN("456789");
	BOOST_CHECK_EQUAL(bk.getbookISBN(), "456789");
	bk.setbookType("Coding");
	BOOST_CHECK_EQUAL(bk.getbookType(), "Coding");
	bk.setbookAvailability("N");
	BOOST_CHECK_EQUAL(bk.getbookAvailability(), "N");
}
BOOST_AUTO_TEST_CASE(check_size_Book_Id)
{
	BOOST_CHECK_LT(bk.bookId(), sizeof(5));
	BOOST_TEST_MESSAGE("BookId must be in less than 5 digit number.");

}
BOOST_AUTO_TEST_CASE(check_edit_Book)
{
	BOOST_CHECK_EQUAL(bk.bookId(), 2);
	bk.setbookId(3);
	BOOST_REQUIRE_EQUAL(bk.bookId(), 3);
	bk.setbookTitle("German");
	BOOST_CHECK_EQUAL(bk.getbookTitle(), "German");
	bk.setbookAuthor("Dr. C");
	BOOST_CHECK_EQUAL(bk.getbookAuthor(), "Dr. C");
	bk.setbookISBN("14567891");
	BOOST_CHECK_EQUAL(bk.getbookISBN(), "14567891");
	bk.setbookType("Language");
	BOOST_CHECK_EQUAL(bk.getbookType(), "Language");
	bk.setbookAvailability("Y");
	BOOST_CHECK_EQUAL(bk.getbookAvailability(), "Y");
	BOOST_TEST_MESSAGE("Enter Correct Book Id");
}
BOOST_AUTO_TEST_CASE(Check_delete_book)
{	b.deleteBook(1);
	bool x = b.deleteBook(1);
	BOOST_CHECK_NE(x,true);
	BOOST_TEST_MESSAGE("Book Deleted");
}

BOOST_AUTO_TEST_CASE(check_show_Book_Availablity)
{
	bk.setbookAvailability("Y");
	BOOST_CHECK_EQUAL(bk.getbookAvailability(), "Y");
	BOOST_TEST_MESSAGE(" Book Available");
}
BOOST_AUTO_TEST_CASE(check_show_Book_Availablity1)
{	
	bk.setbookAvailability("N");
	BOOST_CHECK_EQUAL(bk.getbookAvailability(), "N");
	BOOST_TEST_MESSAGE(" No Book Available");
}
BOOST_AUTO_TEST_CASE(check_getting_Book_Details)
{
	b.getAllBookDetails();
	BOOST_CHECK(b.getAllBookDetails() == b.getAllBookDetails());
}
BOOST_AUTO_TEST_SUITE_END()

namespace {
	struct F1 /*ixture*/ {
		F1() :
			fh(9, "Khushbu", "Vadadoriya", "IE") {
			;
		}

		Student fh;
	};
};

namespace {
	struct F2 {
		F2() :
			bk(1, "ITPM", "Dr. K", "123456", "Management", "Y") {
		}
		Book bk;
	};
}
namespace {
	struct F3 {
		F3() :
			b(1, "ITPM", "Dr. K", "123456", "Management", "Y") {
		}
		BookMap b;
	};
}
namespace {
	struct F4 {
		F4() :
			sp(9, "Khushbu", "Vadadoriya", "IE") {
		}
		StudentMap sp;
	};
}