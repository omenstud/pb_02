#include "median.h"
#include "student_info.h"
#include "grade.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

const int NUM_HOMEWORKS = 6;
const double SUCCESS_GRADE_THRESHOLD = 6.0;

//==============================================================================
double grade (double midterm, double final, double homework) {
	return (0.2 * midterm + 0.4 * final + 0.4 * homework);
}


//==============================================================================
double grade (double midterm, double final, const std::vector<double>& hw) {
	if (hw.size() == 0) throw std::domain_error("Отсутствуют оценки за самостоятельные работы!");

	return grade(midterm, final, median(hw));
}


//==============================================================================
double grade (const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}

double gradeFinal (const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}

bool f_grade (double grade) {
	return grade < SUCCESS_GRADE_THRESHOLD;
}

bool isStudentCompletedAllTasks(Student_info& si) {
	return (si.homework.size() >= NUM_HOMEWORKS) && !si.homework.empty() && (std::find(si.homework.begin(), si.homework.end(), 0.0) == si.homework.end());
}

double computeGradesMedian(std::vector<Student_info>& students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(students), gradeFinal);

	return median(grades);
}