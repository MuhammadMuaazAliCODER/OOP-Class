#include <iostream>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    int totalClasses;
    int* attendance;     // Dynamic Array

public:
    static int studentCount;

    // Default Constructor
    Student() {
        rollNo = 0;
        name = "Unknown";
        totalClasses = 0;
        attendance = nullptr;
        studentCount++;
    }

    // Parameterized Constructor
    Student(int r, string n, int classes) {
        rollNo = r;
        name = n;
        totalClasses = classes;

        attendance = new int[totalClasses];
        for(int i = 0; i < totalClasses; i++)
            attendance[i] = 0;

        studentCount++;
    }

    // Copy Constructor (Deep Copy)
    Student(const Student& s) {
        rollNo = s.rollNo;
        name = s.name;
        totalClasses = s.totalClasses;

        attendance = new int[totalClasses];
        for(int i = 0; i < totalClasses; i++)
            attendance[i] = s.attendance[i];

        studentCount++;
    }

    // Assignment Operator (Deep Copy)
    Student& operator=(const Student& s) {
        if(this != &s) {
            delete[] attendance;

            rollNo = s.rollNo;
            name = s.name;
            totalClasses = s.totalClasses;

            attendance = new int[totalClasses];
            for(int i = 0; i < totalClasses; i++)
                attendance[i] = s.attendance[i];
        }
        return *this;   // Cascaded calls
    }

    // Destructor
    ~Student() {
        delete[] attendance;
    }

    // Mark Attendance
    void markAttendance(int day, int status) {
        if(day >= 0 && day < totalClasses)
            attendance[day] = status;
    }

    // Calculate Percentage (Const Function)
    double calculatePercentage() const {
        int present = 0;
        for(int i = 0; i < totalClasses; i++)
            if(attendance[i] == 1)
                present++;

        if(totalClasses == 0) return 0;

        return (double)present / totalClasses * 100;
    }

    // [] Operator Overloading
    int operator[](int index) const {
        if(index >= 0 && index < totalClasses)
            return attendance[index];
        return -1;
    }

    // Output Operator Overloading (Friend Function)
    friend ostream& operator<<(ostream& out, const Student& s) {
        out << "Roll No: " << s.rollNo << endl;
        out << "Name: " << s.name << endl;
        out << "Attendance %: " << s.calculatePercentage() << "%" << endl;
        return out;
    }
};

// Initialize Static Member
int Student::studentCount = 0;

int main() {

    // Create Student
    Student s1(101, "Muaaz", 5);

    // Mark Attendance
    s1.markAttendance(0, 1);
    s1.markAttendance(1, 1);
    s1.markAttendance(2, 0);
    s1.markAttendance(3, 1);
    s1.markAttendance(4, 1);

    // Using Pointer (Arrow Operator)
    Student* ptr = &s1;

    cout << *ptr << endl;

    // Using [] operator
    cout << "Day 1 Status: " << s1[0] << endl;

    cout << "Total Students Created: "
         << Student::studentCount << endl;

    return 0;
}