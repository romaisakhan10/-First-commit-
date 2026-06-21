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