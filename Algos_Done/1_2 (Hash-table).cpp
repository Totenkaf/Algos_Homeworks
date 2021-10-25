/** Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна поддерживать операции
добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба g(k, i)=g(k, i-1) + i (mod m).
m - степень двойки. 1_2. Для разрешения коллизий используйте двойное хеширование. **/

#include <iostream>
#include <string>
#include <vector>
//#include <fstream>

template <typename T, typename Hasher = std::hash<T>, typename Hasher2 = std::hash<T>>
class HashTable {
public:
    HashTable(T noneElem, T deletedElem, size_t initSize = 8, float expandFactor = 0.75, unsigned int prime = 7):
        tableSize(0), expandFactor(expandFactor), prime(prime), noneElem(noneElem), deletedElem(deletedElem) {
            table.resize(initSize);
            for (size_t i = 0; i < table.size(); i++)
                table[i] = noneElem;
    }
    void print() {
        for (auto i: table)
            std::cout << i << ' ';
        std::cout << ": " << table.size() << std::endl;
    }
    bool add(const T &value) {
        if (select(value))
            return false;
        T node;
        size_t lastId;
        for (int i = 0; ; i++) {
            node = table[lastId = ((hasher(value) + i * hasher2(value)) % table.size())];
            if (node == noneElem || node == deletedElem)
                break;
            if (node == value) {
                return false;
            }
        }
        table[lastId] = value;
        if (++tableSize > table.size() * expandFactor)
            expand();
        return true;
    }
    bool pop(const T &value) {
        T node;
        size_t id;
        for (int i = 0; i < table.size(); i++) {
            node = table[id = ((hasher(value) + i * hasher2(value)) % table.size())];
            if (node == noneElem)
                return false;
            if (node == value) {
                table[id] = deletedElem;
                tableSize--;
                return true;
            }
        }
        return false;
    }
    bool select(const T &value) {
        T node;
        for (int i = 0; i < table.size(); i++) {
            node = table[(hasher(value) + i * hasher2(value)) % table.size()];
            if (node == noneElem)
                return false;
            if (node == value)
                return true;
        }
        return false;
    }

    bool checkAll(const T &value) {
        for (auto node: table) {
            if (node == value)
                return true;
        }
        return false;
    }

    void setField(size_t id, T value) {
        table[id] = value;
    }

    std::vector<T> getTable() {return table;}
private:
    std::vector<T> table;
    T noneElem, deletedElem;
    const unsigned int prime;
    Hasher hasher;
    Hasher2 hasher2;
    size_t tableSize;

    float expandFactor;
    void expand() {
        HashTable<T, Hasher, Hasher2> newTable(noneElem, deletedElem, table.size() * 2, expandFactor, prime);
        for (auto node: table) {
            if (node != noneElem && node != deletedElem)
                newTable.add(node);
        }
        table = newTable.getTable();
    }
};

class GornerHash {
public:
    int operator()(const std::string str) {
        int h = 0;
        const int a = 17;
        for (char sym: str)
            h = a*h + sym;
        return h * 2 + 1;
    }
};

class FirstWordHash {
public:
    int operator()(const std::string str) {
        return str[0] * 2 + 1;
    }
};

int main() {
    //std::ifstream answers("005_answ");
    //std::ifstream asserts("005");
    //std::string answer, assert;

    HashTable<std::string, GornerHash, FirstWordHash> table("NIL", "DEL");
    std::string cmnd, str;
    int num = 0;
    while (std::cin >> cmnd >> str) {
    //while (!asserts.eof()) {
        //answers >> answer;
        //asserts >> cmnd >> str;

        num++;
        if (cmnd == "+") {
            if (table.add(str)) {
                std::cout << "OK" << std::endl;
                //if (answer != "OK") {std::cout << num << ": OK, must be " << answer << ". ----------------Command: " << cmnd << " " << str << std::endl; table.print();}
            } else {
                std::cout << "FAIL" << std::endl;
                //if (answer != "FAIL") {std::cout << num << ": FAIL, must be " << answer << ". ----------------Command: " << cmnd << " " << str << std::endl; table.print();}
            }
        } else if (cmnd == "-") {
            if (table.pop(str)) {
                std::cout << "OK" << std::endl;
                //if (answer != "OK") {std::cout << num << ": OK, must be " << answer << ". ---------------Command: " << cmnd << " " << str << std::endl; table.print();}
            } else {
                std::cout << "FAIL" << std::endl;
                //if (answer != "FAIL") {std::cout << num << ": FAIL, must be " << answer << ". ----------------Command: " << cmnd << " " << str << std::endl; table.print();}
            }
        } else if (cmnd == "?") {
            if (table.select(str)) {
                std::cout << "OK" << std::endl;
                //if (answer != "OK") {std::cout << num << ": OK, must be " << answer << ". ----------------Command: " << cmnd << " " << str << std::endl; table.print();}
            } else {
                std::cout << "FAIL" << std::endl;
                //if (answer != "FAIL") {std::cout << num << ": FAIL, must be " << answer << ". -----------------Command: " << cmnd << " " << str << std::endl; table.print();}
            }
        } else {
            std::cout << "Unknown command: " << cmnd << " " << str << std::endl;
        }
        //table.print();
    }
}
