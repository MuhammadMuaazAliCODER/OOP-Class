#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Date
{
private:
    int day, month, year;

public:
    Date();
    Date(int d, int m, int y);
    Date(const Date &d);
    ~Date();

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDate(int d, int m, int y);
    void display() const;

    bool operator==(const Date &d) const;

    friend ostream &operator<<(ostream &out, const Date &d);
};

Date::Date() : day(1), month(1), year(2024) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const Date &d) : day(d.day), month(d.month), year(d.year) {}

Date::~Date() {}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void Date::display() const { cout << day << "/" << month << "/" << year; }

bool Date::operator==(const Date &d) const
{
    return (day == d.day && month == d.month && year == d.year);
}

ostream &operator<<(ostream &out, const Date &d)
{
    out << d.day << "/" << d.month << "/" << d.year;
    return out;
}

class Room
{
private:
    int roomNumber;
    string roomType;
    float rentPerMonth;
    bool isOccupied;

    static int totalRooms;

public:
    Room();
    Room(int num, string type, float rent);
    Room(const Room &r);
    ~Room();

    Room &operator=(const Room &r);

    int getRoomNumber() const;
    string getRoomType() const;
    float getRent() const;
    bool getIsOccupied() const;

    void setOccupied(bool status);
    void setRoomNumber(int n);
    void setRoomType(string t);
    void setRent(float r);

    static int getTotalRooms();

    bool operator==(const Room &r) const;

    friend ostream &operator<<(ostream &out, const Room &r);

    void display() const;
};

int Room::totalRooms = 0;

Room::Room() : roomNumber(0), roomType("Single"), rentPerMonth(0.0f), isOccupied(false)
{
    totalRooms++;
}

Room::Room(int num, string type, float rent)
    : roomNumber(num), roomType(type), rentPerMonth(rent), isOccupied(false)
{
    totalRooms++;
}

Room::Room(const Room &r)
    : roomNumber(r.roomNumber), roomType(r.roomType),
      rentPerMonth(r.rentPerMonth), isOccupied(r.isOccupied)
{
    totalRooms++;
}

Room::~Room()
{
    totalRooms--;
}

Room &Room::operator=(const Room &r)
{
    if (this != &r)
    {
        roomNumber = r.roomNumber;
        roomType = r.roomType;
        rentPerMonth = r.rentPerMonth;
        isOccupied = r.isOccupied;
    }
    return *this;
}

int Room::getRoomNumber() const { return roomNumber; }
string Room::getRoomType() const { return roomType; }
float Room::getRent() const { return rentPerMonth; }
bool Room::getIsOccupied() const { return isOccupied; }

void Room::setOccupied(bool status) { isOccupied = status; }
void Room::setRoomNumber(int n) { roomNumber = n; }
void Room::setRoomType(string t) { roomType = t; }
void Room::setRent(float r) { rentPerMonth = r; }

int Room::getTotalRooms() { return totalRooms; }

bool Room::operator==(const Room &r) const
{
    return roomNumber == r.roomNumber;
}

ostream &operator<<(ostream &out, const Room &r)
{
    out << "Room #" << r.roomNumber
        << " [" << r.roomType << "]"
        << "  Rent: PKR " << r.rentPerMonth << "/month"
        << "  Status: " << (r.isOccupied ? "Occupied" : "Available");
    return out;
}

void Room::display() const { cout << *this << endl; }

class Student
{
private:
    int studentId;
    char *name;
    string cnic;
    string contact;
    Room room;
    Date joinDate;
    float totalFeesPaid;

    static int studentCount;

public:
    Student();
    Student(int id, const char *n, string c, string con, Room r, Date d);
    Student(const Student &s);
    ~Student();

    Student &operator=(const Student &s);

    int getId() const;
    string getName() const;
    string getCnic() const;
    string getContact() const;
    Room getRoom() const;
    Date getJoinDate() const;
    float getTotalFeesPaid() const;

    void setContact(string c);
    void setRoom(const Room &r);

    Student &payFees(float amount);
    Student &updateContact(string c);

    static int getStudentCount();

    bool operator==(const Student &s) const;

    friend ostream &operator<<(ostream &out, const Student &s);

    void display() const;
};

int Student::studentCount = 0;

Student::Student()
    : studentId(0), name(nullptr), cnic(""), contact(""),
      room(), joinDate(), totalFeesPaid(0.0f)
{
    name = new char[1];
    name[0] = '\0';
    studentCount++;
}

Student::Student(int id, const char *n, string c, string con, Room r, Date d)
    : studentId(id), cnic(c), contact(con),
      room(r), joinDate(d), totalFeesPaid(0.0f)
{

    name = new char[strlen(n) + 1];
    strcpy(name, n);
    studentCount++;
}

Student::Student(const Student &s)
    : studentId(s.studentId), cnic(s.cnic), contact(s.contact),
      room(s.room), joinDate(s.joinDate), totalFeesPaid(s.totalFeesPaid)
{
    name = new char[strlen(s.name) + 1];
    strcpy(name, s.name);
    studentCount++;
}

Student::~Student()
{
    delete[] name;
    studentCount--;
}

Student &Student::operator=(const Student &s)
{
    if (this != &s)
    {
        delete[] name;
        name = new char[strlen(s.name) + 1];
        strcpy(name, s.name);
        studentId = s.studentId;
        cnic = s.cnic;
        contact = s.contact;
        room = s.room;
        joinDate = s.joinDate;
        totalFeesPaid = s.totalFeesPaid;
    }
    return *this;
}

int Student::getId() const { return studentId; }
string Student::getName() const { return string(name); }
string Student::getCnic() const { return cnic; }
string Student::getContact() const { return contact; }
Room Student::getRoom() const { return room; }
Date Student::getJoinDate() const { return joinDate; }
float Student::getTotalFeesPaid() const { return totalFeesPaid; }

void Student::setContact(string c) { contact = c; }
void Student::setRoom(const Room &r) { room = r; }

Student &Student::payFees(float amount)
{
    totalFeesPaid += amount;
    return *this;
}
Student &Student::updateContact(string c)
{
    contact = c;
    return *this;
}

int Student::getStudentCount() { return studentCount; }

bool Student::operator==(const Student &s) const
{
    return studentId == s.studentId;
}

ostream &operator<<(ostream &out, const Student &s)
{
    out << "ID: " << s.studentId
        << " | Name: " << s.name
        << " | CNIC: " << s.cnic
        << " | Contact: " << s.contact
        << " | Room: " << s.room.getRoomNumber()
        << " | Joined: " << s.joinDate
        << " | Fees Paid: PKR " << s.totalFeesPaid;
    return out;
}

void Student::display() const
{
    cout << "\n-------- Student Details --------" << endl;
    cout << *this << endl;
    cout << "Room Info: " << room << endl;
    cout << "---------------------------------" << endl;
}

class Hostel
{
private:
    string hostelName;
    Student **students;
    Room *rooms;
    int maxStudents;
    int maxRooms;
    int currentStudents;
    int currentRooms;

    static int hostelCount;
    const string dataFile;

    Room *findRoom(int roomNum);
    Student *findStudent(int id);

public:
    Hostel(string name, int maxS, int maxR);
    ~Hostel();

    void initializeRooms();

    void addRoom(int num, string type, float rent);
    void displayAllRooms() const;
    void displayAvailableRooms() const;

    void addStudent(int id, const char *name, string cnic,
                    string contact, int roomNum, Date joinDate);
    void removeStudent(int id);
    void searchStudent(int id) const;
    void displayAllStudents() const;

    void collectFees(int id, float amount);

    void displayStats() const;
    string getHostelName() const;

    void saveToFile() const;
    void loadFromFile();

    static int getHostelCount();

    friend ostream &operator<<(ostream &out, const Hostel &h);
};

int Hostel::hostelCount = 0;

Hostel::Hostel(string name, int maxS, int maxR)
    : hostelName(name), maxStudents(maxS), maxRooms(maxR),
      currentStudents(0), currentRooms(0), dataFile("hostel_data.txt")
{

    students = new Student *[maxStudents];
    rooms = new Room[maxRooms];

    for (int i = 0; i < maxStudents; i++)
        students[i] = nullptr;
    hostelCount++;
    initializeRooms();
}

Hostel::~Hostel()
{
    for (int i = 0; i < currentStudents; i++)
    {
        delete students[i];
    }
    delete[] students;
    delete[] rooms;
    hostelCount--;
}

void Hostel::initializeRooms()
{
    string types[] = {"Single", "Double", "Triple"};
    float rents[] = {5000.0f, 8000.0f, 10000.0f};
    int limit = (maxRooms < 10) ? maxRooms : 10;

    for (int i = 0; i < limit; i++)
    {
        rooms[currentRooms] = Room(101 + i, types[i % 3], rents[i % 3]);
        currentRooms++;
    }
}

Room *Hostel::findRoom(int roomNum)
{
    for (int i = 0; i < currentRooms; i++)
    {
        if (rooms[i].getRoomNumber() == roomNum)
            return &rooms[i];
    }
    return nullptr;
}

Student *Hostel::findStudent(int id)
{
    for (int i = 0; i < currentStudents; i++)
    {
        if (students[i]->getId() == id)
            return students[i];
    }
    return nullptr;
}

void Hostel::addRoom(int num, string type, float rent)
{
    if (currentRooms >= maxRooms)
    {
        cout << "[!] No space to add more rooms!" << endl;
        return;
    }
    rooms[currentRooms] = Room(num, type, rent);
    currentRooms++;
    cout << "[+] Room added successfully!" << endl;
}

void Hostel::displayAllRooms() const
{
    cout << "\n========== ALL ROOMS ==========" << endl;
    for (int i = 0; i < currentRooms; i++)
    {
        cout << rooms[i] << endl;
    }
}

void Hostel::displayAvailableRooms() const
{
    cout << "\n======= AVAILABLE ROOMS =======" << endl;
    bool found = false;
    for (int i = 0; i < currentRooms; i++)
    {
        if (!rooms[i].getIsOccupied())
        {
            cout << rooms[i] << endl;
            found = true;
        }
    }
    if (!found)
        cout << "  No available rooms at the moment." << endl;
}

void Hostel::addStudent(int id, const char *name, string cnic,
                        string contact, int roomNum, Date joinDate)
{
    if (currentStudents >= maxStudents)
    {
        cout << "[!] Hostel is full!" << endl;
        return;
    }

    for (int i = 0; i < currentStudents; i++)
    {
        if (students[i]->getId() == id)
        {
            cout << "[!] Student ID already exists!" << endl;
            return;
        }
    }

    Room *r = findRoom(roomNum);
    if (r == nullptr)
    {
        cout << "[!] Room not found!" << endl;
        return;
    }
    if (r->getIsOccupied())
    {
        cout << "[!] Room is already occupied!" << endl;
        return;
    }

    r->setOccupied(true);

    students[currentStudents] = new Student(id, name, cnic, contact, *r, joinDate);
    currentStudents++;
    cout << "[+] Student registered successfully!" << endl;
    saveToFile();
}

void Hostel::removeStudent(int id)
{
    for (int i = 0; i < currentStudents; i++)
    {
        if (students[i]->getId() == id)
        {

            Room *r = findRoom(students[i]->getRoom().getRoomNumber());
            if (r != nullptr)
                r->setOccupied(false);

            delete students[i];

            students[i] = students[currentStudents - 1];
            students[currentStudents - 1] = nullptr;
            currentStudents--;
            cout << "[+] Student removed successfully!" << endl;
            saveToFile();
            return;
        }
    }
    cout << "[!] Student not found!" << endl;
}

void Hostel::searchStudent(int id) const
{
    for (int i = 0; i < currentStudents; i++)
    {
        if (students[i]->getId() == id)
        {
            students[i]->display();
            return;
        }
    }
    cout << "[!] Student not found!" << endl;
}

void Hostel::displayAllStudents() const
{
    if (currentStudents == 0)
    {
        cout << "  No students registered yet." << endl;
        return;
    }
    cout << "\n========= ALL STUDENTS =========" << endl;
    for (int i = 0; i < currentStudents; i++)
    {
        students[i]->display();
    }
}

void Hostel::collectFees(int id, float amount)
{
    Student *s = findStudent(id);
    if (s == nullptr)
    {
        cout << "[!] Student not found!" << endl;
        return;
    }

    s->payFees(amount);
    cout << "[+] PKR " << amount << " collected from " << s->getName() << endl;
    cout << "    Total paid so far: PKR " << s->getTotalFeesPaid() << endl;
    saveToFile();
}

void Hostel::displayStats() const
{
    cout << "\n======= HOSTEL STATISTICS =======" << endl;
    cout << *this << endl;
    cout << "  Room objects alive  : " << Room::getTotalRooms() << endl;
    cout << "  Student objects alive: " << Student::getStudentCount() << endl;
    cout << "  Hostel instances     : " << hostelCount << endl;
}

string Hostel::getHostelName() const { return hostelName; }
int Hostel::getHostelCount() { return hostelCount; }

ostream &operator<<(ostream &out, const Hostel &h)
{
    out << "Hostel : " << h.hostelName
        << "  |  Students: " << h.currentStudents << "/" << h.maxStudents
        << "  |  Rooms: " << h.currentRooms << "/" << h.maxRooms;
    return out;
}

void Hostel::saveToFile() const
{
    ofstream file(dataFile);
    if (!file.is_open())
    {
        cout << "[!] Cannot open file for writing!" << endl;
        return;
    }
    file << currentStudents << "\n";
    for (int i = 0; i < currentStudents; i++)
    {
        file << students[i]->getId() << "\n";
        file << students[i]->getName() << "\n";
        file << students[i]->getCnic() << "\n";
        file << students[i]->getContact() << "\n";
        file << students[i]->getRoom().getRoomNumber() << "\n";
        file << students[i]->getJoinDate().getDay() << " "
             << students[i]->getJoinDate().getMonth() << " "
             << students[i]->getJoinDate().getYear() << "\n";
        file << students[i]->getTotalFeesPaid() << "\n";
    }
    file.close();
    cout << "  [*] Data saved to '" << dataFile << "'" << endl;
}

void Hostel::loadFromFile()
{
    ifstream file(dataFile);
    if (!file.is_open())
    {
        cout << "  [*] No previous data found. Starting fresh." << endl;
        return;
    }
    int count = 0;
    file >> count;
    file.ignore();

    for (int i = 0; i < count && currentStudents < maxStudents; i++)
    {
        int id, roomNum, d, m, y;
        float fees;
        string name, cnic, contact;

        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, cnic);
        getline(file, contact);
        file >> roomNum >> d >> m >> y >> fees;
        file.ignore();

        Room *r = findRoom(roomNum);
        if (r != nullptr)
        {
            Date joinDate(d, m, y);
            r->setOccupied(true);
            students[currentStudents] = new Student(id, name.c_str(),
                                                    cnic, contact, *r, joinDate);
            students[currentStudents]->payFees(fees);
            currentStudents++;
        }
    }
    file.close();
    cout << "  [*] Data loaded from '" << dataFile << "'" << endl;
}

void displayMenu(const Hostel &h)
{
    cout << "\n============================================" << endl;
    cout << "     HOSTEL MANAGEMENT SYSTEM" << endl;
    cout << "     " << h.getHostelName() << endl;
    cout << "============================================" << endl;
    cout << " 1.  Add Student" << endl;
    cout << " 2.  Remove Student" << endl;
    cout << " 3.  Search Student" << endl;
    cout << " 4.  Display All Students" << endl;
    cout << " 5.  Display All Rooms" << endl;
    cout << " 6.  Display Available Rooms" << endl;
    cout << " 7.  Collect Fees" << endl;
    cout << " 8.  Add Room" << endl;
    cout << " 9.  Display Statistics" << endl;
    cout << " 10. Save Data to File" << endl;
    cout << " 0.  Exit" << endl;
    cout << "============================================" << endl;
    cout << " Enter your choice: ";
}

int main()
{
    cout << "\n==============================================" << endl;
    cout << "   Welcome to Hostel Management System (HMS)" << endl;
    cout << "==============================================" << endl;

    Hostel *hostel = new Hostel("Green Valley Hostel", 50, 20);

    hostel->loadFromFile();

    int choice;
    do
    {
        displayMenu(*hostel);
        cin >> choice;
        cin.ignore();

        switch (choice)
        {

        case 1:
        {

            int id, roomNum, d, m, y;
            char name[100];
            string cnic, contact;

            cout << "\n--- Add New Student ---" << endl;
            cout << "Student ID    : ";
            cin >> id;
            cin.ignore();
            cout << "Full Name     : ";
            cin.getline(name, 100);
            cout << "CNIC          : ";
            getline(cin, cnic);
            cout << "Contact No.   : ";
            getline(cin, contact);
            cout << "Room Number   : ";
            cin >> roomNum;
            cout << "Join Date (DD MM YYYY): ";
            cin >> d >> m >> y;

            Date joinDate(d, m, y);
            hostel->addStudent(id, name, cnic, contact, roomNum, joinDate);
            break;
        }

        case 2:
        {

            int id;
            cout << "Enter Student ID to remove: ";
            cin >> id;
            hostel->removeStudent(id);
            break;
        }

        case 3:
        {

            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            hostel->searchStudent(id);
            break;
        }

        case 4:
            hostel->displayAllStudents();
            break;

        case 5:
            hostel->displayAllRooms();
            break;

        case 6:
            hostel->displayAvailableRooms();
            break;

        case 7:
        {

            int id;
            float amount;
            cout << "Enter Student ID  : ";
            cin >> id;
            cout << "Enter Fee Amount  : ";
            cin >> amount;
            hostel->collectFees(id, amount);
            break;
        }

        case 8:
        {

            int num;
            string type;
            float rent;
            cout << "\n--- Add New Room ---" << endl;
            cout << "Room Number           : ";
            cin >> num;
            cin.ignore();
            cout << "Type (Single/Double/Triple): ";
            getline(cin, type);
            cout << "Rent per Month (PKR)  : ";
            cin >> rent;
            hostel->addRoom(num, type, rent);
            break;
        }

        case 9:
            hostel->displayStats();
            break;

        case 10:
            hostel->saveToFile();
            break;

        case 0:
            cout << "\nSaving and exiting..." << endl;
            hostel->saveToFile();
            break;

        default:
            cout << "[!] Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    delete hostel;

    cout << "\nThank you for using HMS. Goodbye!" << endl;
    return 0;
}
