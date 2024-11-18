#include "StudentList.h"

// Constructor to initialize the list
StudentList::StudentList() {
    head = nullptr;
    tail = nullptr;
    numStudents = 0;
}

// Return the number of students in the list
int StudentList::listSize() {
    return numStudents;
}

// Add a student to the front of the list
void StudentList::addFront(Student s) {
    Node* newNode = new Node(s, head, nullptr);
    if (head) head->prev = newNode;
    head = newNode;
    if (!tail) tail = head; // If list was empty
    numStudents++;
}

// Add a student to the back of the list
void StudentList::addBack(Student s) {
    Node* newNode = new Node(s, nullptr, tail);
    if (tail) tail->next = newNode;
    tail = newNode;
    if (!head) head = tail; // If list was empty
    numStudents++;
}

// Print the list of students
void StudentList::printList() {
    Node* current = head;
    while (current) {
        cout << "Name: " << current->data.name 
             << ", ID: " << current->data.id 
             << ", GPA: " << current->data.GPA << endl;
        current = current->next;
    }
}

// Remove the student at the front of the list
void StudentList::popFront() {
    if (!head) {
        cout << "List is empty, nothing to remove." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr; // List is now empty
    delete temp;
    numStudents--;
}

// Remove the student at the back of the list
void StudentList::popBack() {
    if (!tail) {
        cout << "List is empty, nothing to remove." << endl;
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr; // List is now empty
    delete temp;
    numStudents--;
}

// Insert a student at a specific index
void StudentList::insertStudent(Student s, int index) {
    if (index <= 0) {
        addFront(s);
    } else if (index >= numStudents) {
        addBack(s);
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* newNode = new Node(s, current->next, current);
        current->next->prev = newNode;
        current->next = newNode;
        numStudents++;
    }
}

// Retrieve a student by ID
Student StudentList::retrieveStudent(int idNum) {
    Node* current = head;
    while (current) {
        if (current->data.id == idNum) return current->data;
        current = current->next;
    }
    cout << "No student found with ID: " << idNum << endl;
    return Student();
}

// Remove a student by ID
void StudentList::removeStudentById(int idNum) {
    Node* current = head;
    while (current) {
        if (current->data.id == idNum) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next; // Removing head

            if (current->next) current->next->prev = current->prev;
            else tail = current->prev; // Removing tail

            delete current;
            numStudents--;
            return;
        }
        current = current->next;
    }
    cout << "No student found with ID: " << idNum << endl;
}

// Update GPA by ID
void StudentList::updateGPA(int idNum, float newGPA) {
    Node* current = head;
    while (current) {
        if (current->data.id == idNum) {
            current->data.GPA = newGPA;
            return;
        }
        current = current->next;
    }
    cout << "No student found with ID: " << idNum << endl;
}

// Merge another list into this list
void StudentList::mergeList(StudentList& otherList) {
    if (!otherList.head) return; // Other list is empty
    if (!head) { // Current list is empty
        head = otherList.head;
        tail = otherList.tail;
    } else {
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    }
    numStudents += otherList.numStudents;

    otherList.head = nullptr;
    otherList.tail = nullptr;
    otherList.numStudents = 0;
}

// Create an honor roll list with students above a certain GPA
StudentList StudentList::honorRoll(float minGPA) {
    StudentList honorRollList;
    Node* current = head;
    while (current) {
        if (current->data.GPA >= minGPA) {
            honorRollList.addBack(current->data);
        }
        current = current->next;
    }
    return honorRollList;
}
