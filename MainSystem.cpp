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


int main() {
    SmartCampusManagementSystem scms;
    scms.run();
    return 0;
}