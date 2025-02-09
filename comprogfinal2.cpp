#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int MAX_SIZE = 500;

class StudentManager {

public:
    struct Student {
        string name;
        string course;
        float grade;
        int id;
    };
    vector<Student> students;
    StudentManager(const string& filename) {
        students = loadStudentsFromFile(filename);
    }

    void showAllStudents() {
        if (students.empty()) {
            cout << "Student list is empty" << endl;
            return;
        }

        cout << "ID\t\t\tName\t\t\tCourse\t\t\tGrade" << endl;
        for (size_t i = 0; i < students.size(); i++) {
            cout << students[i].id << "\t\t\t" << students[i].name << "\t\t\t" << students[i].course << "\t\t\t" << students[i].grade << endl;
        }
    }

    void searchById(int id) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].id == id) {
                cout << "ID\t\t\tName\t\t\tCourse\t\t\tGrade" << endl;
                cout << students[i].id << "\t\t\t" << students[i].name << "\t\t\t" << students[i].course << "\t\t\t" << students[i].grade << endl;
                return;
            }
        }
        cout << "ID not found" << endl;
    }

    void sortByName() {
        for (size_t i = 0; i < students.size() - 1; i++) {
            for (size_t j = 0; j < students.size() - i - 1; j++) {
                if (students[j].name > students[j + 1].name) {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        cout << "Sorted by name" << endl;
        showAllStudents();
    }

    void sortByGrade() {
        for (size_t i = 0; i < students.size() - 1; i++) {
            int min_idx = i;
            for (size_t j = i + 1; j < students.size(); j++) {
                if (students[j].grade < students[min_idx].grade)
                    min_idx = j;
            }
            Student temp = students[i];
            students[i] = students[min_idx];
            students[min_idx] = temp;
        }
        cout << "Sorted by grade" << endl;
        showAllStudents();
    }

    void addStudent() {
        if (students.size() >= MAX_SIZE) {
            cout << "Maximum student limit reached." << endl;
            return;
        }

        students.push_back(Student()); // Create a default Student object
        Student& newStudent = students.back(); // Get a reference to it

        cout << "Enter name of the student: ";
        cin.ignore();
        getline(cin, newStudent.name);
        cout << "Enter course of the student: ";
        getline(cin, newStudent.course);
        cout << "Enter grade of the student: ";
        cin >> newStudent.grade;

        int next_id = 1;
        if (!students.empty()) {
            for (size_t i = 0; i < students.size(); ++i) {
                next_id = max(next_id, students[i].id + 1);
            }
        }
        newStudent.id = next_id;

        cout << "Student added successfully" << endl;
    }

    void saveStudentsToFile(const string& filename) {
        ofstream outfile(filename);

        if (outfile.is_open()) {
            outfile << "ID\t\t\tName\t\t\tCourse\t\t\tGrade" << endl;
            for (size_t i = 0; i < students.size(); i++) {
                outfile << students[i].id << "\t\t\t" << students[i].name << "\t\t\t" << students[i].course << "\t\t\t" << students[i].grade << endl;
            }
            outfile.close();
            cout << "File saved successfully" << endl;
        } else {
            cerr << "Error opening file for saving." << endl;
        }
    }

private:
    vector<Student> loadStudentsFromFile(const string& filename) {
        vector<Student> loadedStudents;
        ifstream infile(filename);
        int next_id = 1;

        if (infile.is_open()) {
            string line;
            getline(infile, line);  // Skip the header line (if it exists)

            while (getline(infile, line)) {
                stringstream ss(line);
                int id;
                string name, course;
                float grade;

                if (ss >> id >> name >> course >> grade) {
                    loadedStudents.push_back(Student()); // Create a default Student object
                    Student& newStudent = loadedStudents.back();
                    newStudent.name = name;
                    newStudent.course = course;
                    newStudent.grade = grade;
                    newStudent.id = id;

                    next_id = max(next_id, id + 1);
                }
            }
            infile.close();
        } else {
            cerr << "Error opening file. Starting with an empty student list." << endl;
        }
        return loadedStudents;
    }
};

int main() {
    StudentManager manager("Student.txt");

    int choice;
    do {
        cout << "\t\t\t\t\tMENU\t\t\t\t" << endl;
        cout << "\t\t\t1. Show All Students\t\t\t\t" << endl;
        cout << "\t\t\t2. Search by ID\t\t\t\t" << endl;
        cout << "\t\t\t3. Sort by Name\t\t\t\t" << endl;
        cout << "\t\t\t4. Sort by Grade\t\t\t\t" << endl;
        cout << "\t\t\t5. Add Student\t\t\t\t" << endl;
        cout << "\t\t\t6. Save File\t\t\t\t" << endl;
        cout << "\t\t\t7. Exit\t\t\t\t\t" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.showAllStudents();
                break;
            case 2:
                int idNumber;
                cout << "Enter ID number: ";
                cin >> idNumber;
                manager.searchById(idNumber);
                break;
            case 3:
                manager.sortByName();
                break;
            case 4:
                manager.sortByGrade();
                break;
            case 5:
                manager.addStudent();
                break;
            case 6:
                manager.saveStudentsToFile("Student.txt");
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice!= 7);

    return 0;
}