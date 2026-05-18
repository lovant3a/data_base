#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <algorithm>
#include <fstream>
#include "record.h"
using namespace std;

class Database {
private:
    vector<Record> data;

public:
    Database() {}

    Record& operator[](int index) {
        return data[index];
    }

    const Record& operator[](int index) const {
        return data[index];
    }

    // вставка в конец
    void insert(const Record& rec) {
        data.push_back(rec);
        cout << "запись добавлена: " << rec.name << endl;
    }

    // удаление по индексу
    bool remove(int index) {
        if (index < 0 || index >= data.size()) {
            cout << "неверный индекс" << endl;
            return false;
        }
        data.erase(data.begin() + index);
        cout << "запись удалена" << endl;
        return true;
    }

    // сортировка по имени 
    void sort_name(bool ascending = true) {
        if (ascending) {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.name < b.name;
                });
        }
        else {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.name > b.name;
                });
        }
        cout << "отсортировано по имени" << endl;
    }

    // сортировка по id
    void sort_id(bool ascending = true) {
        if (ascending) {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.id < b.id;
                });
        }
        else {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.id > b.id;
                });
        }
        cout << "отсортировано по id" << endl;
    }

    // сортировка по value
    void sort_value(bool ascending = true) {
        if (ascending) {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.value < b.value;
                });
        }
        else {
            sort(data.begin(), data.end(), [](const Record& a, const Record& b) {
                return a.value > b.value;
                });
        }
        cout << "отсортировано по значению выполнена" << endl;
    }

    void print_table() const {
        if (data.empty()) {
            cout << "база пуста" << endl;
            return;
        }

        cout << "| №  | имя              | id  | значение   | количество|" << endl;

        for (size_t i = 0; i < data.size(); i++) {
            printf("| %2d | %-16s | %3d | %10.2f | %8d |\n", (int)i, data[i].name.c_str(), data[i].id, data[i].value, data[i].quantity);
        }
        cout << endl;
        cout << "всего записей: " << data.size() << endl << endl;
    }

    // сохранение в файл
    bool save_to_file(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "не удалось открыть файл для записи" << endl;
            return false;
        }

        file << data.size() << endl;
        for (const auto& rec : data) {
            file << rec.name << endl;
            file << rec.id << endl;
            file << rec.value << endl;
            file << rec.quantity << endl;
        }

        file.close();
        cout << "данные сохранены в файл: " << filename << endl;
        return true;
    }

    // чтение из файла
    bool load_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "не удалось открыть файл для чтения" << endl;
            return false;
        }

        data.clear();
        int count;
        file >> count;

        for (int i = 0; i < count; i++) {
            Record rec;
            file >> rec.name;
            file >> rec.id;
            file >> rec.value;
            file >> rec.quantity;
            data.push_back(rec);
        }

        file.close();
        cout << "данные загружены из файла: " << filename << endl;
        cout << "записей загружено: " << data.size() << endl;
        return true;
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};

#endif