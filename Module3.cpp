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