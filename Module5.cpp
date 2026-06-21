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
        cout << " Hostel Report \n";
        if (managedBlock) {
            managedBlock->displayBlockInfo();
            cout << "Total Rooms: " << managedBlock->getTotalRooms() << "\n";
        }
        cout << "\n";
    }
};
