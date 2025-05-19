#ifndef GRADE_H
#define GRADE_H

#include "student_info.h"

#include <vector>


double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const std::vector<double>& hw);
double gradeStudentMedian(const Student_info& s);
double gradeStudentAvg(const Student_info& s);

bool f_grade(const Student_info& s);
bool isStudentCompletedAllTasks(Student_info& si);
double computeGradesMedian(std::vector<Student_info>& students);
double computeGradesAvg(std::vector<Student_info>& students);

#endif // GRADE_H
