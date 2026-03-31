

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void clearScreen()
{
    cout << "\n------------------------------------------------------------\n";
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

class Room;

class Guest
{
private:
    int id;
    char *name;
    char *cnic;
    int roomNumber;
    float totalBill;

    static int guestCount;

public:
    Guest()
    {
        id = 0;
        name = new char[50];
        cnic = new char[20];
        strcpy(name, "Unknown");
        strcpy(cnic, "00000-0000000-0");
        roomNumber = 0;
        totalBill = 0.0f;
        guestCount++;
        cout << "[Guest Default Constructor Called]\n";
    }

    Guest(int _id, const char *_name, const char *_cnic, int _room)
        : id(_id), roomNumber(_room), totalBill(0.0f)
    {
        name = new char[strlen(_name) + 1];
        cnic = new char[strlen(_cnic) + 1];
        strcpy(name, _name);
        strcpy(cnic, _cnic);
        guestCount++;
        cout << "[Guest Parameterized Constructor Called for: " << name << "]\n";
    }

    Guest(const Guest &other)
        : id(other.id), roomNumber(other.roomNumber), totalBill(other.totalBill)
    {

        name = new char[strlen(other.name) + 1];
        cnic = new char[strlen(other.cnic) + 1];
        strcpy(name, other.name);
        strcpy(cnic, other.cnic);
        guestCount++;
        cout << "[Guest Copy Constructor Called]\n";
    }

    ~Guest()
    {
        cout << "[Guest Destructor Called for: " << name << "]\n";
        delete[] name;
        delete[] cnic;
        guestCount--;
    }

    Guest &operator=(const Guest &other)
    {
        if (this == &other)
            return *this;
        delete[] name;
        delete[] cnic;
        id = other.id;
        roomNumber = other.roomNumber;
        totalBill = other.totalBill;
        name = new char[strlen(other.name) + 1];
        cnic = new char[strlen(other.cnic) + 1];
        strcpy(name, other.name);
        strcpy(cnic, other.cnic);
        cout << "[Assignment Operator Called]\n";
        return *this;
    }

    bool operator==(const Guest &other) const
    {
        return (id == other.id);
    }

    Guest &operator+=(float amount)
    {
        totalBill += amount;
        return *this;
    }

    int getId() const { return id; }
    const char *getName() const { return name; }
    const char *getCnic() const { return cnic; }
    int getRoomNumber() const { return roomNumber; }
    float getTotalBill() const { return totalBill; }

    void setId(int _id) { id = _id; }
    void setName(const char *_name)
    {
        delete[] name;
        name = new char[strlen(_name) + 1];
        strcpy(name, _name);
    }
    void setRoomNumber(int r) { roomNumber = r; }
    void addToBill(float amount) { totalBill += amount; }

    static int getGuestCount() { return guestCount; }

    void display() const
    {
        cout << "  ID        : " << id << "\n";
        cout << "  Name      : " << name << "\n";
        cout << "  CNIC      : " << cnic << "\n";
        cout << "  Room No   : " << roomNumber << "\n";
        cout << "  Total Bill: Rs. " << totalBill << "\n";
    }

    friend ostream &operator<<(ostream &out, const Guest &g);

    void saveToFile() const
    {
        ofstream file("guests.txt", ios::app);
        if (file.is_open())
        {
            file << id << "," << name << "," << cnic << ","
                 << roomNumber << "," << totalBill << "\n";
            file.close();
        }
    }
};

int Guest::guestCount = 0;

ostream &operator<<(ostream &out, const Guest &g)
{
    out << "Guest[" << g.id << "] " << g.name
        << " | Room: " << g.roomNumber
        << " | Bill: Rs." << g.totalBill;
    return out;
}

class Room
{
private:
    int number;
    string type;
    float pricePerNight;
    bool isOccupied;
    static int totalRooms;

public:
    Room() : number(0), type("Standard"), pricePerNight(1000.0f), isOccupied(false)
    {
        totalRooms++;
    }

    Room(int _num, const string &_type, float _price)
        : number(_num), type(_type), pricePerNight(_price), isOccupied(false)
    {
        totalRooms++;
    }

    Room(const Room &other)
        : number(other.number), type(other.type),
          pricePerNight(other.pricePerNight), isOccupied(other.isOccupied)
    {
        totalRooms++;
    }

    ~Room()
    {
        totalRooms--;
    }

    int getNumber() const { return number; }
    string getType() const { return type; }
    float getPrice() const { return pricePerNight; }
    bool getIsOccupied() const { return isOccupied; }

    void checkIn() { isOccupied = true; }
    void checkOut() { isOccupied = false; }

    static int getTotalRooms() { return totalRooms; }

    bool operator==(const Room &other) const
    {
        return number == other.number;
    }

    bool operator<(const Room &other) const
    {
        return pricePerNight < other.pricePerNight;
    }

    void display() const
    {
        cout << "  Room No   : " << number << "\n";
        cout << "  Type      : " << type << "\n";
        cout << "  Price/Night: Rs. " << pricePerNight << "\n";
        cout << "  Status    : " << (isOccupied ? "Occupied" : "Available") << "\n";
    }

    friend ostream &operator<<(ostream &out, const Room &r);

    void saveToFile() const
    {
        ofstream file("rooms.txt", ios::app);
        if (file.is_open())
        {
            file << number << "," << type << "," << pricePerNight
                 << "," << isOccupied << "\n";
            file.close();
        }
    }
};

int Room::totalRooms = 0;

ostream &operator<<(ostream &out, const Room &r)
{
    out << "Room[" << r.number << "] " << r.type
        << " Rs." << r.pricePerNight << "/night"
        << " | " << (r.isOccupied ? "Occupied" : "Available");
    return out;
}

class Booking
{
private:
    int bookingId;
    int guestId;
    int roomNumber;
    int nights;
    float totalCost;
    string checkInDate;
    string checkOutDate;

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
            const string &cIn, const string &cOut)
        : bookingId(bId), guestId(gId), roomNumber(rNum),
          nights(n), totalCost(n * price),
          checkInDate(cIn), checkOutDate(cOut)
    {
        bookingCount++;
    }

    ~Booking() { bookingCount--; }

    int getBookingId() const { return bookingId; }
    int getGuestId() const { return guestId; }
    int getRoomNumber() const { return roomNumber; }
    int getNights() const { return nights; }
    float getTotalCost() const { return totalCost; }
    string getCheckIn() const { return checkInDate; }
    string getCheckOut() const { return checkOutDate; }

    static int getBookingCount() { return bookingCount; }

    void display() const
    {
        cout << "  Booking ID  : " << bookingId << "\n";
        cout << "  Guest ID    : " << guestId << "\n";
        cout << "  Room Number : " << roomNumber << "\n";
        cout << "  Nights      : " << nights << "\n";
        cout << "  Check-In    : " << checkInDate << "\n";
        cout << "  Check-Out   : " << checkOutDate << "\n";
        cout << "  Total Cost  : Rs. " << totalCost << "\n";
    }

    bool operator==(const Booking &other) const
    {
        return bookingId == other.bookingId;
    }

    void saveToFile() const
    {
        ofstream file("bookings.txt", ios::app);
        if (file.is_open())
        {
            file << bookingId << "," << guestId << "," << roomNumber << ","
                 << nights << "," << totalCost << ","
                 << checkInDate << "," << checkOutDate << "\n";
            file.close();
        }
    }

    friend ostream &operator<<(ostream &out, const Booking &b);
};

int Booking::bookingCount = 0;

ostream &operator<<(ostream &out, const Booking &b)
{
    out << "Booking[" << b.bookingId << "] Guest:" << b.guestId
        << " Room:" << b.roomNumber << " Nights:" << b.nights
        << " Cost:Rs." << b.totalCost;
    return out;
}

class Hotel
{
private:
    string hotelName;
    int maxRooms;
    int maxGuests;
    int maxBookings;

    Room **rooms;
    Guest **guests;
    Booking **bookings;

    int roomCount;
    int guestCount;
    int bookingIdCounter;

public:
    Hotel(const string &name, int maxR = 10, int maxG = 20, int maxB = 50)
        : hotelName(name), maxRooms(maxR), maxGuests(maxG), maxBookings(maxB),
          roomCount(0), guestCount(0), bookingIdCounter(1)
    {
        rooms = new Room *[maxRooms];
        guests = new Guest *[maxGuests];
        bookings = new Booking *[maxBookings];

        for (int i = 0; i < maxRooms; i++)
            rooms[i] = nullptr;
        for (int i = 0; i < maxGuests; i++)
            guests[i] = nullptr;
        for (int i = 0; i < maxBookings; i++)
            bookings[i] = nullptr;

        cout << "\n[Hotel '" << hotelName << "' Created Successfully]\n";
        initializeDefaultRooms();
    }

    ~Hotel()
    {
        for (int i = 0; i < maxRooms; i++)
            if (rooms[i])
                delete rooms[i];
        for (int i = 0; i < maxGuests; i++)
            if (guests[i])
                delete guests[i];
        for (int i = 0; i < maxBookings; i++)
            if (bookings[i])
                delete bookings[i];

        delete[] rooms;
        delete[] guests;
        delete[] bookings;
        cout << "[Hotel Destructor Called - Memory Freed]\n";
    }

    void initializeDefaultRooms()
    {
        addRoom(101, "Single", 1500.0f);
        addRoom(102, "Single", 1500.0f);
        addRoom(201, "Double", 2500.0f);
        addRoom(202, "Double", 2500.0f);
        addRoom(301, "Suite", 5000.0f);
        cout << "[Default Rooms Initialized]\n";
    }

    bool addRoom(int num, const string &type, float price)
    {
        if (roomCount >= maxRooms)
        {
            cout << "Max room limit reached!\n";
            return false;
        }
        rooms[roomCount] = new Room(num, type, price);
        rooms[roomCount]->saveToFile();
        roomCount++;
        return true;
    }

    Room *findRoom(int num)
    {
        for (int i = 0; i < roomCount; i++)
            if (rooms[i]->getNumber() == num)
                return rooms[i];
        return nullptr;
    }

    Guest *findGuest(int id)
    {
        for (int i = 0; i < guestCount; i++)
            if (guests[i]->getId() == id)
                return guests[i];
        return nullptr;
    }

    bool checkIn(int guestId, const char *name, const char *cnic,
                 int roomNum, int nights,
                 const string &checkInDate, const string &checkOutDate)
    {
        Room *room = findRoom(roomNum);
        if (!room)
        {
            cout << "Room " << roomNum << " not found!\n";
            return false;
        }
        if (room->getIsOccupied())
        {
            cout << "Room " << roomNum << " is already occupied!\n";
            return false;
        }
        if (guestCount >= maxGuests)
        {
            cout << "Max guest limit reached!\n";
            return false;
        }

        guests[guestCount] = new Guest(guestId, name, cnic, roomNum);
        guests[guestCount]->saveToFile();
        guestCount++;

        int bCount = Booking::getBookingCount();
        bookings[bCount] = new Booking(bookingIdCounter++, guestId,
                                       roomNum, nights,
                                       room->getPrice(),
                                       checkInDate, checkOutDate);
        bookings[bCount]->saveToFile();

        Guest *g = findGuest(guestId);
        if (g)
        {
            *g += bookings[bCount]->getTotalCost();
        }

        room->checkIn();
        cout << "\nCheck-In Successful!\n";
        cout << *bookings[bCount] << "\n";
        return true;
    }

    bool checkOut(int guestId)
    {
        Guest *guest = findGuest(guestId);
        if (!guest)
        {
            cout << "Guest with ID " << guestId << " not found!\n";
            return false;
        }

        Room *room = findRoom(guest->getRoomNumber());
        if (room)
            room->checkOut();

        cout << "\n=== Check-Out Details ===\n";
        cout << *guest << "\n";
        guest->display();

        guest->saveToFile();

        cout << "\nCheck-Out Successful!\n";
        return true;
    }

    void displayAllRooms() const
    {
        cout << "\n====== ROOMS (" << roomCount << " total) ======\n";
        for (int i = 0; i < roomCount; i++)
        {
            cout << *rooms[i] << "\n";
        }
        cout << "Total Room objects: " << Room::getTotalRooms() << "\n";
    }

    void displayAvailableRooms() const
    {
        cout << "\n====== AVAILABLE ROOMS ======\n";
        bool found = false;
        for (int i = 0; i < roomCount; i++)
        {
            if (!rooms[i]->getIsOccupied())
            {
                rooms[i]->display();
                cout << "---\n";
                found = true;
            }
        }
        if (!found)
            cout << "No available rooms!\n";
    }

    void displayAllGuests() const
    {
        cout << "\n====== GUESTS (" << guestCount << " checked in) ======\n";
        for (int i = 0; i < guestCount; i++)
        {
            cout << *guests[i] << "\n";
        }
        cout << "Total Guest objects alive: " << Guest::getGuestCount() << "\n";
    }

    void displayAllBookings() const
    {
        int total = Booking::getBookingCount();
        cout << "\n====== BOOKINGS (" << total << " total) ======\n";
        for (int i = 0; i < total; i++)
        {
            if (bookings[i])
                cout << *bookings[i] << "\n";
        }
    }

    void readGuestsFromFile() const
    {
        ifstream file("guests.txt");
        if (!file.is_open())
        {
            cout << "No guest records file found.\n";
            return;
        }
        cout << "\n=== Guest Records from File ===\n";
        string line;
        while (getline(file, line))
        {
            cout << line << "\n";
        }
        file.close();
    }

    void readBookingsFromFile() const
    {
        ifstream file("bookings.txt");
        if (!file.is_open())
        {
            cout << "No booking records file found.\n";
            return;
        }
        cout << "\n=== Booking Records from File ===\n";
        string line;
        while (getline(file, line))
        {
            cout << line << "\n";
        }
        file.close();
    }

    static void clearDataFiles()
    {
        ofstream("guests.txt", ios::trunc).close();
        ofstream("rooms.txt", ios::trunc).close();
        ofstream("bookings.txt", ios::trunc).close();
        cout << "[Data files cleared]\n";
    }

    string getName() const { return hotelName; }
};

bool hotelNamesMatch(const Hotel &a, const Hotel &b)
{
    return a.getName() == b.getName();
}

void displayMenu()
{
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

void demonstrateOperators()
{
    cout << "\n=== OPERATOR OVERLOADING DEMO (Week 6) ===\n\n";

    Guest g1(101, "Ali Hassan", "12345-1234567-1", 201);
    Guest g2(102, "Sara Khan", "22345-2234567-2", 301);

    g1 += 500.0f;
    g1 += 200.0f;
    cout << "\nAfter += 500 and += 200: " << g1 << "\n";

    Guest g3 = g1;
    cout << "After copy via =: " << g3 << "\n";

    if (g1 == g3)
        cout << "g1 == g3 : TRUE (same ID)\n";
    if (!(g1 == g2))
        cout << "g1 == g2 : FALSE (different IDs)\n";

    Room r1(401, "Single", 1200.0f);
    Room r2(402, "Suite", 6000.0f);

    cout << "\n"
         << r1 << "\n";
    cout << r2 << "\n";

    if (r1 < r2)
        cout << "Room " << r1.getNumber() << " is cheaper than Room " << r2.getNumber() << "\n";

    cout << "\n[g1, g2 destructors will be called at end of this function]\n";
}

int main()
{

    Hotel::clearDataFiles();

    Hotel *hotel = new Hotel("Grand Pearl Hotel");

    int choice = -1;

    while (choice != 0)
    {
        displayMenu();
        cin >> choice;

        if (choice == 1)
        {

            clearScreen();
            cout << "=== CHECK IN GUEST ===\n";

            int gId, roomNum, nights;
            char name[100], cnic[25];
            string checkIn, checkOut;

            cout << "Guest ID     : ";
            cin >> gId;
            cin.ignore();
            cout << "Guest Name   : ";
            cin.getline(name, 100);
            cout << "CNIC         : ";
            cin.getline(cnic, 25);

            hotel->displayAvailableRooms();
            cout << "Room Number  : ";
            cin >> roomNum;
            cout << "Nights       : ";
            cin >> nights;
            cin.ignore();
            cout << "Check-In Date (e.g. 2025-01-01) : ";
            getline(cin, checkIn);
            cout << "Check-Out Date                  : ";
            getline(cin, checkOut);

            hotel->checkIn(gId, name, cnic, roomNum, nights, checkIn, checkOut);
        }
        else if (choice == 2)
        {

            clearScreen();
            cout << "=== CHECK OUT GUEST ===\n";
            int gId;
            cout << "Enter Guest ID: ";
            cin >> gId;
            hotel->checkOut(gId);
        }
        else if (choice == 3)
        {
            hotel->displayAllRooms();
        }
        else if (choice == 4)
        {
            hotel->displayAvailableRooms();
        }
        else if (choice == 5)
        {
            hotel->displayAllGuests();
        }
        else if (choice == 6)
        {
            hotel->displayAllBookings();
        }
        else if (choice == 7)
        {
            hotel->readGuestsFromFile();
        }
        else if (choice == 8)
        {
            hotel->readBookingsFromFile();
        }
        else if (choice == 9)
        {
            demonstrateOperators();
        }
        else if (choice == 0)
        {
            cout << "\nThank you for using Hotel Management System!\n";
            cout << "Saving and shutting down...\n";
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }

        if (choice != 0)
            pauseScreen();
    }

    delete hotel;

    cout << "\n[All memory freed. Program ended cleanly.]\n";
    return 0;
}