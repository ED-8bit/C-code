#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <cstring>

using namespace std;
int slt = 700;
struct Node {
    int data;
    Node* next;
};
void init_list(Node*& head)
{
    head = nullptr;
}
void add_back(Node*& head, int value)
{
    Node* temp = new Node;
    Node* temp1;
    temp->data = value;
    temp->next = nullptr;
    if (head == nullptr) {
        head = temp;  return;
    }
    temp1 = head;
    while (temp1->next != nullptr) temp1 = temp1->next;
    temp1->next = temp;
}
int add_i(Node*& head, int index, int value)
{
    int i;
    Node* temp = new Node;
    Node* temp1;
    temp->data = value;
    temp->next = nullptr;
    if (index < 0) { cout << "Неверный индекс\n"; return 0; }
    temp1 = head;
    for (i = 0; temp1 != nullptr; i++)
    {
        if (i == index) break;
        temp1 = temp1->next;

    }
    if (temp1 == nullptr) { cout << "Неверный индекс\n"; return 0; }
    temp->next = temp1->next;
    temp1->next = temp;
    return 1;
}
void add_front(Node*& head, int value)
{
    Node* temp = new Node;
    temp->data = value;
    temp->next = head;
    head = temp;
}
void remove_value(Node*& head, int value)
{
    Node* cur;
    Node* prev;
    cur = head;
    prev = head;
    if (head == nullptr) return;
    if (head->data == value) { head = head->next; return; }
    cur = cur->next;
    while (cur != nullptr)
    {
        if (cur->data == value) {
            prev->next = cur->next;
            Node* temp = cur;
            delete(temp);
            cur = prev;
        }
        else {
            prev = cur;
        }
        cur = cur->next;
    }
}
void reverselist(Node*& head)
{
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr)
    {
        next = current->next;  // сохраняем следующий узел
        current->next = prev;  // меняем указатель на предыдущий
        prev = current;        // сдвигаем prev
        current = next;        // переходим к следующему
    }
    head = prev;
}
void remove_duplicates(Node*& head)
{
    if (head == nullptr) return;

    Node* current = head;
    Node* temp;
    Node* runner;

    while (current != nullptr)
    {
        runner = current;
        while (runner->next != nullptr)
        {
            if (runner->next->data == current->data)
            {
                temp = runner->next;
                runner->next = temp->next;
                delete temp;
            }
            else
            {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}
void find_min_max(Node* head, int& min_val, int& max_val)
{
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }

    min_val = head->data;
    max_val = head->data;

    Node* temp = head->next;
    while (temp != nullptr)
    {
        if (temp->data < min_val) min_val = temp->data;
        if (temp->data > max_val) max_val = temp->data;
        temp = temp->next;
    }
}
int count_unique_elements(Node* head)
{
    if (head == nullptr) return 0;

    int unique_count = 0;
    Node* current = head;
    Node* runner;
    int count;

    while (current != nullptr)
    {
        count = 0;
        runner = head;

        while (runner != nullptr)
        {
            if (runner->data == current->data)
                count++;
            runner = runner->next;
        }

        if (count == 1)
            unique_count++;

        current = current->next;
    }

    return unique_count;
}
void CreateList(Node*& head)
{
    char answer[40];
    int value;
    cout << "Вы хотите ввести элемент списка (Да/Нет)"; cin >> answer;
    while (!strcmp(answer, "Да") || !strcmp(answer, "ДА") || !strcmp(answer, "да") || !strcmp(answer, "дА"))
    {
        cout << "Введите элемент"; cin >> value;
        add_back(head, value);
        system("cls");
        cout << "Вы хотите ввести элемент списка (Да/Нет)"; cin >> answer;
    }
}
void DestroyList(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp;
        temp = head;
        head = head->next;
        delete(temp);
    }
}
void PrintList(Node*& head)
{
    Node* temp;
    temp = head;
    cout << "Список:";
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

struct Book {
    char title[100];
    char author[100];
    int udk;
    Book* next;
};

void init_book_list(Book*& head)
{
    head = nullptr;
}
bool exists_book_by_udk(Book* head, int udk) {
    Book* cur = head;
    while (cur != nullptr) {
        if (cur->udk == udk)
            return true;
        cur = cur->next;
    }
    return false;
}
void add_book(Book*& head, const char* title, const char* author, int udk) {
    
    //if (exists_book_by_udk(head, udk)) {
    //    cout << "Ошибка: книга с УДК " << udk << " уже существует!\n";
    //    return;
    //}

    Book* temp = new Book;
    
    int i = 0;
    while (title[i] != '\0' && i < 99) {
        temp->title[i] = title[i];
        i++;
    }
    temp->title[i] = '\0';

    i = 0;
    while (author[i] != '\0' && i < 99) {
        temp->author[i] = author[i];
        i++;
    }
    temp->author[i] = '\0';

    temp->udk = udk;
    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        return;
    }
    Book* temp1 = head;
    while (temp1->next != nullptr)
        temp1 = temp1->next;
    temp1->next = temp;
}
void remove_book_by_udk(Book*& head, int udk)
{
    Book* cur;
    Book* prev;
    cur = head;
    prev = head;

    if (head == nullptr) return;

    if (head->udk == udk) {
        head = head->next;
        delete cur;
        return;
    }

    cur = cur->next;
    while (cur != nullptr)
    {
        if (cur->udk == udk) {
            prev->next = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Книга с УДК " << udk << " не найдена\n";
}
void sort_books_by_udk(Book*& head) {
    if (!head || !head->next) return;

    bool swapped;
    Book** pp;

    do {
        swapped = false;
        pp = &head;

        while ((*pp) && (*pp)->next) {
            Book* a = *pp;
            Book* b = a->next;
            if (a->udk > b->udk) {
                a->next = b->next;
                b->next = a;
                *pp = b;
                swapped = true;
            }
            pp = &(*pp)->next;
        }
    } while (swapped);
}
void print_books(Book* head)
{
    Book* temp = head;
    while (temp != nullptr)
    {
        cout << "Название: " << temp->title << ", Автор: " << temp->author
            << ", УДК: " << temp->udk << endl;
        temp = temp->next;
    }
}
void library_demo()
{
    Book* library = nullptr;
    init_book_list(library);

    int choice;
    char title[100], author[100];
    int udk;

    do {
        system("cls");
        cout << "\n========== БИБЛИОТЕКА ==========\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Удалить книгу по УДК\n";
        cout << "3. Сортировать книги по УДК\n";
        cout << "4. Показать все книги\n";
        cout << "0. Вернуться в главное меню\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Введите название книги: ";
            cin.getline(title, 100);
            cout << "Введите автора: ";
            cin.getline(author, 100);
            cout << "Введите УДК: ";
            cin >> udk;
            add_book(library, title, author, udk);
            cout << "Книга успешно добавлена!\n";
            Sleep(slt);
            break;
        case 2:
            cout << "Введите УДК книги для удаления: ";
            cin >> udk;
            remove_book_by_udk(library, udk);
            Sleep(slt);
            break;
        case 3:
            sort_books_by_udk(library);
            cout << "Книги отсортированы по УДК!\n";
            Sleep(slt);
            break;
        case 4:
            if (library == nullptr) {
                cout << "Библиотека пуста.\n";
                Sleep(slt);
            }
            else {
                cout << "\nСписок книг в библиотеке:\n";
                print_books(library);
                system("pause");
            }
            break;
        }
    } while (choice != 0);
}

struct Student {
    char name[100];
    double average_score;
    Student* next;
};

void init_student_list(Student*& head)
{
    head = nullptr;
}
void add_student(Student*& head, const char* name, double score)
{
    Student* temp = new Student;
    Student* temp1;

    int i = 0;
    while (name[i] != '\0' && i < 99) {
        temp->name[i] = name[i];
        i++;
    }
    temp->name[i] = '\0';

    temp->average_score = score;
    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        return;
    }
    temp1 = head;
    while (temp1->next != nullptr) temp1 = temp1->next;
    temp1->next = temp;
}
void sort_students_by_score(Student*& head) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    Student* ptr = nullptr;

    do {
        swapped = false;
        Student* current = head;

        while (current->next != ptr) {
            if (current->average_score < current->next->average_score) {
                // Обмен содержимым (без изменения next)
                char tmp_name[100];
                double tmp_score;

                strcpy_s(tmp_name, current->name);
                tmp_score = current->average_score;

                strcpy_s(current->name, current->next->name);
                current->average_score = current->next->average_score;

                strcpy_s(current->next->name, tmp_name);
                current->next->average_score = tmp_score;

                swapped = true;
            }
            current = current->next;
        }
        ptr = current;
    } while (swapped);
}
void read_students_from_file(const char* filename, Student*& head)
{
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    char name[100];
    double score;


    while (file >> name >> score)
    {
        add_student(head, name, score);
    }

    file.close();
}
void write_students_to_file(const char* filename, Student* head)
{
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Не удалось создать файл " << filename << endl;
        return;
    }

    Student* temp = head;
    while (temp != nullptr)
    {
        file << temp->name << " " << temp->average_score << endl;
        temp = temp->next;
    }

    file.close();
}
void destroy_student_list(Student*& head)
{
    while (head != nullptr)
    {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}
void process_students(const char* input_file, const char* output_file)
{
    Student* head = nullptr;
    init_student_list(head);

    read_students_from_file(input_file, head);

    if (head == nullptr) {
        cout << "Нет данных для обработки!\n";
        return;
    }

    sort_students_by_score(head);
    write_students_to_file(output_file, head);

    cout << "Студенты отсортированы и сохранены в " << output_file << endl;

    // Очищаем память
    destroy_student_list(head);
}
void print_students(Student* head)
{
    if (head == nullptr) {
        cout << "Список студентов пуст.\n";
        return;
    }

    Student* temp = head;
    int count = 1;
    while (temp != nullptr)
    {
        cout << count++ << ". Имя: " << temp->name << ", Средний балл: " << temp->average_score << endl;
        temp = temp->next;
    }
}
void students_demo()
{
    cout << "Текущая директория: ";
    system("cd");
    system("pause");
    const char* input_file = "filein.txt";
    const char* output_file = "fileout.txt";

    ofstream test_file(input_file);
    if (test_file.is_open()) {
        test_file << "Тозлиян 85.5\n";
        test_file << "Петров 92.3\n";
        test_file << "Логинов 78.9\n";
        test_file << "Христокян 95.0\n";
        test_file << "Сафонов 88.7\n";
        test_file << "Раганян 91.2\n";
        test_file.close();
        cout << "Создан тестовый файл " << input_file << " с данными студентов\n";
    }
    else {
        cout << "Ошибка: не удалось создать файл " << input_file << endl;
        system("pause");
        return;
    }

    cout << "\n========== РАБОТА СО СТУДЕНТАМИ ==========\n";
    cout << "Чтение из файла: " << input_file << endl;
    cout << "Запись в файл: " << output_file << endl;

    process_students(input_file, output_file);

    
    Student* students = nullptr;
    init_student_list(students);
    read_students_from_file(output_file, students);

    if (students != nullptr) {
        cout << "\nОтсортированный список студентов (по убыванию балла):\n";
        print_students(students);
        destroy_student_list(students);
    }
    else {
        cout << "Не удалось прочитать отсортированный список.\n";
    }

    system("pause");
}
void list_demo()
{
    Node* myList = nullptr;
    init_list(myList);

    int choice, min_val, max_val;

    do {
        system("cls");
        cout << "\n========== РАБОТА СО СПИСКОМ ==========\n";
        cout << "1. Создать список\n";
        cout << "2. Показать список\n";
        cout << "3. Перевернуть список (задание 1)\n";
        cout << "4. Удалить дубликаты из списка (задание 4)\n";
        cout << "5. Найти наибольший и наименьший элемент (задание 5)\n";
        cout << "6. Подсчитать количество уникальных элементов (задание 6)\n";
        cout << "0. Вернуться в главное меню\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateList(myList);
            break;
        case 2:
            if (myList == nullptr) {
                cout << "Список пуст. Сначала создайте список.\n";
                Sleep(slt);
            }
            else {
                PrintList(myList);
                system("pause");
            }
            break;
        case 3:
            if (myList == nullptr) {
                cout << "Список пуст. Сначала создайте список.\n";
                Sleep(slt);
            }
            else {
                reverselist(myList);
                cout << "Список успешно перевернут!\n";
                Sleep(slt);
                PrintList(myList);
                system("pause");
            }
            break;
        case 4:
            if (myList == nullptr) {
                cout << "Список пуст. Сначала создайте список.\n";
                Sleep(slt);
            }
            else {
                remove_duplicates(myList);
                cout << "Дубликаты успешно удалены!\n";
                Sleep(slt);
                PrintList(myList);
                system("pause");
            }
            break;
        case 5:
            if (myList == nullptr) {
                cout << "Список пуст. Сначала создайте список.\n";
                Sleep(slt);
            }
            else {
                find_min_max(myList, min_val, max_val);
                cout << "Наименьший элемент списка: " << min_val << endl;
                cout << "Наибольший элемент списка: " << max_val << endl;
                system("pause");
            }
            break;
        case 6:
            if (myList == nullptr) {
                cout << "Список пуст. Сначала создайте список.\n";
                Sleep(slt);
            }
            else {
                int unique = count_unique_elements(myList);
                cout << "Количество уникальных элементов: " << unique << endl;
                system("pause");
            }
            break;
        }
    } while (choice != 0);

    DestroyList(myList);
}

int main()
{
    system("chcp 1251");
    int main_choice;
    do {
        system("cls");
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        cout << "1. Работа со списком (задания 1, 4, 5, 6)\n";
        cout << "2. Библиотека (задание 2)\n";
        cout << "3. Работа со студентами (задание 3)\n";
        cout << "0. Выход из программы\n";
        cout << "Выберите действие: ";
        cin >> main_choice;

        switch (main_choice) {
        case 1:
            system("cls");
            list_demo();
            break;
        case 2:
            system("cls");
            library_demo();
            break;
        case 3:
            system("cls");
            students_demo();
            break;
        case 0:
            cout << "\nДо свидания!\n";
            break;
        default:
            cout << "выберите пункт от 0 до 3.\n";
        }
    } while (main_choice != 0);

    return 0;
}