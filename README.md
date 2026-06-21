Smart Campus Management System (SCMS):

Project Info:

Student 1: Romaisa Khan | Roll No: 25-CS-105 | Course: CS-104L OOP | HITEC University Taxila
Student 2: Fatima Batool | Roll No: 25-CS-088 | Course: CS-104L OOP | HITEC University Taxila
Department: Computer Science
Semester: Spring 2026
Instructor: Sir Mohsin Shahzad


Project Description
The Smart Campus Management System (SCMS) is a console-based C++ application designed to manage the core operations of a university campus. The system handles student and faculty records through an organized person hierarchy, manages course registrations and enrollments, maintains a digital library catalog with file-based storage, tracks student fee records and generates invoices, manages hostel room allocations, and produces campus-wide reports. The project demonstrates real-world application of Object-Oriented Programming by integrating six fully functional modules into one unified system. All modules interact through a central menu-driven interface, making the system easy to navigate and use.


OOP Concepts Demonstrated

#OOP ConceptWhere It Is Used1Class & ObjectEvery module defines classes (Person, Course, Book, Invoice, Room) and creates objects2EncapsulationPrivate data members with public getters/setters in all classes3AbstractionAbstract base class Person with pure virtual displayInfo()4Inheritance (Single)Student and Faculty both inherit from Person5Inheritance (Multi-level)GradStudent inherits from Student which inherits from Person6Inheritance (Multiple)HostelManager inherits from both Accommodation and Reportable7Inheritance (Virtual)Virtual public Person used to avoid diamond problem8Polymorphism (Runtime)displayInfo() overridden in Student, Faculty, Staff, GradStudent9Polymorphism (Compile-time)Function overloading used in multiple classes10Pure Virtual FunctiondisplayInfo() declared as pure virtual in Person base class11Virtual FunctionVirtual destructor and virtual displayInfo() in Person12Friend Functionoperator<< overloaded as friend in Course class13Operator Overloading== operator overloaded in Course, << overloaded for display14Constructor OverloadingMultiple constructors in Student, Invoice, FeeRecord classes15DestructorCustom destructor in Invoice to delete dynamically allocated array16Copy ConstructorDeep copy constructor implemented in Invoice class17Copy Assignment Operatoroperator= with self-assignment guard in Invoice class18Static Memberstatic invoiceCounter in Invoice tracks total invoices created19this PointerUsed in copy assignment operator for self-assignment check20Dynamic Memorynew and delete[] used in Invoice for items array on heap21Exception Handlingtry-catch blocks with CapacityExceededException and OverdueException22Custom ExceptionCapacityExceededException and OverdueException classes defined23File I/OLibrary module saves and loads catalog using fstream24TemplatesTemplate used in utility/reporting functions25CompositionHostelBlock object composed inside HostelManager class.


Modules

Module 1 — Person Hierarchy
Defines the base class Person as an abstract class with pure virtual displayInfo(). Derived classes include Student, GradStudent (multi-level), Faculty, and Staff. Demonstrates inheritance, polymorphism, and virtual functions.

Module 2 — Course & Enrollment
Manages course creation, student enrollment, and waiting lists. Includes Course and Enrollment classes. Demonstrates operator overloading (==, <<), friend functions, and exception handling with CapacityExceededException.

Module 3 — Library System
Handles a digital library catalog with LibraryItem, Book, and Journal classes. Supports checkout, return, and overdue fine calculation. Uses file I/O to save and load the catalog. Throws OverdueException on late returns.

Module 4 — Fee & Finance
Manages student fee records and invoice generation using FeeRecord and Invoice classes. Demonstrates static members, dynamic memory allocation, deep copy constructor, and copy assignment operator.

Module 5 — Hostel Management
Handles Hostel room allocation using Accommodation, Reportable, Room, HostelBlock, and HostelManager classes. Demonstrates multiple inheritance, virtual inheritance, and composition.

Module 6 — Reporting & Utilities
Provides campus-wide reporting through the Reports and SmartCampusManagementSystem classes. Acts as the main controller that integrates all six modules into a single menu-driven interface.


How to Compile & Run

bashg++ -std=c++17 "oop project in VCC.cpp" -o scms.exe
./scms.exe

Or for separate module files:

bashg++ -std=c++17 Module1_Person.cpp Module2_Course.cpp Module3.cpp Module4.cpp Module5.cpp Module6.cpp MainSystem.cpp -o scms.exe
./scms.exe


GitHub Repository:

https://github.com/romaisakhan10/-First-commit-


HITEC University Taxila | Department of Computer Science | CS-104L Object-Oriented Programming | Spring 2026
