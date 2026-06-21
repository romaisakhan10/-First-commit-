#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class CapacityExceededException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Course capacity exceeded.";
    }
};

class OverdueException : public exception {
    double fine;
public:
    OverdueException(double f = 0.0) : fine(f) {}
    const char* what() const noexcept override {
        return "Error: Library item is overdue. Fine applied.";
    }
    double getFine() const { return fine; }
};

class Person {
protected:
    string name, cnic, contact;
    int age;
public:
    Person(string n = "", string c = "", string con = "", int a = 0)
        : name(n), cnic(c), contact(con), age(a) {
    }

    string getName()   
        const { return name; }
    string getCNIC()   
        const { return cnic; }
    string getContact()
        const { return contact; }
    int    getAge()    
        const { return age; }

    virtual void displayInfo() const = 0;  
    virtual ~Person() = default;
};


class Course;
class Student : virtual public Person {
private:
    string rollNo;
    int    semester;
    float  gpa;
    Course* enrolledCourses[10];
    int     courseCount;
public:
    Student(string n = "", string cnic = "", string contact = "",
        int age = 0, string roll = "", int sem = 0, float g = 0.0)
        : Person(n, cnic, contact, age),
        rollNo(roll), semester(sem), gpa(g), courseCount(0) {
        for (int i = 0; i < 10; i++) enrolledCourses[i] = nullptr;
    }

    string getRollNo()  
        const { return rollNo; }
    int    getSemester()
        const { return semester; }
    float  getGPA()    
        const { return gpa; }

    void addCourse(Course* c) {
        if (courseCount < 10) enrolledCourses[courseCount++] = c;
    }

    void calculateGrade() const {
        cout << "GPA: " << gpa << " => Grade: ";
        if (gpa >= 3.7) cout << "A\n";
        else if (gpa >= 3.3) cout << "A-\n";
        else if (gpa >= 3.0) cout << "B+\n";
        else if (gpa >= 2.7) cout << "B\n";
        else if (gpa >= 2.3) cout << "B-\n";
        else if (gpa >= 2.0) cout << "C\n";
        else                 cout << "F\n";
    }

    void displayInfo() const override {
        cout << "------------------------------\n";
        cout << "Student Name : " << name << "\n";
        cout << "Roll No      : " << rollNo << "\n";
        cout << "CNIC         : " << cnic << "\n";
        cout << "Contact      : " << contact << "\n";
        cout << "Age          : " << age << "\n";
        cout << "Semester     : " << semester << "\n";
        cout << "GPA          : " << gpa << "\n";
        calculateGrade();
    }
};

// GradStudent multi-level inheritance (GradStudent -> Student -> Person)
class GradStudent : public Student {
private:
    string researchTopic;
    string supervisor;
public:
    GradStudent(string n, string cnic, string contact, int age,
        string roll, int sem, float gpa,
        string topic, string sup)
        : Person(n, cnic, contact, age),
        Student(n, cnic, contact, age, roll, sem, gpa),
        researchTopic(topic), supervisor(sup) {
    }

    void displayInfo() const override {
        Student::displayInfo();
        cout << "Research Topic : " << researchTopic << "\n";
        cout << "Supervisor     : " << supervisor << "\n";
    }
};

// Faculty virtual inheritance from Person
class Faculty : virtual public Person {
private:
    string employeeID, department, designation;
    string assignedCourses[10];
    int    courseCount;
public:
    Faculty(string n = "", string cnic = "", string contact = "",
        int age = 0, string empID = "",
        string dept = "", string desig = "")
        : Person(n, cnic, contact, age),
        employeeID(empID), department(dept),
        designation(desig), courseCount(0) {
    }

    string getEmployeeID()  const { return employeeID; }
    string getDepartment()  const { return department; }
    string getDesignation() const { return designation; }

    void assignCourse(const string& code) {
        if (courseCount < 10) assignedCourses[courseCount++] = code;
    }

    void displayInfo() const override {
        cout << "------------------------------\n";
        cout << "Faculty Name  : " << name << "\n";
        cout << "Employee ID   : " << employeeID << "\n";
        cout << "Department    : " << department << "\n";
        cout << "Designation   : " << designation << "\n";
        cout << "CNIC          : " << cnic << "\n";
        cout << "Contact       : " << contact << "\n";
        cout << "Age           : " << age << "\n";
    }
};

// Staff  virtual inheritance from Person
class Staff : virtual public Person {
private:
    string staffID, role;
    double salary;
public:
    Staff(string n = "", string cnic = "", string contact = "",
        int age = 0, string sID = "",
        string r = "", double sal = 0.0)
        : Person(n, cnic, contact, age),
        staffID(sID), role(r), salary(sal) {
    }

    string getStaffID() const { return staffID; }
    string getRole()    const { return role; }
    double getSalary()  const { return salary; }

    void displayInfo() const override {
        cout << "------------------------------\n";
        cout << "Staff Name : " << name << "\n";
        cout << "Staff ID   : " << staffID << "\n";
        cout << "Role       : " << role << "\n";
        cout << "Salary     : " << salary << "\n";
        cout << "CNIC       : " << cnic << "\n";
        cout << "Contact    : " << contact << "\n";
        cout << "Age        : " << age << "\n";
    }
};

// ===========================================================
// MODULE 2  COURSE & ENROLLMENT
// ===========================================================

class Course {
private:
    string   courseCode, courseName;
    int      creditHours, maxCapacity, enrolledCount;
    Faculty* instructor;
    Student* waitingList[20];
    int      waitingCount;

public:
    Course(string code = "", string name = "",
        int credits = 0, int capacity = 0)
        : courseCode(code), courseName(name),
        creditHours(credits), maxCapacity(capacity),
        enrolledCount(0), instructor(nullptr), waitingCount(0) {
        for (int i = 0; i < 20; i++) waitingList[i] = nullptr;
    }

    string   getCourseCode()    const { return courseCode; }
    string   getCourseName()    const { return courseName; }
    int      getCreditHours()   const { return creditHours; }
    int      getMaxCapacity()   const { return maxCapacity; }
    int      getEnrolledCount() const { return enrolledCount; }
    int      getWaitingCount()  const { return waitingCount; }
    Student* getWaiting(int i)  const { return waitingList[i]; }

    void setInstructor(Faculty* f) { instructor = f; }

    void enrollStudent() {
        if (enrolledCount >= maxCapacity)
            throw CapacityExceededException();
        enrolledCount++;
    }

    void addToWaitingList(Student* s) {
        if (waitingCount < 20) waitingList[waitingCount++] = s;
    }

    bool operator==(const Course& c) const {
        return courseCode == c.courseCode;
    }

    friend ostream& operator<<(ostream& out, const Course& c) {
        out << c.courseCode << " - " << c.courseName
            << " | Credits: " << c.creditHours
            << " | Enrolled: " << c.enrolledCount
            << "/" << c.maxCapacity;
        return out;
    }
};

class Enrollment {
private:
    Student* student;
    Course* course;
    string   enrollmentDate;
    string   grade;
public:
    Enrollment(Student* s = nullptr, Course* c = nullptr,
        string date = "", string g = "")
        : student(s), course(c), enrollmentDate(date), grade(g) {
    }

    Student* getStudent() const { return student; }
    Course* getCourse()  const { return course; }
    string   getGrade()   const { return grade; }
    void     setGrade(const string& g) { grade = g; }

    static int mergeWaitingLists(Course* a, Course* b,
        Student* merged[], int maxSize) {
        int count = 0;
        for (int i = 0; i < a->getWaitingCount() && count < maxSize; i++)
            merged[count++] = a->getWaiting(i);
        for (int i = 0; i < b->getWaitingCount() && count < maxSize; i++)
            merged[count++] = b->getWaiting(i);
        return count;
    }

    void displayEnrollment() const {
        if (student && course)
            cout << "Student: " << student->getName()
            << " | Course: " << course->getCourseCode()
            << " | Grade: " << grade << "\n";
    }
};

// ===========================================================
// MODULE 3  LIBRARY SYSTEM
// ===========================================================

class LibraryItem {
protected:
    int    itemID, publicationYear;
    string title, author;
    bool   isIssued;
public:
    LibraryItem(int id = 0, string t = "", string a = "", int yr = 0)
        : itemID(id), publicationYear(yr),
        title(t), author(a), isIssued(false) {
    }

    int    getItemID()          const { return itemID; }
    string getTitle()           const { return title; }
    string getAuthor()          const { return author; }
    int    getPublicationYear() const { return publicationYear; }
    bool   getIsIssued()        const { return isIssued; }
    void   setIssued(bool v) { isIssued = v; }

    virtual void checkout() = 0;
    virtual void displayItem() const = 0;
    virtual ~LibraryItem() = default;
};

class Book : public LibraryItem {
private:
    string isbn, genre;
    int    copiesAvailable;
public:
    Book(int id = 0, string title = "", string author = "",
        int yr = 0, string isbn = "",
        string genre = "", int copies = 1)
        : LibraryItem(id, title, author, yr),
        isbn(isbn), genre(genre), copiesAvailable(copies) {
    }

    void checkout() override {
        if (copiesAvailable <= 0)
            throw OverdueException(50.0);
        copiesAvailable--;
        isIssued = true;
        cout << "Book \"" << title << "\" checked out. Copies left: "
            << copiesAvailable << "\n";
    }

    void returnBook() {
        copiesAvailable++;
        isIssued = false;
        cout << "Book \"" << title << "\" returned.\n";
    }

    void displayItem() const override {
        cout << "  [BOOK] ID:" << itemID
            << " | " << title << " by " << author
            << " | ISBN:" << isbn
            << " | Genre:" << genre
            << " | Copies:" << copiesAvailable << "\n";
    }
};

class Journal : public LibraryItem {
private:
    string issn;
    int    volume, issueNumber;
public:
    Journal(int id = 0, string title = "", string author = "",
        int yr = 0, string issn = "",
        int vol = 0, int issue = 0)
        : LibraryItem(id, title, author, yr),
        issn(issn), volume(vol), issueNumber(issue) {
    }

    void checkout() override {
        if (isIssued) {
            cout << "Journal already issued.\n"; return;
        }
        isIssued = true;
        cout << "Journal \"" << title << "\" Vol." << volume
            << " Issue " << issueNumber << " checked out.\n";
    }

    void displayItem() const override {
        cout << "  [JOURNAL] ID:" << itemID
            << " | " << title << " by " << author
            << " | ISSN:" << issn
            << " | Vol:" << volume
            << " Issue:" << issueNumber << "\n";
    }
};

struct IssuedRecord {
    string rollNo;
    int    itemID;
    string issueDate;
};

class Library {
private:
    LibraryItem* catalog[100];
    int          itemCount;
    IssuedRecord issuedRecords[100];
    int          issuedCount;
public:
    Library() : itemCount(0), issuedCount(0) {
        for (int i = 0; i < 100; i++) catalog[i] = nullptr;
    }
    ~Library() {
        for (int i = 0; i < itemCount; i++) delete catalog[i];
    }

    void addItem(LibraryItem* item) {
        if (itemCount >= 100) { cout << "Catalog full.\n"; return; }
        catalog[itemCount++] = item;
        cout << "\"" << item->getTitle() << "\" added to library.\n";
    }

    void searchByTitle(const string& title) const {
        bool found = false;
        for (int i = 0; i < itemCount; i++)
            if (catalog[i] && catalog[i]->getTitle() == title) {
                catalog[i]->displayItem(); found = true;
            }
        if (!found) cout << "Not found: " << title << "\n";
    }

    void issueItem(int id, const string& roll, const string& date) {
        for (int i = 0; i < itemCount; i++)
            if (catalog[i] && catalog[i]->getItemID() == id) {
                try {
                    catalog[i]->checkout();
                    issuedRecords[issuedCount++] = { roll, id, date };
                }
                catch (OverdueException& e) {
                    cout << e.what() << " Fine: Rs." << e.getFine() << "\n";
                }
                return;
            }
        cout << "Item ID " << id << " not found.\n";
    }

    void returnItem(int id) {
        for (int i = 0; i < itemCount; i++)
            if (catalog[i] && catalog[i]->getItemID() == id) {
                catalog[i]->setIssued(false);
                cout << "Item ID " << id << " returned.\n";
                for (int j = 0; j < issuedCount; j++)
                    if (issuedRecords[j].itemID == id) {
                        for (int k = j; k < issuedCount - 1; k++)
                            issuedRecords[k] = issuedRecords[k + 1];
                        issuedCount--; break;
                    }
                return;
            }
        cout << "Item ID " << id << " not found.\n";
    }

    void saveToFile(const string& fn = "library_catalog.txt") const {
        ofstream f(fn);
        if (!f) { cout << "Cannot open file.\n"; return; }
        for (int i = 0; i < itemCount; i++)
            if (catalog[i])
                f << catalog[i]->getItemID() << ","
                << catalog[i]->getTitle() << ","
                << catalog[i]->getAuthor() << ","
                << catalog[i]->getPublicationYear() << "\n";
        f.close();
        cout << "Catalog saved to " << fn << "\n";
    }

    void loadFromFile(const string& fn = "library_catalog.txt") {
        ifstream f(fn);
        if (!f) { cout << "Cannot open file.\n";
                   return; }
        string line;
        while (getline(f, line)) cout << "Loaded: " << line << "\n";
        f.close();
        cout << "Data loaded from " << fn << "\n";
    }

    void displayAllItems() const {
        if (itemCount == 0) { cout << "Catalog is empty.\n"; 
             return; }
        cout << "=== Library Catalog ===\n";
        for (int i = 0; i < itemCount; i++)
            if (catalog[i]) catalog[i]->displayItem();
    }
};

// ===========================================================
// MODULE 4 FINANCE
// ===========================================================

class FeeRecord {
private:
    Student* studentRef;
    double   semesterFee, hostelFee, libraryFine;
    double   totalPaid, balance;
public:
    FeeRecord(Student* s = nullptr,
        double sf = 0.0, double hf = 0.0, double lf = 0.0)
        : studentRef(s), semesterFee(sf), hostelFee(hf),
        libraryFine(lf), totalPaid(0.0) {
        balance = semesterFee + hostelFee + libraryFine;
    }
    FeeRecord(const FeeRecord& o)
        : studentRef(o.studentRef), semesterFee(o.semesterFee),
        hostelFee(o.hostelFee), libraryFine(o.libraryFine),
        totalPaid(o.totalPaid), balance(o.balance) {
        cout << "[FeeRecord] Copy constructor called.\n";
    }

    FeeRecord& operator=(const FeeRecord& o) {
        if (this != &o) {
            studentRef = o.studentRef;
            semesterFee = o.semesterFee;
            hostelFee = o.hostelFee;
            libraryFine = o.libraryFine;
            totalPaid = o.totalPaid;
            balance = o.balance;
            cout << "[FeeRecord] Copy assignment called.\n";
        }
        return *this;
    }

    void operator-=(double payment) {
        if (payment <= 0) { cout << "Invalid payment.\n"; return; }
        totalPaid += payment;
        balance -= payment;
        if (balance < 0) balance = 0;
        cout << "Payment Rs." << payment << " recorded."
            << " Balance: Rs." << balance << "\n";
    }

    Student* getStudent()     const { return studentRef; }
    double   getSemesterFee() const { return semesterFee; }
    double   getHostelFee()   const { return hostelFee; }
    double   getLibraryFine() const { return libraryFine; }
    double   getTotalPaid()   const { return totalPaid; }
    double   getBalance()     const { return balance; }

    void displayFeeRecord() const {
        cout << "------------------------------\n";
        if (studentRef)
            cout << "Student      : " << studentRef->getName()
            << " (" << studentRef->getRollNo() << ")\n";
        cout << "Semester Fee : Rs." << semesterFee << "\n";
        cout << "Hostel Fee   : Rs." << hostelFee << "\n";
        cout << "Library Fine : Rs." << libraryFine << "\n";
        cout << "Total Paid   : Rs." << totalPaid << "\n";
        cout << "Balance      : Rs." << balance << "\n";
    }
};

class Invoice {
private:
    static int invoiceCounter;   
    int    invoiceID;
    string date;
    double totalAmount;
    string* items;               
    int     itemCount;
public:
    Invoice(string d = "", double amt = 0.0)
        : date(d), totalAmount(amt), itemCount(0) {
        invoiceCounter++;
        invoiceID = invoiceCounter;
        items = new string[20];
        cout << "Invoice #" << invoiceID << " created.\n";
    }

    ~Invoice() {
        delete[] items;
        cout << "Invoice #" << invoiceID << " destroyed.\n";
    }

    static int getInvoiceCount() { return invoiceCounter; }

    void addItem(const string& item) {
        if (itemCount < 20) items[itemCount++] = item;
    }

    void displayInvoice() const {
        cout << "------------------------------\n";
        cout << "Invoice ID : " << invoiceID << "\n";
        cout << "Date       : " << date << "\n";
        cout << "Amount     : Rs." << totalAmount << "\n";
        for (int i = 0; i < itemCount; i++)
            cout << "  - " << items[i] << "\n";
    }

    friend ostream& operator<<(ostream& out, const Invoice& inv) {
        out << "Invoice #" << inv.invoiceID
            << " | Date: " << inv.date
            << " | Rs." << inv.totalAmount;
        return out;
    }
};

int Invoice::invoiceCounter = 0;

// ===========================================================
// MODULE 5 HOSTEL MANAGEMENT
// ===========================================================

class Accommodation {
protected:
    int    roomNumber;
    double monthlyRent;
    bool   isOccupied;
public:
    Accommodation(int rn = 0, double rent = 0.0)
        : roomNumber(rn), monthlyRent(rent), isOccupied(false) {
    }

    virtual void allocateRoom(Student* s) = 0;
    virtual void vacateRoom() = 0;
    virtual void displayAccommodation() const = 0;

    bool   getIsOccupied()  const { return isOccupied; }
    int    getRoomNumber()  const { return roomNumber; }
    double getMonthlyRent() const { return monthlyRent; }

    virtual ~Accommodation() = default;
};

class Reportable {
public:
    virtual void generateReport() const = 0;
    virtual ~Reportable() = default;
};

class Room : public Accommodation {
private:
    string   roomType;
    int      floor;
    Student* occupants[3];
    int      occupantCount, maxOccupants;
public:
    Room(int rn = 0, double rent = 0.0,
        string type = "Single", int flr = 1)
        : Accommodation(rn, rent),
        roomType(type), floor(flr), occupantCount(0) {
        for (int i = 0; i < 3; i++) occupants[i] = nullptr;
        if (type == "Single") maxOccupants = 1;
        else if (type == "Double") maxOccupants = 2;
        else                       maxOccupants = 3;
    }

    bool   getOccupancyStatus() const { return isOccupied; }
    string getRoomType()        const { return roomType; }

    void allocateRoom(Student* student) override {
        if (occupantCount >= maxOccupants) {
            cout << "Room " << roomNumber << " is full.\n"; return;
        }
        occupants[occupantCount++] = student;
        isOccupied = true;
        cout << "Room " << roomNumber << " [" << roomType
            << "] allocated to " << student->getName() << "\n";
    }

    void vacateRoom() override {
        for (int i = 0; i < 3; i++) occupants[i] = nullptr;
        occupantCount = 0;
        isOccupied = false;
        cout << "Room " << roomNumber << " vacated.\n";
    }

    void displayAccommodation() const override {
        cout << "  Room " << roomNumber
            << " [" << roomType << "] Floor:" << floor
            << " | Rent: Rs." << monthlyRent
            << " | " << (isOccupied ? "Occupied" : "Available")
            << " (" << occupantCount << "/" << maxOccupants << ")\n";
        for (int i = 0; i < occupantCount; i++)
            if (occupants[i])
                cout << "    -> " << occupants[i]->getName()
                << " (" << occupants[i]->getRollNo() << ")\n";
    }
};

class HostelBlock {
private:
    string blockName;
    Room* rooms[100];
    int    totalRooms;
public:
    HostelBlock(string name = "Block-A")
        : blockName(name), totalRooms(0) {
        for (int i = 0; i < 100; i++) rooms[i] = nullptr;
    }
    ~HostelBlock() {
        for (int i = 0; i < totalRooms; i++) delete rooms[i];
    }

    void addRoom(Room* r) {
        if (totalRooms < 100) rooms[totalRooms++] = r;
    }

    Room* findAvailableRoom() {
        for (int i = 0; i < totalRooms; i++)
            if (rooms[i] && !rooms[i]->getOccupancyStatus())
                return rooms[i];
        return nullptr;
    }

    void displayBlockInfo() const {
        cout << "Block: " << blockName
            << " | Rooms: " << totalRooms << "\n";
        for (int i = 0; i < totalRooms; i++)
            if (rooms[i]) rooms[i]->displayAccommodation();
    }

    string getBlockName()  const { return blockName; }
    int    getTotalRooms() const { return totalRooms; }
};
class HostelManager : public Accommodation, public Reportable {
private:
    HostelBlock* managedBlock; 
public:
    HostelManager(HostelBlock* block = nullptr)
        : Accommodation(0, 0.0), managedBlock(block) {
    }

    void allocateRoom(Student* student) override {
        if (!managedBlock) { cout << "No block assigned.\n"; return; }
        Room* r = managedBlock->findAvailableRoom();
        if (r) r->allocateRoom(student);
        else   cout << "No rooms available.\n";
    }

    void vacateRoom() override {
        cout << "Specify room number to vacate.\n";
    }

    void displayAccommodation() const override {
        if (managedBlock) managedBlock->displayBlockInfo();
        else cout << "No block assigned.\n";
    }

    void generateReport() const override {
        cout << "========== Hostel Report ==========\n";
        if (managedBlock) {
            managedBlock->displayBlockInfo();
            cout << "Total Rooms: " << managedBlock->getTotalRooms() << "\n";
        }
        cout << "===================================\n";
    }
};

// ===========================================================
// MODULE 6  REPORTS & UTILITIES
// ===========================================================

class Reports {
public:
    static void generateStudentReport(Student* students[], int count) {
        cout << "\n========== STUDENT REPORT ==========\n";
        if (count == 0) { cout << "No students.\n"; return; }
        for (int i = 0; i < count; i++) students[i]->displayInfo();
        cout << "Total Students: " << count << "\n";
        cout << "=====================================\n";
    }

    static void generateCourseReport(Course* courses[], int count) {
        cout << "\n========== COURSE REPORT ==========\n";
        if (count == 0) { cout << "No courses.\n"; 
            return; }
        for (int i = 0; i < count; i++) cout << *courses[i] << "\n";
        cout << "Total Courses: " << count << "\n";
        cout << "====================================\n";
    }

    static void generateLibraryReport(Library& library) {
        cout << "\n========== LIBRARY REPORT ==========\n";
        library.displayAllItems();
        cout << "=====================================\n";
    }

    static void generateFinanceReport(FeeRecord* records[], int count) {
        cout << "\n========== FINANCE REPORT ==========\n";
        if (count == 0) { cout << "No fee records.\n";
            return; }
        double total = 0.0;
        for (int i = 0; i < count; i++) {
            records[i]->displayFeeRecord();
            total += records[i]->getBalance();
        }
        cout << "Total Pending: Rs." << total << "\n";
        cout << "=====================================\n";
    }

    static void generateHostelReport(HostelManager& hm) {
        cout << "\n";
        hm.generateReport();
    }
};

class Utils {
public:
    static void sortStudentsByGPA(Student* s[], int count) {
        for (int i = 0; i < count - 1; i++)
            for (int j = 0; j < count - i - 1; j++)
                if (s[j]->getGPA() < s[j + 1]->getGPA()) {
                    Student* tmp = s[j]; s[j] = s[j + 1]; s[j + 1] = tmp;
                }
        cout << "Students sorted by GPA.\n";
    }

    static Student* searchStudentByRollNo(Student* s[], int count,
        const string& roll) {
        for (int i = 0; i < count; i++)
            if (s[i]->getRollNo() == roll) return s[i];
        return nullptr;
    }

    static Course* searchCourseByCode(Course* c[], int count,
        const string& code) {
        for (int i = 0; i < count; i++)
            if (c[i]->getCourseCode() == code) return c[i];
        return nullptr;
    }

    static int getIntInput(const string& prompt) {
        int val;
        cout << prompt;
        while (!(cin >> val)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid. " << prompt;
        }
        cin.ignore();
        return val;
    }

    static string getStringInput(const string& prompt) {
        string val;
        cout << prompt;
        getline(cin, val);
        return val;
    }
};

// ===========================================================
// MAIN SYSTEM CLASS
// ===========================================================

class SmartCampusManagementSystem {
private:
    Student* students[100];
    Faculty* facultyMembers[50];
    Staff* staffMembers[50];
    Course* courses[50];
    FeeRecord* feeRecords[100];
    HostelManager* hostelManager;
    Library        library;

    int studentCount, facultyCount, staffCount;
    int courseCount, feeRecordCount;

public:
    SmartCampusManagementSystem()
        : hostelManager(nullptr),
        studentCount(0), facultyCount(0), staffCount(0),
        courseCount(0), feeRecordCount(0) {
    }

    ~SmartCampusManagementSystem() {
        for (int i = 0; i < studentCount; i++) delete students[i];
        for (int i = 0; i < facultyCount; i++) delete facultyMembers[i];
        for (int i = 0; i < staffCount; i++) delete staffMembers[i];
        for (int i = 0; i < courseCount; i++) delete courses[i];
        for (int i = 0; i < feeRecordCount; i++) delete feeRecords[i];
        delete hostelManager;
    }

    
    void personMenu() {
        int ch;
        do {
            cout << "\n--- Person Management ---\n"
                << "1. Add Student\n2. Add Faculty\n3. Add Staff\n"
                << "4. Show Students\n5. Show Faculty\n6. Show Staff\n0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) {
                string n = Utils::getStringInput("Name: ");
                string c = Utils::getStringInput("CNIC: ");
                string con = Utils::getStringInput("Contact: ");
                int age = Utils::getIntInput("Age: ");
                string r = Utils::getStringInput("Roll No: ");
                int sem = Utils::getIntInput("Semester: ");
                float gpa; cout << "GPA: "; cin >> gpa; cin.ignore();
                if (studentCount < 100)
                    students[studentCount++] = new Student(n, c, con, age, r, sem, gpa);
                cout << "Student added.\n";
            }
            else if (ch == 2) {
                string n = Utils::getStringInput("Name: ");
                string c = Utils::getStringInput("CNIC: ");
                string con = Utils::getStringInput("Contact: ");
                int age = Utils::getIntInput("Age: ");
                string eid = Utils::getStringInput("Employee ID: ");
                string dep = Utils::getStringInput("Department: ");
                string des = Utils::getStringInput("Designation: ");
                if (facultyCount < 50)
                    facultyMembers[facultyCount++] = new Faculty(n, c, con, age, eid, dep, des);
                cout << "Faculty added.\n";
            }
            else if (ch == 3) {
                string n = Utils::getStringInput("Name: ");
                string c = Utils::getStringInput("CNIC: ");
                string con = Utils::getStringInput("Contact: ");
                int age = Utils::getIntInput("Age: ");
                string sid = Utils::getStringInput("Staff ID: ");
                string rol = Utils::getStringInput("Role: ");
                double sal; cout << "Salary: "; cin >> sal; cin.ignore();
                if (staffCount < 50)
                    staffMembers[staffCount++] = new Staff(n, c, con, age, sid, rol, sal);
                cout << "Staff added.\n";
            }
            else if (ch == 4) {
                if (studentCount == 0) { cout << "No students.\n"; continue; }
                for (int i = 0; i < studentCount; i++) students[i]->displayInfo();
            }
            else if (ch == 5) {
                if (facultyCount == 0) { cout << "No faculty.\n"; continue; }
                for (int i = 0; i < facultyCount; i++) facultyMembers[i]->displayInfo();
            }
            else if (ch == 6) {
                if (staffCount == 0) { cout << "No staff.\n"; continue; }
                for (int i = 0; i < staffCount; i++) staffMembers[i]->displayInfo();
            }
        } while (ch != 0);
    }

    //  Course Menu //
    void courseMenu() {
        int ch;
        do {
            cout << "\n--- Course Management ---\n"
                << "1. Add Course\n2. Enroll Student\n"
                << "3. Show Courses\n4. Search Course\n0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) {
                string code = Utils::getStringInput("Course Code: ");
                string name = Utils::getStringInput("Course Name: ");
                int cr = Utils::getIntInput("Credit Hours: ");
                int cap = Utils::getIntInput("Max Capacity: ");
                if (courseCount < 50)
                    courses[courseCount++] = new Course(code, name, cr, cap);
                cout << "Course added.\n";
            }
            else if (ch == 2) {
                if (studentCount == 0 || courseCount == 0) {
                    cout << "Add students and courses first.\n"; 
                      continue;
                }
                string roll = Utils::getStringInput("Student Roll No: ");
                string code = Utils::getStringInput("Course Code: ");
                Student* s = Utils::searchStudentByRollNo(students, studentCount, roll);
                Course* c = Utils::searchCourseByCode(courses, courseCount, code);
                if (!s) { cout << "Student not found.\n"; 
                   continue; }
                if (!c) { cout << "Course not found.\n"; 
                    continue; }
                try {
                    c->enrollStudent();
                    s->addCourse(c);
                    cout << s->getName() << " enrolled in " << c->getCourseCode() << "\n";
                }
                catch (CapacityExceededException& e) {
                    cout << e.what() << "\nAdded to waiting list.\n";
                    c->addToWaitingList(s);
                }
            }
            else if (ch == 3) {
                if (courseCount == 0) { cout << "No courses.\n"; continue; }
                for (int i = 0; i < courseCount; i++) cout << *courses[i] << "\n";
            }
            else if (ch == 4) {
                string code = Utils::getStringInput("Course Code: ");
                Course* c = Utils::searchCourseByCode(courses, courseCount, code);
                if (c) cout << *c << "\n";
                else   cout << "Not found.\n";
            }
        } while (ch != 0);
    }

    // Library Menu //
    void libraryMenu() {
        int ch;
        do {
            cout << "\n--- Library Management ---\n"
                << "1. Add Book\n2. Add Journal\n3. Search by Title\n"
                << "4. Issue Item\n5. Return Item\n6. Show All\n"
                << "7. Save to File\n8. Load from File\n0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) {
                int    id = Utils::getIntInput("Item ID: ");
                string t = Utils::getStringInput("Title: ");
                string a = Utils::getStringInput("Author: ");
                int    yr = Utils::getIntInput("Year: ");
                string isbn = Utils::getStringInput("ISBN: ");
                string gen = Utils::getStringInput("Genre: ");
                int    cop = Utils::getIntInput("Copies: ");
                library.addItem(new Book(id, t, a, yr, isbn, gen, cop));
            }
            else if (ch == 2) {
                int    id = Utils::getIntInput("Item ID: ");
                string t = Utils::getStringInput("Title: ");
                string a = Utils::getStringInput("Author: ");
                int    yr = Utils::getIntInput("Year: ");
                string issn = Utils::getStringInput("ISSN: ");
                int    vol = Utils::getIntInput("Volume: ");
                int    iss = Utils::getIntInput("Issue No: ");
                library.addItem(new Journal(id, t, a, yr, issn, vol, iss));
            }
            else if (ch == 3) {
                library.searchByTitle(Utils::getStringInput("Title: "));
            }
            else if (ch == 4) {
                int    id = Utils::getIntInput("Item ID: ");
                string roll = Utils::getStringInput("Roll No: ");
                string date = Utils::getStringInput("Date: ");
                library.issueItem(id, roll, date);
            }
            else if (ch == 5) {
                library.returnItem(Utils::getIntInput("Item ID: "));
            }
            else if (ch == 6) { library.displayAllItems(); }
            else if (ch == 7) { library.saveToFile(); }
            else if (ch == 8) { library.loadFromFile(); }
        } while (ch != 0);
    }

    // Finance Menu //
    void financeMenu() {
        int ch;
        do {
            cout << "\n--- Finance Management ---\n";
                cout << "1. Add Fee Record\n";
                cout << " 2. Make Payment\n";
                cout << "3. Show All Records\n";
                cout << " 4. Generate Invoice\n";
                cout << "5. Demo Copy Constructor\n";
                cout << " 0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) {
                if (studentCount == 0) { cout << "Add students first.\n"; continue; }
                string roll = Utils::getStringInput("Roll No: ");
                Student* s = Utils::searchStudentByRollNo(students, studentCount, roll);
                if (!s) { cout << "Not found.\n"; continue; }
                double sf, hf, lf;
                cout << "Semester Fee: "; cin >> sf; cin.ignore();
                cout << "Hostel Fee  : "; cin >> hf; cin.ignore();
                cout << "Library Fine: "; cin >> lf; cin.ignore();
                if (feeRecordCount < 100)
                    feeRecords[feeRecordCount++] = new FeeRecord(s, sf, hf, lf);
                cout << "Fee record added.\n";
            }
            else if (ch == 2) {
                if (feeRecordCount == 0) { cout << "No records.\n"; continue; }
                string roll = Utils::getStringInput("Roll No: ");
                for (int i = 0; i < feeRecordCount; i++)
                    if (feeRecords[i]->getStudent() &&
                        feeRecords[i]->getStudent()->getRollNo() == roll) {
                        double pay; cout << "Amount: Rs."; cin >> pay; cin.ignore();
                        *feeRecords[i] -= pay;
                        break;
                    }
            }
            else if (ch == 3) {
                for (int i = 0; i < feeRecordCount; i++)
                    feeRecords[i]->displayFeeRecord();
            }
            else if (ch == 4) {
                string date = Utils::getStringInput("Date: ");
                double amt;
                cout << "Amount: Rs."; 
                cin >> amt;
                   cin.ignore();
                Invoice* inv = new Invoice(date, amt);
                inv->displayInvoice();
                delete inv;
            }
            else if (ch == 5) {
                if (feeRecordCount == 0) { cout << "No records.\n"; 
                  continue; }
                FeeRecord copy = *feeRecords[0]; 
                cout << "Copied record:\n";
                copy.displayFeeRecord();
            }
        } while (ch != 0);
    }

    //  Hostel Menu //
    void hostelMenu() {
        int ch;
        do {
            cout << "\n--- Hostel Management ---\n"
                << "1. Setup Block\n2. Allocate Room\n"
                << "3. Show Hostel Info\n4. Hostel Report\n0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) {
                if (hostelManager) { cout << "Already set up.\n"; 
                   continue; }
                HostelBlock* block = new HostelBlock("Block-A");
                int n = Utils::getIntInput("How many rooms: ");
                for (int i = 0; i < n; i++) {
                    int    rn = Utils::getIntInput("Room Number: ");
                    double rent; 
                    cout << "Rent: ";
                    cin >> rent;
                    cin.ignore();
                    string type = Utils::getStringInput("Type (Single/Double/Triple): ");
                    int    flr = Utils::getIntInput("Floor: ");
                    block->addRoom(new Room(rn, rent, type, flr));
                }
                hostelManager = new HostelManager(block);
                cout << "Hostel set up.\n";
            }
            else if (ch == 2) {
                if (!hostelManager) { cout << "Setup hostel first.\n"; 
                    continue; }
                if (studentCount == 0) { cout << "Add students first.\n";
                    continue; }
                string roll = Utils::getStringInput("Roll No: ");
                Student* s = Utils::searchStudentByRollNo(students, studentCount, roll);
                if (!s) { cout << "Not found.\n";
                       continue; }
                hostelManager->allocateRoom(s);
            }
            else if (ch == 3) {
                if (!hostelManager) { cout << "No hostel.\n"; continue; }
                hostelManager->displayAccommodation();
            }
            else if (ch == 4) {
                if (!hostelManager) { cout << "No hostel.\n"; continue; }
                hostelManager->generateReport();
            }
        } while (ch != 0);
    }

    void reportsMenu() {
        int ch;
        do {
            cout << "\n--- Reports & Utilities ---\n";
                cout << "1. Student Report\n";
                cout << "    2. Course Report\n";
                cout << "3. Library Report\n";
                cout << "   4. Finance Report\n";
                cout << "5. Hostel Report\n";
                cout << "   6. Full Campus Report\n";
                cout << "7. Sort Students by GPA\n";
                cout << "  8. Search Student\n";
                cout << "9. Search Course\n";
                cout << "  0. Back\n";
            ch = Utils::getIntInput("Choice: ");

            if (ch == 1) Reports::generateStudentReport(students, studentCount);
            else if (ch == 2) Reports::generateCourseReport(courses, courseCount);
            else if (ch == 3) Reports::generateLibraryReport(library);
            else if (ch == 4) Reports::generateFinanceReport(feeRecords, feeRecordCount);
            else if (ch == 5) {
                if (hostelManager) Reports::generateHostelReport(*hostelManager);
                else cout << "No hostel.\n";
            }
            else if (ch == 6) {
                cout << "\n========== FULL CAMPUS REPORT ==========\n";
                Reports::generateStudentReport(students, studentCount);
                Reports::generateCourseReport(courses, courseCount);
                Reports::generateLibraryReport(library);
                Reports::generateFinanceReport(feeRecords, feeRecordCount);
                if (hostelManager) Reports::generateHostelReport(*hostelManager);
                cout << "=========================================\n";
            }
            else if (ch == 7) {
                Utils::sortStudentsByGPA(students, studentCount);
                for (int i = 0; i < studentCount; i++)
                    cout << students[i]->getName()   << " - GPA: " << students[i]->getGPA() << "\n";
            }
            else if (ch == 8) {
                string roll = Utils::getStringInput("Roll No: ");
                Student* s = Utils::searchStudentByRollNo(students, studentCount, roll);
                if (s) s->displayInfo(); 
                     else cout << "Not found.\n";
            }
            else if (ch == 9) {
                string code = Utils::getStringInput("Course Code: ");
                Course* c = Utils::searchCourseByCode(courses, courseCount, code);
                if (c) cout << *c << "\n"; 
                    else cout << "Not found.\n";
            }
        } while (ch != 0);
    }
    void run() {
        int choice;
        do {
            cout << "\n===== SMART CAMPUS MANAGEMENT SYSTEM =====\n";
            cout << "       HITEC University Taxila | OOP\n";
            cout << "===========================================\n";
            cout << "1. Person Management\n";
            cout << "2. Course Management\n";
            cout << "3. Library Management\n";
            cout << "4. Finance Management\n";
            cout << "5. Hostel Management\n";
            cout << "6. Reports & Utilities\n";
            cout << "0. Exit\n";
            cout << "===========================================\n";
            choice = Utils::getIntInput("Enter choice: ");

            switch (choice) {
            case 1: personMenu(); 
                                break;
            case 2: courseMenu(); 
                                break;
            case 3: libraryMenu();
                               break;
            case 4: financeMenu();
                                break;
            case 5: hostelMenu(); 
                                break;
            case 6: reportsMenu();
                               break;
            case 0: cout << "Exiting SCMS. Goodbye!\n";
                                                    break;
            default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

// ====================
// MAIN
// =====================
int main() {
    SmartCampusManagementSystem scms;
    scms.run();
    return 0;
}