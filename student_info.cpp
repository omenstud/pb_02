#include "student_info.h"
#include "locale_string.h"
#include "grade.h"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <list>
#include <string>
#include <vector>


//==============================================================================
std::istream& read_hw (std::istream& in, std::vector<double>& hw) {
	if (in) {
		hw.clear();
		
		for (double x; in >> x;) hw.push_back(x);

		in.clear();
	}
	return in;
}


//==============================================================================
std::istream& read (std::istream& is, Student_info& s) {
	is >> s.name >> s.midterm >> s.final;
	read_hw(is, s.homework);

	return is;
}


//==============================================================================
bool compare (const Student_info& x, const Student_info& y) {
	return x.name < y.name;
}

void printExeption(const Student_info &student, std::size_t columnSize, const char* exception) {
	std::cout << student.name << std::string(columnSize + 2 - string_lenght(student.name), ' ') << exception;

	std::cout << std::endl;
}

void printStudentMidGrade(const Student_info &student, std::size_t columnSize, double grade) {
	std::cout << student.name << std::string(columnSize + 2 - string_lenght(student.name), ' ');

	std::streamsize prec = std::cout.precision();
	std::cout << std::setprecision(3) << grade << std::setprecision(prec);

	std::cout << std::endl;
}

void printStudentName(const Student_info &student) {
	std::cout << student.name << std::endl;
}

void printFailedStudents(std::vector<Student_info>& failedStudents) {
	std::cout << std::endl << "Неаттестованы:" << std::endl;

	for (Student_info student : failedStudents) {
		printStudentName(student);
	}
}

void printIncompleteStudents(std::vector<Student_info>& incompleteStudents) {
	std::cout << std::endl << "Выполнили не все работы:" << std::endl;

	for (Student_info student : incompleteStudents) {
		printStudentName(student);
	}
}

void printStudents(std::vector<Student_info>& students, size_t maxlen) {
	for (std::size_t i = 0; i != students.size(); ++i) {
		try {
			printStudentMidGrade(students[i], maxlen, grade(students[i]));
		} catch (std::domain_error e) {
			printExeption(students[i], maxlen, e.what());
		}
	}
}

std::vector<Student_info> extract_fails(std::vector<Student_info>& students) {
	std::vector<Student_info> failedStudents;

	for (std::size_t i = 0; i != students.size(); ++i) {
		try {
			if (f_grade(grade(students[i]))) {
				failedStudents.push_back(students[i]);
				students.erase(students.begin() + i);
			}
		} catch (std::domain_error e) {
			failedStudents.push_back(students[i]);
			students.erase(students.begin() + i);
		}
	}

	return failedStudents;
}

std::vector<Student_info> extractIncomplete(std::vector<Student_info>& students) {
	std::vector<Student_info> incomplete;

	std::remove_copy_if(students.begin(), students.end(), std::back_inserter(incomplete), isStudentCompletedAllTasks);

	return incomplete;
}