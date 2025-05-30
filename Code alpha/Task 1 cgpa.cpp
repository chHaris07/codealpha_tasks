#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Course {
    string name;
    double creditHours;
    double marks;
    double gradePoints;
};

double calculateGradePoints(double marks) {
    if (marks >= 90) return 4.0;
    else if (marks >= 80) return 3.5;
    else if (marks >= 70) return 3.0;
    else if (marks >= 60) return 2.5;
    else if (marks >= 50) return 2.0;
    else if (marks >= 40) return 1.0;
    else return 0.0;
}

int main() {
    cout << "------------------------------------------" << endl;
    cout << "        CGPA Calculator Application       " << endl;
    cout << "------------------------------------------" << endl;

    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    while (numCourses <= 0) {
        cout << "Number of courses must be positive. Please enter again: ";
        cin >> numCourses;
    }

    vector<Course> courses(numCourses);

    double totalCreditHours = 0.0;
    double totalWeightedGradePoints = 0.0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nEnter details for Course " << i + 1 << ":" << endl;

        cin.ignore();

        cout << "  Course Name: ";
        getline(cin, courses[i].name);

        cout << "  Credit Hours: ";
        cin >> courses[i].creditHours;

        while (courses[i].creditHours <= 0) {
            cout << "  Credit hours must be positive. Please enter again: ";
            cin >> courses[i].creditHours;
        }

        cout << "  Marks (out of 100): ";
        cin >> courses[i].marks;

        while (courses[i].marks < 0 || courses[i].marks > 100) {
            cout << "  Marks must be between 0 and 100. Please enter again: ";
            cin >> courses[i].marks;
        }

        courses[i].gradePoints = calculateGradePoints(courses[i].marks);

        totalCreditHours += courses[i].creditHours;
        totalWeightedGradePoints += (courses[i].gradePoints * courses[i].creditHours);
    }

    cout << "\n------------------------------------------" << endl;
    cout << "          Individual Course Grades        " << endl;
    cout << "------------------------------------------" << endl;
    cout << left << setw(25) << "Course Name"
         << setw(15) << "Credits"
         << setw(10) << "Marks"
         << setw(15) << "Grade Points" << endl;
    cout << "------------------------------------------" << endl;

    for (const auto& course : courses) {
        cout << left << setw(25) << course.name
             << setw(15) << fixed << setprecision(1) << course.creditHours
             << setw(10) << fixed << setprecision(1) << course.marks
             << setw(15) << fixed << setprecision(2) << course.gradePoints << endl;
    }
    cout << "------------------------------------------" << endl;

    double cgpa = 0.0;
    if (totalCreditHours > 0) {
        cgpa = totalWeightedGradePoints / totalCreditHours;
    }

    cout << "\n------------------------------------------" << endl;
    cout << "              CGPA Summary                " << endl;
    cout << "------------------------------------------" << endl;
    cout << "Total Credit Hours: " << fixed << setprecision(1) << totalCreditHours << endl;
    cout << "Total Weighted Grade Points: " << fixed << setprecision(2) << totalWeightedGradePoints << endl;
    cout << "Calculated CGPA: " << fixed << setprecision(2) << cgpa << endl;
    cout << "------------------------------------------" << endl;

    cout << "\nCGPA Calculator task completed." << endl;

    return 0;
}
