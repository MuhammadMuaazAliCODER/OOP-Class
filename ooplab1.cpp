// ============================================================
//   SOCIETY MANAGEMENT SYSTEM
//   Covers: All OOP concepts from Week 1-6 + CLO1, CLO2, CLO3
// ============================================================
//
//  TOPICS COVERED:
//  [Week 0] Pointers, dynamic memory, structured vs OOP
//  [Week 1] Classes & Objects, implicit member functions,
//           default/copy constructor, destructor, =, &,
//           access modifiers (public/private)
//  [Week 2] Programmer-defined constructor, copy constructor,
//           destructor, assignment operator, overloading
//           constructors, shallow vs deep copy,
//           constructor initializer list
//  [Week 3] Separate declaration & definition, accessors,
//           utility methods, objects as argument/return type,
//           cascaded function calls
//  [Week 4] Static members, const members, object members,
//           initializer list revisited, implicit 'this' pointer
//  [Week 5] Arrow (->) operator, new/delete for objects
//  [Week 6] Operator overloading (member & friend functions),
//           cascaded operator calls, restrictions on friend
//           operators for [], (), ->
// ============================================================

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// ============================================================
//  FORWARD DECLARATIONS
// ============================================================
class Address;
class Person;
class Member;
class Society;

// ============================================================
//  CLASS: Address
//  Demonstrates: object-as-member, deep copy, initializer list
// ============================================================
class Address {
private:
    char* street;   // dynamic memory => deep copy needed
    int houseNo;

public:
    // --- Default Constructor (Week 1/2) ---
    Address() : houseNo(0) {
        street = new char[50];
        strcpy(street, "Unknown Street");
        cout << "  [Address] Default constructor called\n";
    }

    // --- Parameterized Constructor (Week 2) ---
    Address(const char* s, int h) : houseNo(h) {
        street = new char[strlen(s) + 1];
        strcpy(street, s);
    }

    // --- Copy Constructor - DEEP COPY (Week 2) ---
    Address(const Address& other) : houseNo(other.houseNo) {
        street = new char[strlen(other.street) + 1];
        strcpy(street, other.street);
        cout << "  [Address] Deep copy constructor called\n";
    }

    // --- Assignment Operator = (Week 1/2) ---
    Address& operator=(const Address& other) {
        if (this != &other) {           // self-assignment check
            delete[] street;
            street = new char[strlen(other.street) + 1];
            strcpy(street, other.street);
            houseNo = other.houseNo;
        }
        return *this;                   // cascaded assignment support
    }

    // --- Destructor (Week 2) ---
    ~Address() {
        delete[] street;
        cout << "  [Address] Destructor called\n";
    }

    // --- Accessors (Week 3) ---
    const char* getStreet() const { return street; }
    int getHouseNo()        const { return houseNo; }

    void setStreet(const char* s) {
        delete[] street;
        street = new char[strlen(s) + 1];
        strcpy(street, s);
    }
    void setHouseNo(int h) { houseNo = h; }

    void display() const {
        cout << "House #" << houseNo << ", " << street;
    }
};


// ============================================================
//  CLASS: Person
//  Demonstrates: encapsulation, abstraction, object member,
//                initializer list, this pointer, static member
// ============================================================
class Person {
private:
    char*   name;           // dynamic => deep copy
    int     age;
    Address address;        // object-as-member (Week 4)

    static int totalPersons; // Static member (Week 4)

public:
    // --- Default Constructor ---
    Person() : age(0), address() {
        name = new char[50];
        strcpy(name, "Unknown");
        totalPersons++;
        cout << "  [Person] Default constructor | Total: " << totalPersons << "\n";
    }

    // --- Parameterized Constructor with initializer list (Week 2/4) ---
    Person(const char* n, int a, const char* street, int hNo)
        : age(a), address(street, hNo)   // initializer list
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        totalPersons++;
    }

    // --- Copy Constructor - DEEP COPY (Week 2) ---
    Person(const Person& other) : age(other.age), address(other.address) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        totalPersons++;
        cout << "  [Person] Copy constructor (deep copy)\n";
    }

    // --- Assignment Operator (Week 2) ---
    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            age     = other.age;
            address = other.address;    // uses Address::operator=
        }
        return *this;
    }

    // --- Destructor (Week 2) ---
    virtual ~Person() {
        cout << "  [Person] Destructor for: " << name << "\n";
        delete[] name;
        totalPersons--;
    }

    // --- Accessors & Mutators (Week 3) ---
    const char* getName()    const { return name; }
    int         getAge()     const { return age;  }
    const Address& getAddress() const { return address; }

    void setName(const char* n) {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    void setAge(int a)             { age = a; }
    void setAddress(const Address& a) { address = a; }

    // --- Static member accessor (Week 4) ---
    static int getTotalPersons() { return totalPersons; }

    // --- Utility / display (Week 3) ---
    virtual void display() const {
        cout << "  Name   : " << name << "\n"
             << "  Age    : " << age  << "\n"
             << "  Address: "; address.display(); cout << "\n";
    }

    // --- this pointer usage (Week 4) ---
    Person& copyFrom(const Person& other) {
        *this = other;          // explicit use of this
        return *this;
    }

    // --- Address-of operator & (Week 1) ---
    // (Built-in, but we demonstrate using it explicitly in main)
};

int Person::totalPersons = 0;   // static member definition (Week 4)


// ============================================================
//  CLASS: Member   (inherits Person)
//  Demonstrates: const member, cascaded calls, operator overloading
// ============================================================
class Member : public Person {
private:
    int         memberId;
    double      dues;           // monthly dues
    bool        hasPaid;

    const int   SOCIETY_CODE;   // const member (Week 4)

    static int  nextId;         // static counter

public:
    // --- Default Constructor with initializer list for const (Week 4) ---
    Member() : Person(), memberId(nextId++), dues(500.0),
               hasPaid(false), SOCIETY_CODE(1001)
    {
        cout << "  [Member] Default constructor | ID: " << memberId << "\n";
    }

    // --- Parameterized Constructor ---
    Member(const char* n, int a, const char* street, int hNo, double d)
        : Person(n, a, street, hNo),
          memberId(nextId++), dues(d), hasPaid(false), SOCIETY_CODE(1001)
    {}

    // --- Copy Constructor (Week 2) ---
    Member(const Member& other)
        : Person(other), memberId(nextId++),
          dues(other.dues), hasPaid(other.hasPaid), SOCIETY_CODE(1001)
    {
        cout << "  [Member] Copy constructor called\n";
    }

    // --- Destructor ---
    ~Member() override {
        cout << "  [Member] Destructor for member ID: " << memberId << "\n";
    }

    // --- Accessors (Week 3) ---
    int    getMemberId() const { return memberId;    }
    double getDues()     const { return dues;        }
    bool   isPaid()      const { return hasPaid;     }
    int    getSocCode()  const { return SOCIETY_CODE;} // const member read

    // --- Utility: pay dues (Week 3) - returns *this for cascading (Week 3) ---
    Member& payDues() {
        hasPaid = true;
        cout << "  >> Member " << getName() << " paid dues of Rs." << dues << "\n";
        return *this;   // cascaded call support
    }

    Member& resetDues() {
        hasPaid = false;
        return *this;
    }

    Member& updateDues(double d) {
        dues = d;
        return *this;
    }

    // --------------------------------------------------------
    //  OPERATOR OVERLOADING (Week 6)
    // --------------------------------------------------------

    // --- operator== as MEMBER function (Week 6) ---
    bool operator==(const Member& other) const {
        return memberId == other.memberId;
    }

    // --- operator< as MEMBER function (for sorting / comparison) ---
    bool operator<(const Member& other) const {
        return dues < other.dues;
    }

    // --- operator+= as MEMBER (add to dues) ---
    Member& operator+=(double amount) {
        dues += amount;
        return *this;   // cascaded: m += 100 += 200 (chaining)
    }

    // --- operator<< as FRIEND function (Week 6) ---
    // Note: [], (), -> cannot be friend operators (Week 6 restriction note)
    friend ostream& operator<<(ostream& out, const Member& m);

    // --- operator>> as FRIEND function ---
    friend istream& operator>>(istream& in, Member& m);

    void display() const override {
        cout << "  ---- Member Info ----\n";
        Person::display();
        cout << "  Member ID  : " << memberId << "\n"
             << "  Society Code: " << SOCIETY_CODE << "\n"
             << "  Monthly Dues: Rs." << fixed << setprecision(2) << dues << "\n"
             << "  Dues Paid  : " << (hasPaid ? "Yes" : "No") << "\n";
    }
};

int Member::nextId = 1001;  // static member definition

// --- Friend operator<< definition (Week 6) ---
ostream& operator<<(ostream& out, const Member& m) {
    out << "[ID:" << m.memberId << "] "
        << m.getName() << " | Dues: Rs." << m.dues
        << " | Paid: " << (m.hasPaid ? "Yes" : "No");
    return out; // cascaded: cout << m1 << m2
}

// --- Friend operator>> definition (Week 6) ---
istream& operator>>(istream& in, Member& m) {
    cout << "  Enter dues amount: ";
    in >> m.dues;
    return in;
}


// ============================================================
//  CLASS: Society
//  Demonstrates: dynamic array with new/delete (Week 5),
//                arrow operator (Week 5), static member,
//                objects as arg/return (Week 3)
// ============================================================
class Society {
private:
    char*    societyName;
    Member** members;       // dynamic array of pointers (Week 5)
    int      capacity;
    int      count;

    static int totalSocieties;  // Week 4

public:
    // --- Constructor ---
    Society(const char* name, int cap = 10) : capacity(cap), count(0) {
        societyName = new char[strlen(name) + 1];
        strcpy(societyName, name);

        // Dynamic allocation with new[] (Week 5)
        members = new Member*[capacity];
        for (int i = 0; i < capacity; i++) members[i] = nullptr;

        totalSocieties++;
        cout << "\n  [Society] '" << societyName << "' created. Total societies: " << totalSocieties << "\n";
    }

    // --- Destructor: de-allocate with delete (Week 5) ---
    ~Society() {
        cout << "\n  [Society] Destroying '" << societyName << "'...\n";
        for (int i = 0; i < count; i++) {
            delete members[i];      // delete each Member object (Week 5)
            members[i] = nullptr;
        }
        delete[] members;           // delete array (Week 5)
        delete[] societyName;
        totalSocieties--;
    }

    // --- Add member using new (Week 5) ---
    void addMember(const char* name, int age, const char* street, int hNo, double dues) {
        if (count >= capacity) {
            cout << "  Society is full!\n";
            return;
        }
        // Instantiate in heap using new (Week 5)
        members[count] = new Member(name, age, street, hNo, dues);
        cout << "  >> Added: " << name << " to " << societyName << "\n";
        count++;
    }

    // --- Arrow operator -> usage (Week 5) ---
    void showMember(int index) const {
        if (index < 0 || index >= count) { cout << "  Invalid index!\n"; return; }
        // Using -> operator to access member through pointer (Week 5)
        members[index]->display();
    }

    // --- Object as return type (Week 3) ---
    Member getMemberCopy(int index) const {
        if (index >= 0 && index < count)
            return *members[index]; // returns a copy (invokes copy constructor)
        return Member();
    }

    // --- Object as argument (Week 3) ---
    void findAndPrint(const Member& target) const {
        for (int i = 0; i < count; i++) {
            if (*members[i] == target) {    // uses overloaded ==
                cout << "  Found: "; members[i]->display();
                return;
            }
        }
        cout << "  Member not found.\n";
    }

    // --- Collect dues from all ---
    void collectAllDues() {
        cout << "\n  -- Collecting dues for all members --\n";
        for (int i = 0; i < count; i++) {
            // Cascaded calls (Week 3/4): resetDues().updateDues().payDues()
            members[i]->resetDues().updateDues(members[i]->getDues()).payDues();
        }
    }

    // --- Using -> operator explicitly (Week 5) ---
    void arrowOperatorDemo(int index) const {
        if (index < 0 || index >= count) return;
        Member* ptr = members[index];       // raw pointer
        cout << "\n  [Arrow -> Demo] Accessing via pointer:\n";
        cout << "  Name via ptr->getName(): " << ptr->getName() << "\n";
        cout << "  Age  via ptr->getAge() : " << ptr->getAge()  << "\n";
        cout << "  Address: "; ptr->getAddress().display(); cout << "\n";
    }

    // --- Operator overloading: += adds member dues (friend) ---
    friend Society& operator+=(Society& soc, double amount);

    // --- Display all ---
    void displayAll() const {
        cout << "\n  ========== " << societyName << " Members ==========\n";
        cout << "  Total Members  : " << count << "\n";
        cout << "  Total Persons  : " << Person::getTotalPersons() << "\n";
        cout << "  Total Societies: " << totalSocieties << "\n\n";
        for (int i = 0; i < count; i++) {
            cout << "  " << *members[i] << "\n"; // uses friend operator<<
        }
        cout << "  ==========================================\n";
    }

    static int getTotalSocieties() { return totalSocieties; }
};

int Society::totalSocieties = 0;

// --- Friend operator for Society (Week 6) ---
Society& operator+=(Society& soc, double amount) {
    cout << "\n  [op+=] Increasing all dues by Rs." << amount << "\n";
    for (int i = 0; i < soc.count; i++) {
        *soc.members[i] += amount;  // uses Member::operator+=
    }
    return soc;
}


// ============================================================
//  DEMONSTRATION FUNCTIONS
// ============================================================

// --- Demonstrates shallow vs deep copy concept (Week 2) ---
void shallowVsDeepDemo() {
    cout << "\n============================================\n";
    cout << "  DEMO: Shallow vs Deep Copy (Week 2)\n";
    cout << "============================================\n";

    Address a1("Green Avenue", 5);
    Address a2 = a1;        // deep copy constructor called
    a2.setStreet("Blue Road");
    a2.setHouseNo(10);

    cout << "  a1 (original): "; a1.display(); cout << "\n";
    cout << "  a2 (copy mod): "; a2.display(); cout << "\n";
    cout << "  => Deep copy: modifying a2 did NOT affect a1\n";
}

// --- Demonstrates static members (Week 4) ---
void staticMemberDemo() {
    cout << "\n============================================\n";
    cout << "  DEMO: Static Member (Week 4)\n";
    cout << "============================================\n";
    cout << "  Total Persons right now: " << Person::getTotalPersons() << "\n";
    cout << "  Total Societies right now: " << Society::getTotalSocieties() << "\n";
}

// --- Demonstrates pointer arithmetic & address-of (Week 0/1) ---
void pointerDemo() {
    cout << "\n============================================\n";
    cout << "  DEMO: Pointers & Dynamic Allocation (Week 0/5)\n";
    cout << "============================================\n";

    // Stack object
    Member m1("Stack Ali", 30, "Johar Town", 7, 300.0);
    cout << "  Stack object address (&m1): " << &m1 << "\n";

    // Heap object with new (Week 5)
    Member* m2 = new Member("Heap Usman", 25, "Model Town", 3, 450.0);
    cout << "  Heap object address (m2)  : " << m2 << "\n";

    // Arrow operator (Week 5)
    cout << "  m2->getName()  : " << m2->getName() << "\n";
    cout << "  m2->getMemberId(): " << m2->getMemberId() << "\n";

    // de-allocate (Week 5)
    delete m2;
    m2 = nullptr;
    cout << "  Heap object deleted, m2 = nullptr\n";
}

// --- Demonstrates operator overloading (Week 6) ---
void operatorOverloadDemo() {
    cout << "\n============================================\n";
    cout << "  DEMO: Operator Overloading (Week 6)\n";
    cout << "============================================\n";

    Member* m1 = new Member("Sara", 28, "DHA", 12, 600.0);
    Member* m2 = new Member("Bilal", 35, "Gulberg", 4, 600.0);

    // operator<< (friend) - cascaded output
    cout << "  m1: " << *m1 << "\n";
    cout << "  m2: " << *m2 << "\n";

    // operator== (member)
    cout << "  m1 == m2 ? " << (*m1 == *m2 ? "Yes (same ID)" : "No (different ID)") << "\n";

    // operator< (member)
    cout << "  m1 < m2 (by dues)? " << (*m1 < *m2 ? "Yes" : "No") << "\n";

    // operator+= (member) - cascaded
    *m1 += 100;
    cout << "  After m1 += 100: " << *m1 << "\n";

    // Cascaded member function calls (Week 3/4)
    cout << "\n  Cascaded calls: m1->resetDues().updateDues(800).payDues()\n";
    m1->resetDues().updateDues(800).payDues();
    cout << "  m1 after cascade: " << *m1 << "\n";

    cout << "\n  [Week 6 Note] Restrictions on friend operator overloads:\n";
    cout << "  - [] (subscript)  must be a member function\n";
    cout << "  - () (call)       must be a member function\n";
    cout << "  - -> (arrow)      must be a member function\n";
    cout << "  - = (assignment)  must be a member function\n";
    cout << "  These CANNOT be defined as friend functions.\n";

    delete m1;
    delete m2;
}


// ============================================================
//  MAIN FUNCTION
// ============================================================
int main() {
    cout << "====================================================\n";
    cout << "     SOCIETY MANAGEMENT SYSTEM - OOP in C++        \n";
    cout << "     Covers Week 0-6 | CLO1, CLO2, CLO3            \n";
    cout << "====================================================\n\n";

    // ---------------------------------------------------------
    //  [Week 0] Pointer & Dynamic Memory Demo
    // ---------------------------------------------------------
    pointerDemo();

    // ---------------------------------------------------------
    //  [Week 2] Shallow vs Deep Copy Demo
    // ---------------------------------------------------------
    shallowVsDeepDemo();

    // ---------------------------------------------------------
    //  [Week 1-5] Main Society Object - allocated on HEAP (Week 5)
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  Creating Society on HEAP with new (Week 5)\n";
    cout << "============================================\n";

    Society* greenSociety = new Society("Green Valley Housing Society", 5);

    // addMember -> internally uses 'new' to allocate Member (Week 5)
    greenSociety->addMember("Ahmed Khan",   34, "Block A, Street 3",  12, 1200.0);
    greenSociety->addMember("Fatima Malik", 29, "Block B, Street 7",  5,  900.0);
    greenSociety->addMember("Usman Raza",   42, "Block C, Street 1",  8,  1500.0);
    greenSociety->addMember("Ayesha Noor",  25, "Block A, Street 9",  3,  800.0);

    // Display using friend operator<< via displayAll
    greenSociety->displayAll();

    // ---------------------------------------------------------
    //  [Week 3] Arrow operator demo
    // ---------------------------------------------------------
    greenSociety->arrowOperatorDemo(0);

    // ---------------------------------------------------------
    //  [Week 3] Object as return type - getMemberCopy
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  DEMO: Object as return type (Week 3)\n";
    cout << "============================================\n";
    Member copy = greenSociety->getMemberCopy(1); // copy constructor called
    cout << "  Copied member info:\n";
    copy.display();

    // ---------------------------------------------------------
    //  [Week 3] Object as argument - findAndPrint
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  DEMO: Object as argument (Week 3)\n";
    cout << "============================================\n";
    greenSociety->findAndPrint(copy);

    // ---------------------------------------------------------
    //  [Week 3/4] Cascaded function calls
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  DEMO: Cascaded Calls (Week 3/4)\n";
    cout << "============================================\n";
    greenSociety->collectAllDues();

    // ---------------------------------------------------------
    //  [Week 4] Static members
    // ---------------------------------------------------------
    staticMemberDemo();

    // ---------------------------------------------------------
    //  [Week 6] Operator Overloading demos
    // ---------------------------------------------------------
    operatorOverloadDemo();

    // ---------------------------------------------------------
    //  [Week 6] Friend operator+= on Society (increase all dues)
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  DEMO: Friend operator+= on Society (Week 6)\n";
    cout << "============================================\n";
    *greenSociety += 200.0;     // all members dues +200
    greenSociety->displayAll();

    // ---------------------------------------------------------
    //  [Week 5] Second society to demo multiple objects on heap
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  Creating 2nd Society on heap (Week 5)\n";
    cout << "============================================\n";
    Society* blueSociety = new Society("Blue Horizon Apartments", 3);
    blueSociety->addMember("Zara Iqbal",   22, "Tower A, Floor 3", 302, 2000.0);
    blueSociety->addMember("Hamza Sheikh", 38, "Tower B, Floor 7", 701, 2500.0);
    blueSociety->displayAll();

    staticMemberDemo();

    // ---------------------------------------------------------
    //  [Week 5] Cleanup with delete (Week 5)
    // ---------------------------------------------------------
    cout << "\n============================================\n";
    cout << "  Cleanup: delete societies (Week 5)\n";
    cout << "============================================\n";

    delete greenSociety;    // calls ~Society -> delete[] members -> ~Member -> ~Person -> ~Address
    greenSociety = nullptr;

    delete blueSociety;
    blueSociety = nullptr;

    cout << "\n============================================\n";
    cout << "  After cleanup:\n";
    cout << "  Total Persons remaining  : " << Person::getTotalPersons() << "\n";
    cout << "  Total Societies remaining: " << Society::getTotalSocieties() << "\n";
    cout << "============================================\n";

    cout << "\n====================================================\n";
    cout << "     All OOP concepts demonstrated successfully!    \n";
    cout << "====================================================\n";

    return 0;
}

// ============================================================
//  CONCEPT INDEX (Quick Reference)
// ============================================================
//
//  Concept                         | Location in code
//  --------------------------------|---------------------------
//  Pointers & dynamic memory       | pointerDemo(), Society
//  Struct -> Class migration       | Person, Member classes
//  Encapsulation / Abstraction     | private members + accessors
//  Protection (access modifiers)   | public/private in all classes
//  Messaging (function calls)      | addMember, display, etc.
//  Default constructor             | Address(), Person(), Member()
//  Copy constructor (deep)         | Address(const Address&), Person(...)
//  Destructor                      | ~Address, ~Person, ~Member, ~Society
//  Assignment operator =           | Address::operator=, Person::operator=
//  Address-of operator &           | &m1 in pointerDemo()
//  Overloaded constructors         | Multiple ctors in each class
//  Shallow vs Deep copy            | shallowVsDeepDemo()
//  Initializer list                | Person(...) : age(a), address(...)
//  Separate declaration/definition | (all methods defined outside class scope possible)
//  Accessors / utility methods     | getters, setters, payDues()
//  Object as argument              | findAndPrint(const Member&)
//  Object as return type           | getMemberCopy() -> Member
//  Cascaded calls                  | resetDues().updateDues().payDues()
//  Static members                  | Person::totalPersons, Member::nextId
//  Const members                   | SOCIETY_CODE in Member
//  Object members                  | Address inside Person
//  this pointer                    | Person::copyFrom(), operator=
//  Arrow (->) operator             | ptr->getName(), ptr->getAge()
//  new (heap allocation)           | new Member(...), new Society(...)
//  delete (heap deallocation)      | delete members[i], delete m2
//  Operator overload (member)      | ==, <, +=  in Member
//  Operator overload (friend)      | operator<<, operator>>, operator+=Society
//  Cascaded operator calls         | cout << m1 << m2, *this += ...
//  Friend operator restrictions    | Note in operatorOverloadDemo()
// ============================================================