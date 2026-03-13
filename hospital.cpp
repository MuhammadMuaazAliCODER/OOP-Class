#include <iostream>
using namespace std;

class Patient {
private:
    int id;
    string name;
    int age;
    int totalDays;
    int* dailyCharges;   // Dynamic array

public:
    static int patientCount;

    // Default Constructor
    Patient() {
        id = 0;
        name = "Unknown";
        age = 0;
        totalDays = 0;
        dailyCharges = nullptr;
        patientCount++;
    }

    // Parameterized Constructor
    Patient(int i, string n, int a, int days) {
        id = i;
        name = n;
        age = a;
        totalDays = days;

        dailyCharges = new int[totalDays];
        for(int i = 0; i < totalDays; i++)
            dailyCharges[i] = 0;

        patientCount++;
    }

    // Copy Constructor (Deep Copy)
    Patient(const Patient& p) {
        id = p.id;
        name = p.name;
        age = p.age;
        totalDays = p.totalDays;

        dailyCharges = new int[totalDays];
        for(int i = 0; i < totalDays; i++)
            dailyCharges[i] = p.dailyCharges[i];

        patientCount++;
    }

    // Assignment Operator (Deep Copy)
    Patient& operator=(const Patient& p) {
        if(this != &p) {
            delete[] dailyCharges;

            id = p.id;
            name = p.name;
            age = p.age;
            totalDays = p.totalDays;

            dailyCharges = new int[totalDays];
            for(int i = 0; i < totalDays; i++)
                dailyCharges[i] = p.dailyCharges[i];
        }
        return *this;
    }

    // Destructor
    ~Patient() {
        delete[] dailyCharges;
    }

    // Add charge for a specific day
    void addCharge(int day, int amount) {
        if(day >= 0 && day < totalDays)
            dailyCharges[day] = amount;
    }

    // Calculate total bill (Const Function)
    int calculateBill() const {
        int total = 0;
        for(int i = 0; i < totalDays; i++)
            total += dailyCharges[i];
        return total;
    }

    // Output Operator Overloading
    friend ostream& operator<<(ostream& out, const Patient& p) {
        out << "Patient ID: " << p.id << endl;
        out << "Name: " << p.name << endl;
        out << "Age: " << p.age << endl;
        out << "Total Bill: Rs. " << p.calculateBill() << endl;
        return out;
    }
};

// Initialize static member
int Patient::patientCount = 0;

int main() {

    // Create Patient
    Patient p1(1, "Ali", 25, 3);

    // Add daily charges
    p1.addCharge(0, 2000);
    p1.addCharge(1, 3000);
    p1.addCharge(2, 2500);

    // Using Pointer (Arrow operator)
    Patient* ptr = &p1;

    cout << *ptr << endl;

    cout << "Total Patients Created: "
         << Patient::patientCount << endl;

    return 0;
    
}