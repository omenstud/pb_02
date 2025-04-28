#include "locale_string.h"
#include "grade.h"
#include "student_info.h"


#include <algorithm>
#include <iostream>
#include <vector>


//==============================================================================
int main () {
	std::vector<Student_info> students;
	std::size_t maxlen = 0;

	for (Student_info record; read(std::cin, record);) {
		maxlen = std::max(maxlen, string_lenght(record.name));
		students.push_back(record);
	}

	sort(students.begin(), students.end(), compare);

	for (std::size_t i = 0; i != students.size(); ++i) {
		try {
			double final_grade = grade(students[i]);
			printStudentMidGrade(students[i], maxlen, final_grade);
		} catch (std::domain_error e) {
			printExeption(students[i], maxlen, e.what());
		}
	}

	std::vector<Student_info> failedStudents = extract_fails(students);
	printFailedStudents(failedStudents);

	return 0;
}