#include "median.h"
#include "student_info.h"
#include "grade.h"

#include <algorithm>
#include <iterator>
#include <numeric>
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
double gradeStudentMedian(const Student_info& s) {
	try {
		return grade(s.midterm, s.final, s.homework);
	} catch (std::domain_error e) {
		return grade(s.midterm, s.final, 0.0);
	}
}

double gradeStudentAvg(const Student_info& s) {
	double avg = std::accumulate(s.homework.begin(), s.homework.end(), 0.0);
	return grade(s.midterm, s.final, s.homework.size() > 0 ? avg / s.homework.size() : 0.0);
}


bool f_grade (const Student_info& s) {
	return gradeStudentMedian(s) < SUCCESS_GRADE_THRESHOLD;
}

bool isStudentCompletedAllTasks(Student_info& si) {
	return (si.homework.size() >= NUM_HOMEWORKS) && !si.homework.empty() && (std::find(si.homework.begin(), si.homework.end(), 0.0) == si.homework.end());
}

double computeGradesMedian(std::vector<Student_info>& students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(grades), gradeStudentMedian);

	return median(grades);
}

double computeGradesAvg(std::vector<Student_info>& students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(grades), gradeStudentAvg);

	return median(grades);
}