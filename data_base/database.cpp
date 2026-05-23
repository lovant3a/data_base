#include "database.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Database::Database() {}

Record& Database::operator[](size_t index) {
    return data[index];
}

const Record& Database::operator[](size_t index) const {
    return data[index];
}

void Database::insert(const Record& rec) {
    data.push_back(rec);
    cout << "запись добавлена: " << rec.name << endl;
}

bool Database::remove(size_t index) {
    if (index >= data.size()) {
        cout << "неверный индекс" << endl;
        return false;
    }
    data.erase(data.begin() + index);
    cout << "запись удалена" << endl;
    return true;
}

// вспомогательные функции-компараторы для sort
static bool cmp_name_asc(const Record& a, const Record& b) { return a.name < b.name; }
static bool cmp_name_desc(const Record& a, const Record& b) { return a.name > b.name; }
static bool cmp_id_asc(const Record& a, const Record& b) { return a.id < b.id; }
static bool cmp_id_desc(const Record& a, const Record& b) { return a.id > b.id; }
static bool cmp_value_asc(const Record& a, const Record& b) { return a.value < b.value; }
static bool cmp_value_desc(const Record& a, const Record& b) { return a.value > b.value; }

void Database::sort_name(bool ascending) {
    if (ascending)
        sort(data.begin(), data.end(), cmp_name_asc);
    else
        sort(data.begin(), data.end(), cmp_name_desc);
    cout << "сортировка по имени выполнена" << endl;
}

void Database::sort_id(bool ascending) {
    if (ascending)
        sort(data.begin(), data.end(), cmp_id_asc);
    else
        sort(data.begin(), data.end(), cmp_id_desc);
    cout << "сортировка по ID выполнена" << endl;
}

void Database::sort_value(bool ascending) {
    if (ascending)
        sort(data.begin(), data.end(), cmp_value_asc);
    else
        sort(data.begin(), data.end(), cmp_value_desc);
    cout << "сортировка по цене выполнена" << endl;
}

void Database::print_table() const {
    if (empty()) {
        cout << "база пуста" << endl;
        return;
    }
    cout << "\n=== ТАБЛИЦА ===" << endl;
    cout << "NAME | ID | VALUE | QUANT" << endl;
    cout << "---------------------------" << endl;
    for (const auto& rec : data) {
        cout << rec.name << " | " << rec.id << " | " << rec.value << " | " << rec.quantity << endl;
    }
    cout << "---------------------------" << endl;
    cout << "всего записей: " << size() << "\n" << endl;
}

bool Database::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ошибка: не удалось открыть файл для записи" << endl;
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
    cout << "данные сохранены в " << filename << endl;
    return true;
}

bool Database::load_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ошибка: не удалось открыть файл для чтения" << endl;
        return false;
    }
    
    size_t count;
    file >> count;
    file.ignore(); 
    
    for (size_t i = 0; i < count; ++i) {
        Record rec;
        getline(file, rec.name);      
        file >> rec.id;
        file >> rec.value;
        file >> rec.quantity;
        file.ignore();               
        data.push_back(rec);
    }
    
    file.close();
    cout << "загружено записей: " << count << endl;
    return true;
}
