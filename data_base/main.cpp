#include <iostream>
#include <string>
#include <limits>
#include <locale.h>
#include "database.h"

using namespace std;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Database db;
    int choice = 0;
    string filename;

    setlocale(LC_ALL, "Russian.UTF8");

    cout << "=== БАЗА ДАННЫХ ТОВАРОВ ===" << endl;

    while (true) {
        cout << "\nменю:\n";
        cout << "  1. добавить запись\n";
        cout << "  2. удалить запись по индексу\n";
        cout << "  3. показать всю таблицу\n";
        cout << "  4. сортировать по имени (А-Я)\n";
        cout << "  5. сортировать по имени (Я-А)\n";
        cout << "  6. сортировать по ID (возр.)\n";
        cout << "  7. сортировать по ID (убыв.)\n";
        cout << "  8. сортировать по цене (дешёвые сначала)\n";
        cout << "  9. сортировать по цене (дорогие сначала)\n";
        cout << " 10. сохранить в файл\n";
        cout << " 11. загрузить из файла\n";
        cout << "  0. выход\n";
        cout << "выберите команду: ";

        if (!(cin >> choice)) {
            clearCin();
            cout << "ошибка: введите число от 0 до 11.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1: {
                Record rec;
                cout << "введите название товара: ";
                clearCin();
                getline(cin, rec.name);
                
                cout << "введите ID (число): ";
                if (!(cin >> rec.id)) { clearCin(); throw runtime_error("ошибка ввода ID"); }
                
                cout << "введите цену: ";
                if (!(cin >> rec.value)) { clearCin(); throw runtime_error("ошибка ввода цены"); }
                
                cout << "введите количество: ";
                if (!(cin >> rec.quantity)) { clearCin(); throw runtime_error("ошибка ввода количества"); }
                
                db.insert(rec);
                break;
            }
            case 2: {
                if (db.empty()) {
                    cout << "база пуста, удалять нечего" << endl;
                    break;
                }
                cout << "введите индекс записи для удаления (0.." << db.size() - 1 << "): ";
                size_t idx;
                if (!(cin >> idx) || idx >= db.size()) {
                    clearCin();
                    cout << "неверный индекс" << endl;
                }
                else {
                    db.remove(idx);
                }
                break;
            }
            case 3: {
                db.print_table();
                break;
            }
            case 4: db.sort_name(true); break;
            case 5: db.sort_name(false); break;
            case 6: db.sort_id(true); break;
            case 7: db.sort_id(false); break;
            case 8: db.sort_value(true); break;
            case 9: db.sort_value(false); break;
            case 10: {
                cout << "введите имя файла для сохранения: ";
                clearCin();
                getline(cin, filename);
                db.save_to_file(filename);
                break;
            }
            case 11: {
                cout << "введите имя файла для загрузки: ";
                clearCin();
                getline(cin, filename);
                db.load_from_file(filename);
                break;
            }
            case 0: {
                cout << "завершение работы. до свидания!" << endl;
                return 0;
            }
            default:
                cout << "неизвестная команда" << endl;
            }
        }
        catch (const exception& e) {
            cerr << "\nОШИБКА: " << e.what() << "\n";
            clearCin();
        }
    }

    return 0;
}
