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