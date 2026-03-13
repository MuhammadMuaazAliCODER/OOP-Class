//First Exercise 
#include <iostream>
using namespace std;

class MarksVector {
private:
    int* marks;
    int size;

public:
    // Parameterized Constructor
    MarksVector(int s) : size(s) {
        marks = new int[size];
        for(int i = 0; i < size; i++)
            marks[i] = 0;
    }

    // Copy Constructor (Deep Copy)
    MarksVector(const MarksVector& other) : size(other.size) {
        marks = new int[size];
        for(int i = 0; i < size; i++)
            marks[i] = other.marks[i];
    }

    // Assignment Operator
    MarksVector& operator=(const MarksVector& other) {
        if(this != &other) {
            delete[] marks;
            size = other.size;
            marks = new int[size];
            for(int i = 0; i < size; i++)
                marks[i] = other.marks[i];
        }
        return *this;
    }

    void setMark(int index, int value) {
        if(index >= 0 && index < size)
            marks[index] = value;
    }

    int getMark(int index) const {
        if(index >= 0 && index < size)
            return marks[index];
        return -1;
    }

    void displayMarks() const {
        for(int i = 0; i < size; i++)
            cout << marks[i] << " ";
        cout << endl;
    }

    ~MarksVector() {
        delete[] marks;
    }
};

int main() {
    MarksVector course1(3);
    course1.setMark(0, 85);
    course1.setMark(1, 90);
    course1.setMark(2, 75);

    MarksVector course2 = course1; // Deep Copy

    course2.setMark(0, 100);

    cout << "Course 1 Marks: ";
    course1.displayMarks();

    cout << "Course 2 Marks: ";
    course2.displayMarks();

    return 0;
}

// Second Exercise
#include <iostream>
using namespace std;

class SeatingMatrix {
private:
    int** matrix;
    int rows, cols;

public:
    // Default Constructor
    SeatingMatrix() : rows(0), cols(0), matrix(nullptr) {}

    // Parameterized Constructor
    SeatingMatrix(int r, int c) : rows(r), cols(c) {
        matrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            for(int j = 0; j < cols; j++)
                matrix[i][j] = 0;
        }
    }

    // Copy Constructor (Deep Copy)
    SeatingMatrix(const SeatingMatrix& other) : rows(other.rows), cols(other.cols) {
        matrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            for(int j = 0; j < cols; j++)
                matrix[i][j] = other.matrix[i][j];
        }
    }

    // Assignment Operator
    SeatingMatrix& operator=(const SeatingMatrix& other) {
        if(this != &other) {
            for(int i = 0; i < rows; i++)
                delete[] matrix[i];
            delete[] matrix;

            rows = other.rows;
            cols = other.cols;

            matrix = new int*[rows];
            for(int i = 0; i < rows; i++) {
                matrix[i] = new int[cols];
                for(int j = 0; j < cols; j++)
                    matrix[i][j] = other.matrix[i][j];
            }
        }
        return *this;
    }

    void setElement(int r, int c, int value) {
        if(r < rows && c < cols)
            matrix[r][c] = value;
    }

    int getElement(int r, int c) const {
        if(r < rows && c < cols)
            return matrix[r][c];
        return -1;
    }

    void display() const {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    ~SeatingMatrix() {
        for(int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;
    }
};

int main() {
    SeatingMatrix hall1(2, 2);
    hall1.setElement(0, 0, 101);
    hall1.setElement(1, 1, 202);

    SeatingMatrix hall2 = hall1; // Deep Copy
    hall2.setElement(0, 0, 999);

    cout << "Hall1:\n";
    hall1.display();

    cout << "Hall2:\n";
    hall2.display();

    return 0;
}

// Third Exercise

#include <iostream>
using namespace std;

class ComplexTransaction {
private:
    double real;
    double imaginary;

public:
    // Default Constructor
    ComplexTransaction() : real(0), imaginary(0) {}

    // Single Parameter Constructor
    ComplexTransaction(double r) : real(r), imaginary(0) {}

    // Two Parameter Constructor
    ComplexTransaction(double r, double i) : real(r), imaginary(i) {}

    // Copy Constructor
    ComplexTransaction(const ComplexTransaction& other)
        : real(other.real), imaginary(other.imaginary) {}

    // Assignment Operator
    ComplexTransaction& operator=(const ComplexTransaction& other) {
        if(this != &other) {
            real = other.real;
            imaginary = other.imaginary;
        }
        return *this;
    }

    ComplexTransaction add(const ComplexTransaction& other) {
        return ComplexTransaction(real + other.real,
                                  imaginary + other.imaginary);
    }

    ComplexTransaction subtract(const ComplexTransaction& other) {
        return ComplexTransaction(real - other.real,
                                  imaginary - other.imaginary);
    }

    ComplexTransaction multiply(const ComplexTransaction& other) {
        return ComplexTransaction(
            real * other.real - imaginary * other.imaginary,
            real * other.imaginary + imaginary * other.real
        );
    }

    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }

    ~ComplexTransaction() {}
};

int main() {
    ComplexTransaction t1(100, 5);
    ComplexTransaction t2(50, 3);

    ComplexTransaction result = t1.add(t2);

    result.display();

    return 0;
}

// Fourth Exercise

#include <iostream>
using namespace std;

class Date {
private:
    int day, month, year;

    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    bool isValidDate(int d, int m, int y) const {
        if(y < 1 || m < 1 || m > 12 || d < 1)
            return false;

        int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

        if(m == 2 && isLeapYear(y))
            return d <= 29;

        return d <= daysInMonth[m-1];
    }

public:
    // Default Constructor
    Date() : day(1), month(1), year(2000) {}

    // Parameterized Constructor
    Date(int d, int m, int y) : day(1), month(1), year(2000) {
        if(isValidDate(d, m, y)) {
            day = d;
            month = m;
            year = y;
        } else {
            cout << "Invalid Date! Setting default date.\n";
        }
    }

    // Copy Constructor
    Date(const Date& other)
        : day(other.day), month(other.month), year(other.year) {}

    // Assignment Operator
    Date& operator=(const Date& other) {
        if(this != &other) {
            day = other.day;
            month = other.month;
            year = other.year;
        }
        return *this;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void display() const {
        cout << day << "/" << month << "/" << year << endl;
    }

    ~Date() {}
};

int main() {
    Date d1(29, 2, 2023); // Invalid
    Date d2(29, 2, 2024); // Valid (Leap year)

    d1.display();
    d2.display();

    return 0;
}