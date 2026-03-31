/*
=============================================================================
  HOTEL MANAGEMENT SYSTEM
  Covers: Pointers, Dynamic Memory, OOP Concepts, Classes, Constructors,
          Destructors, Copy Constructors, Operator Overloading, Static Members,
          Const Members, Friend Functions, Arrow Operator, new/delete,
          File Handling, Access Modifiers, Encapsulation, Abstraction, etc.
=============================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// ============================================================
// WEEK 1 - CLO1: Utility / Helper
// ============================================================
void clearScreen() {
    cout << "\n------------------------------------------------------------\n";
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ============================================================
// WEEK 1 - CLO1: Base concept - Protection, Encapsulation,
//                Abstraction via Class
// ============================================================

// Forward declaration (used for friend function later)
class Room;

// ============================================================
// CLASS: Guest
// Covers: Week 1 (CLO1) - Migration from struct to class
//         Week 2 (CLO2) - Constructors, Copy Constructor, Destructor
//         Week 3 (CLO2) - Accessors, objects as return type
//         Week 4 (CLO3) - const members, this pointer
//         Week 5 (CLO3) - dynamic memory with new/delete
//         Week 6 (CLO3) - Operator Overloading
// ============================================================
class Guest {
private:
    // Private data members - Encapsulation (Week 1)
    int    id;
    char*  name;       // dynamic char array - Week 5
    char*  cnic;
    int    roomNumber;
    float  totalBill;

    // Static member - shared across all objects (Week 4)
    static int guestCount;

public:
    // ---- Default Constructor (Week 1 - implicitly available, Week 2 - programmer defined) ----
    Guest() {
        id         = 0;
        name       = new char[50];   // dynamic allocation - Week 5
        cnic       = new char[20];
        strcpy(name, "Unknown");
        strcpy(cnic, "00000-0000000-0");
        roomNumber = 0;
        totalBill  = 0.0f;
        guestCount++;
        cout << "[Guest Default Constructor Called]\n";
    }

    // ---- Parameterized Constructor (overloaded - Week 2) ----
    Guest(int _id, const char* _name, const char* _cnic, int _room)
        : id(_id), roomNumber(_room), totalBill(0.0f)   // initializer list - Week 3/4
    {
        name = new char[strlen(_name) + 1];   // deep copy allocation - Week 2
        cnic = new char[strlen(_cnic) + 1];
        strcpy(name, _name);
        strcpy(cnic, _cnic);
        guestCount++;
        cout << "[Guest Parameterized Constructor Called for: " << name << "]\n";
    }

    // ---- Copy Constructor - Deep Copy (Week 2) ----
    Guest(const Guest& other)
        : id(other.id), roomNumber(other.roomNumber), totalBill(other.totalBill)
    {
        // Deep copy of dynamic memory (not shallow) - Week 2
        name = new char[strlen(other.name) + 1];
        cnic = new char[strlen(other.cnic) + 1];
        strcpy(name, other.name);
        strcpy(cnic, other.cnic);
        guestCount++;
        cout << "[Guest Copy Constructor Called]\n";
    }

    // ---- Destructor (Week 1 implicitly available, Week 2 programmer defined) ----
    ~Guest() {
        cout << "[Guest Destructor Called for: " << name << "]\n";
        delete[] name;   // free dynamic memory - Week 5
        delete[] cnic;
        guestCount--;
    }

    // ---- Assignment Operator Overload (Week 2, Week 6) ----
    Guest& operator=(const Guest& other) {
        if (this == &other) return *this;   // self-assignment check, this pointer - Week 4
        delete[] name;
        delete[] cnic;
        id         = other.id;
        roomNumber = other.roomNumber;
        totalBill  = other.totalBill;
        name = new char[strlen(other.name) + 1];
        cnic = new char[strlen(other.cnic) + 1];
        strcpy(name, other.name);
        strcpy(cnic, other.cnic);
        cout << "[Assignment Operator Called]\n";
        return *this;
    }

    // ---- Equality Operator Overload as member (Week 6) ----
    bool operator==(const Guest& other) const {
        return (id == other.id);
    }

    // ---- Addition Operator: add to bill (Week 6) ----
    Guest& operator+=(float amount) {
        totalBill += amount;
        return *this;   // cascaded calls - Week 6
    }

    // ---- Accessors (Week 3 - CLO2) ----
    int   getId()         const { return id; }
    const char* getName() const { return name; }
    const char* getCnic() const { return cnic; }
    int   getRoomNumber() const { return roomNumber; }
    float getTotalBill()  const { return totalBill; }

    // ---- Mutators ----
    void setId(int _id)              { id = _id; }
    void setName(const char* _name)  { delete[] name; name = new char[strlen(_name)+1]; strcpy(name,_name); }
    void setRoomNumber(int r)        { roomNumber = r; }
    void addToBill(float amount)     { totalBill += amount; }

    // ---- Static member accessor (Week 4) ----
    static int getGuestCount() { return guestCount; }

    // ---- Display (Utility method - Week 3) ----
    void display() const {
        cout << "  ID        : " << id         << "\n";
        cout << "  Name      : " << name       << "\n";
        cout << "  CNIC      : " << cnic       << "\n";
        cout << "  Room No   : " << roomNumber << "\n";
        cout << "  Total Bill: Rs. " << totalBill << "\n";
    }

    // ---- Output Operator Overload as friend (Week 6) ----
    friend ostream& operator<<(ostream& out, const Guest& g);

    // ---- Save guest to file (Text File Handling) ----
    void saveToFile() const {
        ofstream file("guests.txt", ios::app);
        if (file.is_open()) {
            file << id << "," << name << "," << cnic << ","
                 << roomNumber << "," << totalBill << "\n";
            file.close();
        }
    }
};

// Static member definition (Week 4)
int Guest::guestCount = 0;

// Friend function definition (Week 6)
ostream& operator<<(ostream& out, const Guest& g) {
    out << "Guest[" << g.id << "] " << g.name
        << " | Room: " << g.roomNumber
        << " | Bill: Rs." << g.totalBill;
    return out;
}

// ============================================================
// CLASS: Room
// Covers: Week 1-6 concepts, const members, static members,
//         operator overloading, friend functions
// ============================================================
class Room {
private:
    int         number;
    string      type;        // "Single", "Double", "Suite"
    float       pricePerNight;
    bool        isOccupied;
    static int  totalRooms;  // Week 4 - static member

public:
    // ---- Constructor with initializer list (Week 3/4) ----
    Room() : number(0), type("Standard"), pricePerNight(1000.0f), isOccupied(false) {
        totalRooms++;
    }

    Room(int _num, const string& _type, float _price)
        : number(_num), type(_type), pricePerNight(_price), isOccupied(false)
    {
        totalRooms++;
    }

    // ---- Copy Constructor ----
    Room(const Room& other)
        : number(other.number), type(other.type),
          pricePerNight(other.pricePerNight), isOccupied(other.isOccupied)
    {
        totalRooms++;
    }

    // ---- Destructor ----
    ~Room() {
        totalRooms--;
    }

    // ---- Accessors (Week 3) ----
    int    getNumber()       const { return number; }
    string getType()         const { return type; }
    float  getPrice()        const { return pricePerNight; }
    bool   getIsOccupied()   const { return isOccupied; }

    // ---- Mutators ----
    void checkIn()  { isOccupied = true; }
    void checkOut() { isOccupied = false; }

    // ---- Static accessor (Week 4) ----
    static int getTotalRooms() { return totalRooms; }

    // ---- Comparison operator as member (Week 6) ----
    bool operator==(const Room& other) const {
        return number == other.number;
    }

    // ---- Less-than operator (Week 6) ----
    bool operator<(const Room& other) const {
        return pricePerNight < other.pricePerNight;
    }

    // ---- Display ----
    void display() const {
        cout << "  Room No   : " << number        << "\n";
        cout << "  Type      : " << type          << "\n";
        cout << "  Price/Night: Rs. " << pricePerNight << "\n";
        cout << "  Status    : " << (isOccupied ? "Occupied" : "Available") << "\n";
    }

    // ---- Friend operator<< (Week 6 - friend function) ----
    friend ostream& operator<<(ostream& out, const Room& r);

    // ---- Save to file ----
    void saveToFile() const {
        ofstream file("rooms.txt", ios::app);
        if (file.is_open()) {
            file << number << "," << type << "," << pricePerNight
                 << "," << isOccupied << "\n";
            file.close();
        }
    }
};

int Room::totalRooms = 0;

ostream& operator<<(ostream& out, const Room& r) {
    out << "Room[" << r.number << "] " << r.type
        << " Rs." << r.pricePerNight << "/night"
        << " | " << (r.isOccupied ? "Occupied" : "Available");
    return out;
}

// ============================================================
// CLASS: Booking
// Covers: Objects as members (Week 4), const members,
//         Arrow operator usage (Week 5), new/delete (Week 5)
// ============================================================
class Booking {
private:
    int     bookingId;
    int     guestId;
    int     roomNumber;
    int     nights;
    float   totalCost;
    string  checkInDate;
    string  checkOutDate;

    static int bookingCount;

public:
    Booking()
        : bookingId(0), guestId(0), roomNumber(0),
          nights(0), totalCost(0.0f),
          checkInDate("N/A"), checkOutDate("N/A")
    {
        bookingCount++;
    }

    Booking(int bId, int gId, int rNum, int n, float price,
            const string& cIn, const string& cOut)
        : bookingId(bId), guestId(gId), roomNumber(rNum),
          nights(n), totalCost(n * price),
          checkInDate(cIn), checkOutDate(cOut)
    {
        bookingCount++;
    }

    ~Booking() { bookingCount--; }

    // Accessors
    int    getBookingId()   const { return bookingId; }
    int    getGuestId()     const { return guestId; }
    int    getRoomNumber()  const { return roomNumber; }
    int    getNights()      const { return nights; }
    float  getTotalCost()   const { return totalCost; }
    string getCheckIn()     const { return checkInDate; }
    string getCheckOut()    const { return checkOutDate; }

    static int getBookingCount() { return bookingCount; }

    void display() const {
        cout << "  Booking ID  : " << bookingId   << "\n";
        cout << "  Guest ID    : " << guestId     << "\n";
        cout << "  Room Number : " << roomNumber  << "\n";
        cout << "  Nights      : " << nights      << "\n";
        cout << "  Check-In    : " << checkInDate << "\n";
        cout << "  Check-Out   : " << checkOutDate<< "\n";
        cout << "  Total Cost  : Rs. " << totalCost << "\n";
    }

    // Operator == as member
    bool operator==(const Booking& other) const {
        return bookingId == other.bookingId;
    }

    // Save to file
    void saveToFile() const {
        ofstream file("bookings.txt", ios::app);
        if (file.is_open()) {
            file << bookingId << "," << guestId << "," << roomNumber << ","
                 << nights << "," << totalCost << ","
                 << checkInDate << "," << checkOutDate << "\n";
            file.close();
        }
    }

    friend ostream& operator<<(ostream& out, const Booking& b);
};

int Booking::bookingCount = 0;

ostream& operator<<(ostream& out, const Booking& b) {
    out << "Booking[" << b.bookingId << "] Guest:" << b.guestId
        << " Room:" << b.roomNumber << " Nights:" << b.nights
        << " Cost:Rs." << b.totalCost;
    return out;
}

// ============================================================
// CLASS: Hotel (Main controller class)
// Covers: dynamic arrays (new/delete - Week 5), arrow operator,
//         static members, all Week 1-6 topics
// ============================================================
class Hotel {
private:
    string   hotelName;
    int      maxRooms;
    int      maxGuests;
    int      maxBookings;

    Room**    rooms;      // dynamic array of Room pointers - Week 5 (arrow operator)
    Guest**   guests;     // dynamic array of Guest pointers - Week 5
    Booking** bookings;   // dynamic array of Booking pointers

    int roomCount;
    int guestCount;
    int bookingIdCounter;

public:
    // Constructor - allocates dynamic arrays (Week 5)
    Hotel(const string& name, int maxR = 10, int maxG = 20, int maxB = 50)
        : hotelName(name), maxRooms(maxR), maxGuests(maxG), maxBookings(maxB),
          roomCount(0), guestCount(0), bookingIdCounter(1)
    {
        rooms    = new Room*[maxRooms];       // array of pointers - Week 5
        guests   = new Guest*[maxGuests];
        bookings = new Booking*[maxBookings];

        // Initialize to nullptr
        for (int i = 0; i < maxRooms;    i++) rooms[i]    = nullptr;
        for (int i = 0; i < maxGuests;   i++) guests[i]   = nullptr;
        for (int i = 0; i < maxBookings; i++) bookings[i] = nullptr;

        cout << "\n[Hotel '" << hotelName << "' Created Successfully]\n";
        initializeDefaultRooms();
    }

    // Destructor - frees all dynamic memory (Week 2, Week 5)
    ~Hotel() {
        for (int i = 0; i < maxRooms; i++)
            if (rooms[i]) delete rooms[i];   // delete each Room object - Week 5
        for (int i = 0; i < maxGuests; i++)
            if (guests[i]) delete guests[i];
        for (int i = 0; i < maxBookings; i++)
            if (bookings[i]) delete bookings[i];

        delete[] rooms;      // delete arrays
        delete[] guests;
        delete[] bookings;
        cout << "[Hotel Destructor Called - Memory Freed]\n";
    }

    // Initialize some default rooms
    void initializeDefaultRooms() {
        addRoom(101, "Single",  1500.0f);
        addRoom(102, "Single",  1500.0f);
        addRoom(201, "Double",  2500.0f);
        addRoom(202, "Double",  2500.0f);
        addRoom(301, "Suite",   5000.0f);
        cout << "[Default Rooms Initialized]\n";
    }

    // ---- Add Room (uses arrow operator -> Week 5) ----
    bool addRoom(int num, const string& type, float price) {
        if (roomCount >= maxRooms) {
            cout << "Max room limit reached!\n";
            return false;
        }
        rooms[roomCount] = new Room(num, type, price);   // new - Week 5
        rooms[roomCount]->saveToFile();                  // arrow operator -> - Week 5
        roomCount++;
        return true;
    }

    // ---- Find Room by number ----
    Room* findRoom(int num) {
        for (int i = 0; i < roomCount; i++)
            if (rooms[i]->getNumber() == num)   // arrow operator -> - Week 5
                return rooms[i];
        return nullptr;
    }

    // ---- Find Guest by ID ----
    Guest* findGuest(int id) {
        for (int i = 0; i < guestCount; i++)
            if (guests[i]->getId() == id)       // arrow operator ->
                return guests[i];
        return nullptr;
    }

    // ---- Check In a Guest ----
    bool checkIn(int guestId, const char* name, const char* cnic,
                 int roomNum, int nights,
                 const string& checkInDate, const string& checkOutDate)
    {
        Room* room = findRoom(roomNum);
        if (!room) {
            cout << "Room " << roomNum << " not found!\n";
            return false;
        }
        if (room->getIsOccupied()) {   // arrow operator ->
            cout << "Room " << roomNum << " is already occupied!\n";
            return false;
        }
        if (guestCount >= maxGuests) {
            cout << "Max guest limit reached!\n";
            return false;
        }

        // Create Guest dynamically (Week 5 - new operator)
        guests[guestCount] = new Guest(guestId, name, cnic, roomNum);
        guests[guestCount]->saveToFile();
        guestCount++;

        // Create Booking dynamically
        int bCount = Booking::getBookingCount();
        bookings[bCount] = new Booking(bookingIdCounter++, guestId,
                                       roomNum, nights,
                                       room->getPrice(),
                                       checkInDate, checkOutDate);
        bookings[bCount]->saveToFile();

        // Add bill to guest using += operator (Week 6)
        Guest* g = findGuest(guestId);
        if (g) {
            *g += bookings[bCount]->getTotalCost();   // Week 6 - operator+=
        }

        room->checkIn();   // mark room as occupied
        cout << "\nCheck-In Successful!\n";
        cout << *bookings[bCount] << "\n";   // operator<< Week 6
        return true;
    }

    // ---- Check Out a Guest ----
    bool checkOut(int guestId) {
        Guest* guest = findGuest(guestId);
        if (!guest) {
            cout << "Guest with ID " << guestId << " not found!\n";
            return false;
        }

        Room* room = findRoom(guest->getRoomNumber());
        if (room) room->checkOut();

        cout << "\n=== Check-Out Details ===\n";
        cout << *guest << "\n";   // operator<< Week 6
        guest->display();

        // Update file record
        guest->saveToFile();

        cout << "\nCheck-Out Successful!\n";
        return true;
    }

    // ---- Display All Rooms ----
    void displayAllRooms() const {
        cout << "\n====== ROOMS (" << roomCount << " total) ======\n";
        for (int i = 0; i < roomCount; i++) {
            cout << *rooms[i] << "\n";   // operator<< Week 6
        }
        cout << "Total Room objects: " << Room::getTotalRooms() << "\n";
    }

    // ---- Display Available Rooms ----
    void displayAvailableRooms() const {
        cout << "\n====== AVAILABLE ROOMS ======\n";
        bool found = false;
        for (int i = 0; i < roomCount; i++) {
            if (!rooms[i]->getIsOccupied()) {
                rooms[i]->display();
                cout << "---\n";
                found = true;
            }
        }
        if (!found) cout << "No available rooms!\n";
    }

    // ---- Display All Guests ----
    void displayAllGuests() const {
        cout << "\n====== GUESTS (" << guestCount << " checked in) ======\n";
        for (int i = 0; i < guestCount; i++) {
            cout << *guests[i] << "\n";
        }
        cout << "Total Guest objects alive: " << Guest::getGuestCount() << "\n";
    }

    // ---- Display All Bookings ----
    void displayAllBookings() const {
        int total = Booking::getBookingCount();
        cout << "\n====== BOOKINGS (" << total << " total) ======\n";
        for (int i = 0; i < total; i++) {
            if (bookings[i])
                cout << *bookings[i] << "\n";
        }
    }

    // ---- Read from files ----
    void readGuestsFromFile() const {
        ifstream file("guests.txt");
        if (!file.is_open()) {
            cout << "No guest records file found.\n";
            return;
        }
        cout << "\n=== Guest Records from File ===\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }

    void readBookingsFromFile() const {
        ifstream file("bookings.txt");
        if (!file.is_open()) {
            cout << "No booking records file found.\n";
            return;
        }
        cout << "\n=== Booking Records from File ===\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }

    // ---- Clear old data files ----
    static void clearDataFiles() {
        ofstream("guests.txt",   ios::trunc).close();
        ofstream("rooms.txt",    ios::trunc).close();
        ofstream("bookings.txt", ios::trunc).close();
        cout << "[Data files cleared]\n";
    }

    string getName() const { return hotelName; }
};

// ============================================================
// WEEK 6 - CLO3: Standalone Friend Operator (non-member)
// Compare two Hotel names with == as a free function
// ============================================================
bool hotelNamesMatch(const Hotel& a, const Hotel& b) {
    return a.getName() == b.getName();
}

// ============================================================
// MENU SYSTEM
// ============================================================
void displayMenu() {
    clearScreen();
    cout << "   *** HOTEL MANAGEMENT SYSTEM ***\n";
    clearScreen();
    cout << "  1. Check In Guest\n";
    cout << "  2. Check Out Guest\n";
    cout << "  3. View All Rooms\n";
    cout << "  4. View Available Rooms\n";
    cout << "  5. View All Guests\n";
    cout << "  6. View All Bookings\n";
    cout << "  7. View Guest Records (from File)\n";
    cout << "  8. View Booking Records (from File)\n";
    cout << "  9. Demonstrate Operator Overloading (Week 6)\n";
    cout << "  0. Exit\n";
    clearScreen();
    cout << "  Enter your choice: ";
}

void demonstrateOperators() {
    cout << "\n=== OPERATOR OVERLOADING DEMO (Week 6) ===\n\n";

    // Create guests on stack
    Guest g1(101, "Ali Hassan",   "12345-1234567-1", 201);
    Guest g2(102, "Sara Khan",    "22345-2234567-2", 301);

    // operator+=
    g1 += 500.0f;
    g1 += 200.0f;
    cout << "\nAfter += 500 and += 200: " << g1 << "\n";

    // operator=  (assignment)
    Guest g3 = g1;
    cout << "After copy via =: " << g3 << "\n";

    // operator==
    if (g1 == g3)
        cout << "g1 == g3 : TRUE (same ID)\n";
    if (!(g1 == g2))
        cout << "g1 == g2 : FALSE (different IDs)\n";

    // Room operators
    Room r1(401, "Single", 1200.0f);
    Room r2(402, "Suite",  6000.0f);

    cout << "\n" << r1 << "\n";
    cout << r2 << "\n";

    if (r1 < r2)
        cout << "Room " << r1.getNumber() << " is cheaper than Room " << r2.getNumber() << "\n";

    cout << "\n[g1, g2 destructors will be called at end of this function]\n";
}

// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {
    // Clear old data files at startup
    Hotel::clearDataFiles();

    // Create Hotel object on heap using new (Week 5)
    Hotel* hotel = new Hotel("Grand Pearl Hotel");   // new operator - Week 5

    int choice = -1;

    while (choice != 0) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            // --- Check In ---
            clearScreen();
            cout << "=== CHECK IN GUEST ===\n";

            int gId, roomNum, nights;
            char name[100], cnic[25];
            string checkIn, checkOut;

            cout << "Guest ID     : "; cin >> gId;
            cin.ignore();
            cout << "Guest Name   : "; cin.getline(name, 100);
            cout << "CNIC         : "; cin.getline(cnic, 25);

            hotel->displayAvailableRooms();
            cout << "Room Number  : "; cin >> roomNum;
            cout << "Nights       : "; cin >> nights;
            cin.ignore();
            cout << "Check-In Date (e.g. 2025-01-01) : "; getline(cin, checkIn);
            cout << "Check-Out Date                  : "; getline(cin, checkOut);

            hotel->checkIn(gId, name, cnic, roomNum, nights, checkIn, checkOut);

        } else if (choice == 2) {
            // --- Check Out ---
            clearScreen();
            cout << "=== CHECK OUT GUEST ===\n";
            int gId;
            cout << "Enter Guest ID: "; cin >> gId;
            hotel->checkOut(gId);

        } else if (choice == 3) {
            hotel->displayAllRooms();

        } else if (choice == 4) {
            hotel->displayAvailableRooms();

        } else if (choice == 5) {
            hotel->displayAllGuests();

        } else if (choice == 6) {
            hotel->displayAllBookings();

        } else if (choice == 7) {
            hotel->readGuestsFromFile();

        } else if (choice == 8) {
            hotel->readBookingsFromFile();

        } else if (choice == 9) {
            demonstrateOperators();

        } else if (choice == 0) {
            cout << "\nThank you for using Hotel Management System!\n";
            cout << "Saving and shutting down...\n";

        } else {
            cout << "Invalid choice! Try again.\n";
        }

        if (choice != 0) pauseScreen();
    }

    // delete hotel pointer - frees all dynamic memory (Week 5)
    delete hotel;   // arrow operator used internally, destructor called here

    cout << "\n[All memory freed. Program ended cleanly.]\n";
    return 0;
}