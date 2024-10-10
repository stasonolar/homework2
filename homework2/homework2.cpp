#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string surname;
    string group;
    int grades[5];
};

void inputStudent(Student& student) {
    cout << "Введіть прізвище студента: ";
    getline(cin, student.surname);
    cout << "Введіть групу студента: ";
    getline(cin, student.group);
    cout << "Введіть 5 оцінок студента (через пробіл): ";
    for (int i = 0; i < 5; ++i) {
        cin >> student.grades[i];
    }
    cin.ignore(); // Очистка буферу
}

void displayStudent(const Student& student) {
    cout << "Прізвище: " << student.surname << ", Група: " << student.group << ", Оцінки: ";
    for (int i = 0; i < 5; ++i) {
        cout << student.grades[i] << ' ';
    }
    cout << endl;
}

// Функція для додавання студента до масиву
void addStudent(vector<Student>& students) {
    Student newStudent;
    inputStudent(newStudent);
    students.push_back(newStudent);
    cout << "Студента додано успішно!\n";
}

// Функція для видалення студента за прізвищем
void removeStudent(vector<Student>& students) {
    string surname;
    cout << "Введіть прізвище студента для видалення: ";
    getline(cin, surname);
    auto it = remove_if(students.begin(), students.end(), [&](const Student& s) {
        return s.surname == surname;
        });
    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Студента видалено успішно!\n";
    }
    else {
        cout << "Студента з таким прізвищем не знайдено.\n";
    }
}

// Функція для виведення списку відмінників
void displayHonorStudents(const vector<Student>& students) {
    cout << "\n--- Список відмінників ---\n";
    for (const auto& student : students) {
        int excellent = 0;
        for (int grade : student.grades) {
            if (grade >= 4) excellent++;
        }
        if (excellent >= 4) { // >75% з 5 оцінок – 4 і 5
            displayStudent(student);
        }
    }
}

// Функція для виведення списку двієчників
void displayPoorStudents(const vector<Student>& students) {
    cout << "\n--- Список двієчників ---\n";
    for (const auto& student : students) {
        int poor = 0;
        for (int grade : student.grades) {
            if (grade <= 3) poor++;
        }
        if (poor >= 3) { // >50% з 5 оцінок – 3 і 2
            displayStudent(student);
        }
    }
}

void menu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Додати студента\n";
    cout << "2. Видалити студента\n";
    cout << "3. Показати всіх студентів\n";
    cout << "4. Показати відмінників\n";
    cout << "5. Показати двієчників\n";
    cout << "6. Вийти\n";
    cout << "Оберіть опцію: ";
}

int main()
{
    // Встановлення кодування для коректного відображення українських символів
    system("chcp 1251>null");
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    vector<Student> students;
    int choice;

    while (true) {
        menu();
        cin >> choice;
        cin.ignore(); // Очистка буферу

        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            removeStudent(students);
            break;
        case 3:
            cout << "\n--- Список всіх студентів ---\n";
            for (const auto& student : students) {
                displayStudent(student);
            }
            break;
        case 4:
            displayHonorStudents(students);
            break;
        case 5:
            displayPoorStudents(students);
            break;
        case 6:
            cout << "Вихід з програми.\n";
            return 0;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}
