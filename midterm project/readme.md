# 🏨 Hotel Management System — C++ OOP Project

A beginner-friendly Hotel Management System in C++ that covers **all OOP concepts** from Week 1 to Week 6, including Pointers, Dynamic Memory, Operator Overloading, File Handling, and more.

---

## 👨‍💻 Author

| Field | Details |
|-------|---------|
| **Name** | Muhammad Muaaz Ali |
| **Roll Number** | 2025-CS-708 |
| **Language** | C++ |
| **Project** | OOP — Hotel Management System |

---

## 📚 Topics Covered (Week-by-Week)

| Week | CLO | Topics Demonstrated in Code |
|------|-----|------------------------------|
| **Week 1** | CLO1 | Classes vs Structs, Encapsulation, Abstraction, Protection, Access Modifiers (`public`, `private`), Implicit member functions |
| **Week 2** | CLO2 | Programmer-defined Constructor, Copy Constructor (Deep Copy), Destructor, Assignment Operator (`=`), Shallow vs Deep objects |
| **Week 3** | CLO2 | Separate declaration & definition, Accessors, Utility methods, Objects as arguments & return types, Cascaded function calls |
| **Week 4** | CLO2/CLO3 | `static` members, `const` members, Object members, Constructor initializer list, `this` pointer |
| **Week 5** | CLO3 | Arrow `->` operator, `new` / `delete` for dynamic objects, Array of pointers, Heap allocation |
| **Week 6** | CLO3 | Operator Overloading (`==`, `<`, `+=`, `=`, `<<`), Member & Friend operators, Cascaded operator calls |

---

## 🗂️ File Structure

```
hotel-management/
│
├── main.cpp          ← All code in one file
├── guests.txt        ← Auto-generated: guest records
├── rooms.txt         ← Auto-generated: room records
├── bookings.txt      ← Auto-generated: booking records
└── README.md         ← This file
```

---

## 🧱 Class Overview

| Class | Responsibility |
|-------|----------------|
| `Guest` | Stores guest info, uses dynamic `char*`, operator overloading |
| `Room` | Represents hotel room, tracks availability, static room count |
| `Booking` | Links guest to room, stores cost & dates, static booking count |
| `Hotel` | Main controller, manages dynamic arrays of pointers, file I/O |

---

## 📊 UML Class Diagram

```mermaid
classDiagram
    class Guest {
        - int id
        - char* name
        - char* cnic
        - int roomNumber
        - float totalBill
        - static int guestCount
        + Guest()
        + Guest(int, char*, char*, int)
        + Guest(Guest&)
        + ~Guest()
        + operator=(Guest&) Guest&
        + operator==(Guest&) bool
        + operator+=(float) Guest&
        + getId() int
        + getName() char*
        + getCnic() char*
        + getRoomNumber() int
        + getTotalBill() float
        + getGuestCount()$ int
        + display() void
        + saveToFile() void
    }

    class Room {
        - int number
        - string type
        - float pricePerNight
        - bool isOccupied
        - static int totalRooms
        + Room()
        + Room(int, string, float)
        + Room(Room&)
        + ~Room()
        + operator==(Room&) bool
        + operator~lt~(Room&) bool
        + getNumber() int
        + getType() string
        + getPrice() float
        + getIsOccupied() bool
        + getTotalRooms()$ int
        + checkIn() void
        + checkOut() void
        + display() void
        + saveToFile() void
    }

    class Booking {
        - int bookingId
        - int guestId
        - int roomNumber
        - int nights
        - float totalCost
        - string checkInDate
        - string checkOutDate
        - static int bookingCount
        + Booking()
        + Booking(int, int, int, int, float, string, string)
        + ~Booking()
        + operator==(Booking&) bool
        + getBookingId() int
        + getGuestId() int
        + getRoomNumber() int
        + getTotalCost() float
        + getBookingCount()$ int
        + display() void
        + saveToFile() void
    }

    class Hotel {
        - string hotelName
        - int maxRooms
        - int maxGuests
        - int maxBookings
        - Room** rooms
        - Guest** guests
        - Booking** bookings
        - int roomCount
        - int guestCount
        - int bookingIdCounter
        + Hotel(string, int, int, int)
        + ~Hotel()
        + addRoom(int, string, float) bool
        + findRoom(int) Room*
        + findGuest(int) Guest*
        + checkIn(...) bool
        + checkOut(int) bool
        + displayAllRooms() void
        + displayAvailableRooms() void
        + displayAllGuests() void
        + displayAllBookings() void
        + readGuestsFromFile() void
        + readBookingsFromFile() void
        + clearDataFiles()$ void
    }

    Hotel "1" --> "*" Room : manages
    Hotel "1" --> "*" Guest : manages
    Hotel "1" --> "*" Booking : manages
    Booking --> Guest : references
    Booking --> Room : references
```

---

## 🔄 Program Flowchart

```mermaid
flowchart TD
    A([START]) --> B[Clear Data Files\nHotel::clearDataFiles]
    B --> C[Create Hotel Object\nnew Hotel on Heap]
    C --> D[Initialize Default Rooms\nRooms 101 102 201 202 301]
    D --> E{Show Main Menu}

    E --> |1| F[Check In Guest]
    E --> |2| G[Check Out Guest]
    E --> |3| H[Display All Rooms]
    E --> |4| I[Display Available Rooms]
    E --> |5| J[Display All Guests]
    E --> |6| K[Display All Bookings]
    E --> |7| L[Read Guests from File]
    E --> |8| M[Read Bookings from File]
    E --> |9| N[Operator Overloading Demo]
    E --> |0| O[Exit]

    F --> F1{Room Exists\nand Available?}
    F1 --> |No| F2[Show Error] --> E
    F1 --> |Yes| F3[new Guest on Heap\nSave to guests.txt]
    F3 --> F4[new Booking on Heap\nSave to bookings.txt]
    F4 --> F5[g += totalCost\noperator+=]
    F5 --> F6[room->checkIn\nArrow Operator]
    F6 --> E

    G --> G1{Guest Found?}
    G1 --> |No| G2[Show Error] --> E
    G1 --> |Yes| G3[room->checkOut\nDisplay Bill]
    G3 --> E

    H --> H1[Loop rooms array\noperator<< for each]
    H1 --> E

    N --> N1[Create Guest g1 g2 on stack]
    N1 --> N2[g1 += 500 += 200\noperator+=]
    N2 --> N3[Guest g3 = g1\nDeep Copy operator=]
    N3 --> N4[g1 == g3 comparison\noperator==]
    N4 --> N5[Room r1 < r2\noperator<]
    N5 --> N6[Destructors called\nfor g1 g2 g3]
    N6 --> E

    O --> P[delete hotel\nDestructor frees all memory]
    P --> Q([END])
```

---

## ⚙️ How to Compile & Run

### Linux / Mac
```bash
g++ -o hotel main.cpp
./hotel
```

### Windows (MinGW)
```bash
g++ -o hotel.exe main.cpp
hotel.exe
```

### Windows (Dev-C++ / Code::Blocks)
- Create a new project
- Add `main.cpp`
- Click **Build & Run**

---

## 🧪 Sample Run

```
------------------------------------------------------------
   *** HOTEL MANAGEMENT SYSTEM ***
------------------------------------------------------------
  1. Check In Guest
  2. Check Out Guest
  3. View All Rooms
  4. View Available Rooms
  5. View All Guests
  6. View All Bookings
  7. View Guest Records (from File)
  8. View Booking Records (from File)
  9. Demonstrate Operator Overloading (Week 6)
  0. Exit
------------------------------------------------------------
  Enter your choice: 1
```

---

## 💡 Key OOP Concepts at a Glance

### 🔐 Encapsulation
All data members are `private`. They can only be accessed through `public` methods (accessors/mutators).

### 🧩 Abstraction
Users interact with `Hotel` class methods without knowing internal implementation.

### 🛡️ Protection
`private` keyword prevents direct access. Only class methods can modify state.

### 📨 Messaging
Objects communicate by calling each other's methods (e.g., `room->checkIn()`, `guest->saveToFile()`).

### 🔁 Operator Overloading (Week 6)
| Operator | Class | Purpose |
|----------|-------|---------|
| `+=`     | Guest | Add to bill |
| `==`     | Guest, Room, Booking | Equality check |
| `<`      | Room  | Compare prices |
| `=`      | Guest | Deep copy assignment |
| `<<`     | Guest, Room, Booking | Print to stream (friend) |

### 🧠 Dynamic Memory (Week 5)
- `Hotel` uses `new Room*[]`, `new Guest*[]`, `new Booking*[]`
- Individual objects created with `new Guest(...)`, `new Room(...)`
- All freed with `delete` in `~Hotel()`
- Arrow operator `->` used to access members through pointers

---

## 📁 Text File Handling

| File | Contents |
|------|----------|
| `guests.txt` | id, name, cnic, roomNumber, totalBill |
| `rooms.txt` | number, type, pricePerNight, isOccupied |
| `bookings.txt` | bookingId, guestId, roomNumber, nights, totalCost, checkIn, checkOut |

Files are written with `ofstream` (append mode) and read with `ifstream`.

---

## 👨‍💻 Author
**Name:** Muhammad Muaaz Ali  
**Roll Number:** 2025-CS-708  
**Project:** OOP — Hotel Management System  
Covers all CLO1, CLO2, CLO3 topics from Week 1–6  
Language: **C++** | File: `main.cpp` (single file)