#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib> // For atoi and atof

using namespace std;

// Student structure
struct Student {
    int id;
    string name;
    vector<pair<string, double> > courses;
    Student* next;
};

// Function to load data from the file
Student* loadData(const string& filename) {
    Student* head = NULL;
    ifstream inputFile(filename);

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            Student* newStudent = new Student;

            stringstream ss(line);
            string idStr, nameStr, courseData; // Combined course data

            getline(ss, idStr, ',');
            newStudent->id = atoi(idStr.c_str()); // Use atoi
            getline(ss, nameStr, ',');
            newStudent->name = nameStr;

            // Handle course data separately
            while (getline(ss, courseData, ',')) { // Get all course data at once
                stringstream courseSS(courseData); // New stream for course data
                string courseName, gradeStr;

                getline(courseSS, courseName, ':'); // Split course name and grade (using:)
                getline(courseSS, gradeStr);

                if (!courseName.empty() &&!gradeStr.empty()) { // Check for empty strings
                  pair<string, double> courseGradePair;
                  courseGradePair.first = courseName;
                  courseGradePair.second = atof(gradeStr.c_str()); // Use atof
                  newStudent->courses.push_back(courseGradePair);
                }
            }

            newStudent->next = head;
            head = newStudent;
        }
        inputFile.close();
    } else {
        cerr << "Error opening file for loading. A new file will be created." << endl;
        ofstream outfile(filename);
        outfile.close();
    }
    return head;
}

// Function to save data to the file
void saveData(Student* head, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        Student* current = head;
        while (current!= NULL) {
            outputFile << current->id << "," << current->name;
            for (size_t i = 0; i < current->courses.size(); ++i) { // Index-based loop
                outputFile << "," << current->courses[i].first << "," << current->courses[i].second;
            }
            outputFile << endl;
            current = current->next;
        }
        outputFile.close();
    } else {
        cerr << "Error opening file for saving." << endl;
    }
}

// Function to add a new student
Student* addStudent(Student* head) {
    Student* newStudent = new Student;

    cout << "Enter student ID: ";
    cin >> newStudent->id;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, newStudent->name);

    char addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        string courseName;
        double grade;
        cout << "Enter course name: ";
        getline(cin, courseName);
        cout << "Enter grade: ";
        cin >> grade;
        cin.ignore();
        pair<string, double> courseGradePair;
        courseGradePair.first = courseName;
        courseGradePair.second = grade;
        newStudent->courses.push_back(courseGradePair);


        cout << "Add another course? (y/n): ";
        cin >> addMore;
        cin.ignore();
    }

    newStudent->next = head;
    return newStudent;
}

// Function to display all students
void displayStudents(Student* head) {
    if (head == NULL) {
        cout << "No student records found." << endl;
        return;
    }

    Student* current = head;
    while (current!= NULL) {
        cout << "ID: " << current->id << endl;
        cout << "Name: " << current->name << endl;
        cout << "Courses: " << endl;
        for (size_t i = 0; i < current->courses.size(); ++i) { // Index-based loop
            cout << "  " << current->courses[i].first << ": " << current->courses[i].second << endl;
        }
        cout << endl;
        current = current->next;
    }
}
bool compareStudentsByName(const Student* a, const Student* b) {
    return a->name < b->name;
}
Student* sortStudentsByName(Student* head) {
    if (head == NULL || head->next == NULL) {
        return head; // Already sorted or empty
    }

    // 1. Convert linked list to vector of pointers
    vector<Student*> studentList;
    Student* current = head;
    while (current != NULL) {
        studentList.push_back(current);
        current = current->next;
    }

    // 2. Sort the vector
    sort(studentList.begin(), studentList.end(), compareStudentsByName);

    // 3. Reconstruct the linked list from the sorted vector
    head = studentList[0];
    for (size_t i = 0; i < studentList.size() - 1; ++i) {
        studentList[i]->next = studentList[i + 1];
    }
    studentList.back()->next = NULL; // Important: null-terminate the list

    return head;
}

// Function to delete a student
Student* deleteStudent(Student* head, int id) {
    if (head == NULL) {
        return NULL;
    }

    if (head->id == id) {
        Student* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Student* current = head;
    while (current->next!= NULL && current->next->id!= id) {
        current = current->next;
    }

    if (current->next == NULL) {
        cout << "Student with ID " << id << " not found." << endl;
        return head;
    }

    Student* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return head;
}

// Function to modify a student's name
Student* modifyStudent(Student* head, int id) {
    Student* current = head;
    while (current!= NULL) {
        if (current->id == id) {
            cout << "Enter new name (or press Enter to keep current): ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                current->name = newName;
            }
            return head;
        }
        current = current->next;
    }
    cout << "Student with ID " << id << " not found." << endl;
    return head;
}

// Function to search for a student by ID
Student* searchStudent(Student* head, int id) {
    Student* current = head;
    while (current!= NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to free the memory used by the linked list
void freeMemory(Student* head) {
    while (head!= NULL) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Student* head = loadData("students.txt");

    int choice;
    do {
        cout << "\nStudent Record Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Modify Student\n";
        cout << "5. Search Student\n";
        cout << "6. Save Data\n";
        cout << "7. Sort By name\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3: {
                int idToDelete;
                cout << "Enter ID to delete: ";
                cin >> idToDelete;
                head = deleteStudent(head, idToDelete);
                break;
            }
            case 4: {
                int idToModify;
                cout << "Enter ID to modify: ";
                cin >> idToModify;
                head = modifyStudent(head, idToModify);
                break;
            }
            case 5: {
                int idToSearch;
                cout << "Enter ID to search: ";
                cin >> idToSearch;
                Student* foundStudent = searchStudent(head, idToSearch);
                if (foundStudent) {
                    cout << "Student found:\n";
                    cout << "ID: " << foundStudent->id << endl;
                    cout << "Name: " << foundStudent->name << endl;
                    for (size_t i = 0; i < foundStudent->courses.size(); ++i) { // Index-based loop
                        cout << "  " << foundStudent->courses[i].first << ": " << foundStudent->courses[i].second << endl;
                    }
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 6:
                saveData(head, "students.txt");
                break;
            case 7:
                head = sortStudentsByName(head);
                cout << "Students sorted by name." << endl;
                break;
            case 8:
                cout << "exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice!= 8);

    saveData(head, "students.txt");
    freeMemory(head);

    return 0;
}