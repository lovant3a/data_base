#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "record.h"

using namespace std;

class Database {
private:
    vector<Record> data;

public:
    Database();
    
    // оператор доступа
    Record& operator[](size_t index);
    const Record& operator[](size_t index) const;
    
    // основные операции
    void insert(const Record& rec);
    bool remove(size_t index);
    
    // сортировки
    void sort_name(bool ascending = true);
    void sort_id(bool ascending = true);
    void sort_value(bool ascending = true);
    
    // вывод и файлы
    void print_table() const;
    bool save_to_file(const string& filename) const;
    bool load_from_file(const string& filename);
    
    // утилиты
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};

#endif
