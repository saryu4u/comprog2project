#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
const int maxsize = 500;

struct studentList {
    string name;
    string course;
    float grade;
    int id;
    studentList* next;
};

class Student {
public:
    string name;
    string course;
    float grade;
    int id;

    void showAllStudents(Student stud[], int size) {
        if (size < 1) {
            cout<<"Student is empty"<<endl;
        }else {
            for (int i = 0; i < size; i++) {
            cout << "id: " << stud[i].id << endl;
            cout << "name of the student: " << stud[i].name << endl;
            cout << "course: " << stud[i].course << endl;
            cout << "grade: " << stud[i].grade << endl;
            }
        }

    }
    void searchById(Student stud[], int id, int size) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (stud[i].id == id) {
                found = true;
                cout << "id: " << stud[i].id << endl;
                cout << "name of the student: " << stud[i].name << endl;
                cout << "course: " << stud[i].course << endl;
                cout << "grade: " << stud[i].grade << endl;
            }
        }
        if (!found) {
            cout << "id not found" << endl;
        }
    }
    void sortByName(Student stud[], int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (stud[j].name >  stud[j + 1].name) {
                    Student temp = stud[j];
                    stud[j] = stud[j + 1];
                    stud[j + 1] = temp;
                }
            }
        }
        cout << "sorted by name" << endl;
        for (int i = 0; i < size; i++) {
            cout << "id: " << stud[i].id << endl;
            cout << "name of the student: " << stud[i].name << endl;
            cout << "course: " << stud[i].course << endl;
            cout << "grade: " << stud[i].grade << endl;
        }
    }
    void sortByGrade(Student stud[], int size) {
        for (int i = 0; i < size; i++) {
            int min_index = i;
            for (int j = i + 1; j < size; j++) {
                if (stud[j].grade < stud[min_index].grade) {
                    min_index = j;
                }
            }
        }
        cout << "sorted by name" << endl;
        for (int i = 0; i < size; i++) {
            cout << "id: " << stud[i].id << endl;
            cout << "name of the student: " << stud[i].name << endl;
            cout << "course: " << stud[i].course << endl;
            cout << "grade: " << stud[i].grade << endl;
        }
    }
    void addStudent(Student stud[], int &currentSize) {
        if (currentSize >= maxsize) {
            cout << "max size exceeded" << endl;
            return;
        }
        Student newStudent;
        cout << "Enter name of the student: ";
        cin.ignore();
        getline(cin, newStudent.name);
        cout << "Enter course of the student: ";
        cin.ignore();
        getline(cin, newStudent.course);
        cout << "Enter grade of the student: ";
        cin >> newStudent.grade;
        stud[currentSize] = newStudent;
        currentSize++;
        cout << "Student added successfully" << endl;
    }
    void saveStudentToFile(Student stud[], int currentsize, const string filename) {
        ofstream outfile(filename);

        if (!outfile) {
            cout << "File could not be opened" << endl;
            return;
        }
        outfile << "Name\t\t\tCourse\t\t\tGrade" << endl;
        for (int i = 0; i < currentsize; i++) {
            outfile << stud[i].name << "\t\t\t"
            << stud[i].course << "\t\t\t"
            << stud[i].grade << endl;
        }
        outfile.close();
        cout << "File saved successfully" << endl;
    }
};

int main() {
    Student stud[maxsize];
    ifstream infile("Student.txt");
    int currentSize = 0;
    string line;
    while (getline(infile, line) && currentSize < maxsize) {
        stringstream ss(line);
        string name, course;
        float grade;
        int id;
        ss >> id >> name >> course >> grade ;

        stud[currentSize].name = name;
        stud[currentSize].course = course;
        stud[currentSize].grade = grade;
        stud[currentSize].id = id;
    }
    infile.close();
    int choice;
    do {
        cout << "\t\t\t\t\tMENU\t\t\t\t" << endl;
        cout << "\t\t\t1. show all student\t\t\t\t" << endl;
        cout << "\t\t\t2. search by id\t\t\t\t" << endl;
        cout << "\t\t\t3. sort by name\t\t\t\t" << endl;
        cout << "\t\t\t4. sort by grade\t\t\t\t" << endl;
        cout << "\t\t\t5. add student\t\t\t\t" << endl;
        cout << "\t\t\t6. save file\t\t\t\t" << endl;
        cout << "\t\t\t7. exit\t\t\t\t\t" << endl;
        cout << "enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                stud-> showAllStudents(stud, currentSize);
                break;
            case 2:
                int idnumber;
                cout << "enter id number: ";
                cin >> idnumber;
                stud-> searchById(stud,idnumber ,currentSize);
                break;
            case 3:
                stud -> sortByName(stud, currentSize);
                break;
            case 4:
                stud -> sortByGrade(stud, currentSize);
                break;
            case 5:
                stud -> addStudent(stud, currentSize);
                break;
            case 6:
                stud -> saveStudentToFile(stud, currentSize, "Student.txt");
                break;
            case 7:
                cout << "Exiting..." << endl;
                exit(0);
        }
    }while(choice != 7);
}