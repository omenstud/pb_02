#include "median.h"
#include "grade.h"

#include <stdexcept>


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

bool f_grade (double grade) {
	return grade < 6;
}