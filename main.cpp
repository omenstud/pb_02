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

	printStudents(students, maxlen);
	
	std::vector<Student_info> incompleteStudents = extractIncomplete(students);
	printIncompleteStudents(incompleteStudents);

	return 0;
}