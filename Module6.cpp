class Reports {
public:
    static void generateStudentReport(Student* students[], int count) {
        cout << "\nSTUDENT REPORT \n";
        if (count == 0) { cout << "No students.\n"; return; }
        for (int i = 0; i < count; i++) students[i]->displayInfo();
        cout << "Total Students: " << count << "\n";
        cout << "\n";
    }

    static void generateCourseReport(Course* courses[], int count) {
        cout << "\n COURSE REPORT \n";
        if (count == 0) { cout << "No courses.\n"; 
            return; }
        for (int i = 0; i < count; i++) cout << *courses[i] << "\n";
        cout << "Total Courses: " << count << "\n";
        cout << "\n";
    }

    static void generateLibraryReport(Library& library) {
        cout << "\n LIBRARY REPORT \n";
        library.displayAllItems();
        cout << "\n";
    }

    static void generateFinanceReport(FeeRecord* records[], int count) {
        cout << "\n FINANCE REPORT \n";
        if (count == 0) { cout << "No fee records.\n";
            return; }
        double total = 0.0;
        for (int i = 0; i < count; i++) {
            records[i]->displayFeeRecord();
            total += records[i]->getBalance();
        }
        cout << "Total Pending: Rs." << total << "\n";
        cout << "\n";
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