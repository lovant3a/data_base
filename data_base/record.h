#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
using namespace std;

struct Record {
    string name;        
    int id;             
    double value;      
    int quantity;       

    Record() : id(0), value(0.0), quantity(0) {}
    Record(const string& n, int i, double v, int q)
        : name(n), id(i), value(v), quantity(q) {}

    void print() const {
        cout << name << " | id: " << id << " | value: " << value << " | quant: " << quantity << endl;
    }
};

#endif