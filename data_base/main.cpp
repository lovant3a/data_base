#include <iostream>
#include <string>
#include <limits>
#include <locale.h>
#include "database.h"

using namespace std;

// очистка буфера ввода
void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// показать меню
void show_menu() {
    cout << "1. показать все записи" << endl;
    cout << "2. добавить запись" << endl;
    cout << "3. удалить запись" << endl;
    cout << "4. сортировать по имени" << endl;
    cout << "5. сортировать по id" << endl;
    cout << "6. сортировать по значению" << endl;
    cout << "7. сохранить в файл" << endl;
    cout << "8. загрузить из файла" << endl;
    cout << "0. выход" << endl;
    cout << "введите номер команды";
}

// добавить запись
void add_record(Database& db) {
    string name;
    int id, qty;
    double value;

    cout << "введите имя: ";
    cin.ignore();
    getline(cin, name);

    cout << "введите id: ";
    while (!(cin >> id)) {
        cout << "введите целое число: ";
        clear_input();
    }

    cout << "введите значение (вещественное): ";
    while (!(cin >> value)) {
        cout << "введите число: ";
        clear_input();
    }

    cout << "введите количество (целое): ";
    while (!(cin >> qty)) {
        cout << "введите целое число: ";
        clear_input();
    }

    db.insert(Record(name, id, value, qty));
}

// удалить запись
void remove_record(Database& db) {
    if (db.empty()) {
        cout << "база пуста" << endl;
        return;
    }

    int index;
    cout << "введите номер записи для удаления (0-" << db.size() - 1 << "): ";
    cin >> index;

    db.remove(index);
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Russian.UTF8");

    Database db;
    string filename = "database.txt";

    // обработка параметров командной строки
    if (argc > 1) {
        filename = argv[1];
        cout << "файл базы данных: " << filename << endl;
        db.load_from_file(filename);
    }

    int choice;

    while (true) {
        show_menu();

        if (!(cin >> choice)) {
            clear_input();
            cout << "ошибка ввода" << endl;
            continue;
        }

        switch (choice) {
        case 0:
            cout << "выход из программы..." << endl;
            return 0;

        case 1:
            db.print_table();
            break;

        case 2:
            add_record(db);
            break;

        case 3:
            remove_record(db);
            break;

        case 4: {
            if (db.empty()) { cout << "база пуста" << endl; break; }
            cout << "направление (1 - возрастание, 2 - убывание): ";
            int dir; cin >> dir;
            db.sort_name(dir == 1);
            break;
        }
        case 5: {
            if (db.empty()) { cout << "база пуста" << endl; break; }
            cout << "направление (1 - возрастание, 2 - убывание): ";
            int dir; cin >> dir;
            db.sort_id(dir == 1);
            break;
        }
        case 6: {
            if (db.empty()) { cout << "база пуста" << endl; break; }
            cout << "направление (1 - возрастание, 2 - убывание): ";
            int dir; cin >> dir;
            db.sort_value(dir == 1);
            break;
        }

        case 7: {
            string fname;
            cout << "имя файла (Enter - " << filename << "): ";
            cin.ignore();
            getline(cin, fname);
            if (!fname.empty()) filename = fname;
            db.save_to_file(filename);
            break;
        }

        case 8: {
            string fname;
            cout << "имя файла: ";
            cin.ignore();
            getline(cin, fname);
            if (!fname.empty()) {
                db.load_from_file(fname);
                filename = fname;
            }
            break;
        }

        default:
            cout << "неверный выбор" << endl;
        }
    }

    return 0;
}