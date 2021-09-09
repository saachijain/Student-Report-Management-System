#include <bits/stdc++.h>

using namespace std;

class Student
{
public:
    int studentID, school_class;
    string name, password;
    char gender;
    unordered_map<int, string> subject_name;
    unordered_map<int, int> subject_marks;
    unordered_map<int, char> subject_grade;

    Student()
    {
        studentID = 0;
        school_class = INT_MIN;
        name = "";
        password = "";
        gender = 'A';
        subject_name.clear();
        subject_marks.clear();
        subject_grade.clear();
    }

    Student(int studentID)
    {
        this->studentID = studentID;
    }

    void addStudent()
    {
        cout << "Please enter your name: ";
        string name;
        cin >> name;
        cout << "\n";

        cout << "Please enter the class you are studying in currently (1-12): ";
        int school_class;
        cin >> school_class;
        cout << "\n";

        if (school_class >= 1 && school_class <= 12)
        {
            cout << "Invalid input. Please try again!\n";
            return;
        }

        cout << "Please enter your gender (M/F): ";
        char gender;
        cin >> gender;
        cout << "\n";

        if (gender != 'M' && gender != 'F')
        {
            cout << "Invalid input. Please try again!\n";
            return;
        }

        cout << "Please enter your new 6 character password: ";
        string pwd1;
        cin >> pwd1;
        cout << "\n";

        cout << "Please re-enter your new 6 character password: ";
        string pwd2;
        cin >> pwd2;
        cout << "\n";

        if ((int)pwd1.size() != 6 || (int)pwd2.size() != 6 || pwd1 != pwd2)
        {
            cout << "Invalid input. Please try again!\n";
            return;
        }

        this->school_class = school_class;
        password = pwd2;
        this->gender = gender;
        this->name = name;
    }

    void displayStudent(string pwd)
    {
        if (pwd.size() != 6)
        {
            cout << "Invalid input. Please try again!\n";
            return;
        }

        if (pwd != password)
        {
            cout << "Incorrect password entered. Please try again!\n";
            return;
        }

        cout << "Your Grade Report\n";
        for (auto i : subject_name)
        {
            cout << i.first << "\t" << i.second << "\t" << subject_marks[i.first] << "\t";
            cout << subject_grade[i.first] << "\n";
        }
    }
};

class Teacher
{
public:
    int teacherID;
    string password;

    Teacher()
    {
        teacherID = 0;
        password = "";
    }

    Teacher(int ID)
    {
        teacherID = ID;
    }

    void addTeacher()
    {
        cout << "Please enter your new 6 character password: ";
        string pwd1;
        cin >> pwd1;
        cout << "\n";

        cout << "Please re-enter your new 6 character password: ";
        string pwd2;
        cin >> pwd2;
        cout << "\n";

        if ((int)pwd1.size() != 6 || (int)pwd2.size() != 6 || pwd1 != pwd2)
        {
            cout << "Invalid input. Please try again!\n";
            return;
        }
        password = pwd2;
    }

    bool check_password(string pwd)
    {
        if (pwd == password)
            return true;
        else
            return false;
    }

    void displayStudent(Student &s)
    {
        cout << s.name << "'s Grade Report\n";
        for (auto i : s.subject_name)
        {
            cout << i.first << "\t" << i.second << "\t" << s.subject_marks[i.first] << "\t";
            cout << s.subject_grade[i.first] << "\n";
        }
    }

    void generateGrades(Student &s)
    {
        for (auto i : s.subject_marks)
        {
            if (i.second >= 90)
                s.subject_grade[i.first] = 'A';
            else if (i.second >= 80)
                s.subject_grade[i.first] = 'B';
            else if (i.second >= 70)
                s.subject_grade[i.first] = 'C';
            else if (i.second >= 60)
                s.subject_grade[i.first] = 'D';
            else if (i.second >= 50)
                s.subject_grade[i.first] = 'E';
            else
                s.subject_grade[i.first] = 'F';
        }
    }

    void updateMarks(Student &s)
    {
        cout << "Enter number of subjects to be modified: ";
        int n;
        cin >> n;
        cout << "\n";

        string name = "";
        int marks = 0, ID = 0;

        for (int i = 0; i < n; ++i)
        {
            cout << "Enter subject ID: ";
            cin >> ID;
            cout << "\n";

            cout << "Enter subject name: ";
            cin >> name;
            cout << "\n";

            cout << "Enter marks: ";
            cin >> marks;
            cout << "\n";

            s.subject_marks[ID] = marks;
            s.subject_name[ID] = name;
        }
    }
};

unordered_map<int, Student> student_data;
unordered_map<int, Teacher> teacher_data;

int main()
{
    bool check = true;
    do
    {
        cout << "Hello! Welcome to the Student Report Management System\n";
        cout << "What entity do you want to login as?\n1. Student\n2. Teacher\n";
        cout << "Enter the corresponding option number (1/2)\n";

        int entity;
        cin >> entity;
        switch (entity)
        {
        case 1:
        {
            cout << "Please enter your 6 digit Student ID: ";
            string student_ID;
            cin >> student_ID;
            cout << "\n";

            if ((int)student_ID.size() != 6)
                cout << "Invalid input. Please try again!\n";

            int ID = stoi(student_ID);
            if (student_data.find(ID) == student_data.end())
            {
                cout << "Student does not exist. Do you want to make a new account?\n1. Yes\n2. No\n";
                cout << "Enter the corresponding option number (1/2)\n";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    Student s = Student(ID);
                    s.addStudent();
                    student_data[ID] = s;
                    break;
                }
                case 2:
                {
                    cout << "Logging out. Have a good day!\n";
                    break;
                }
                default:
                {
                    cout << "Wrong input. Please try again!\n";
                    break;
                }
                }
            }
            else
            {
                cout << "Please enter your 6 character password: ";
                string pwd;
                cin >> pwd;
                cout << "\n";
                Student s = student_data[ID];
                s.displayStudent(pwd);
                break;
            }
            break;
        }
        case 2:
        {
            cout << "Please enter your 6 digit Teacher ID: ";
            string teacher_ID;
            cin >> teacher_ID;
            cout << "\n";

            if ((int)teacher_ID.size() != 6)
                cout << "Invalid input. Please try again!\n";

            int ID = stoi(teacher_ID);
            if (teacher_data.find(ID) == teacher_data.end())
            {
                cout << "Teacher does not exist. Do you want to make a new account?\n1. Yes\n2. No\n";
                cout << "Enter the corresponding option number (1/2)\n";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    Teacher t = Teacher(ID);
                    t.addTeacher();
                    teacher_data[ID] = t;
                    break;
                }
                case 2:
                {
                    cout << "Logging out. Have a good day!\n";
                    break;
                }
                default:
                {
                    cout << "Wrong input. Please try again!\n";
                    break;
                }
                }
            }
            else
            {
                Teacher t = Teacher(ID);
                cout << "Please enter your 6 character password: ";
                string pwd;
                cin >> pwd;
                cout << "\n";

                if (!t.check_password(pwd))
                {
                    cout << "Wrong password. Please try again!\n";
                    break;
                }
                else
                {
                    cout << "What do you want to do today?\n1. Generate and display student's grade\n";
                    cout << "2. Update student's marks\nEnter corresponding number (1/2)\n";

                    int choice = 0;
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                    {
                        cout << "Enter Student ID: ";
                        int ID;
                        cin >> ID;
                        Student s = student_data[ID];
                        t.generateGrades(s);
                        t.displayStudent(s);
                        break;
                    }
                    case 2:
                    {
                        cout << "Enter Student ID: ";
                        int ID;
                        cin >> ID;
                        Student s = student_data[ID];
                        t.updateMarks(s);
                        break;
                    }
                    default:
                    {
                        cout << "Wrong input. Please try again!\n";
                        break;
                    }
                    }
                }
            }
            break;
        }
        default:
        {
            cout << "Wrong input. Please try again!\n";
            break;
        }
        }
    } while (check);

    return 0;
}