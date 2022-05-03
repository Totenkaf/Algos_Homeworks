// Copyright 2022 by Artem Ustsov

// Задача 1_1

/*
* Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
* Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
* Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
* Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству

** Требования к варианту задачи : 
*
* Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
* g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

** Требования: В таблице запрещено хранение указателей на описатель элемента.

** Формат входных данных
* Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
* Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество; 
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству. 
* При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

** Формат выходных данных
* Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.
*
*/

#include <iostream>
#include <string>
#include <vector>

const size_t INITIAL_CAPACITY = 8;
const double LAMBDA = 0.75;

class StringHasher {
public:
    explicit StringHasher(size_t prime = 13)
    : prime(prime)
    {}

    ~StringHasher() = default;
    size_t operator() (const std::string& str) const {
        size_t hash = 0;
        for (auto symbol : str) {
            hash = hash * prime + symbol;
        }
        return hash;
    }

private:
    size_t prime;
};

template<class T, class Hasher = StringHasher>
class HashTable {
public:
    explicit HashTable(size_t initial_capacity = INITIAL_CAPACITY);
    ~HashTable();

    bool add(const T& key);
    bool remove(const T& key);
    bool has(const T& key) const;

private:
    struct HashTableElement {
        HashTableElement() 
        : is_del(false), is_nil(true) 
        {}

        explicit HashTableElement(const T& key_) 
        : key(key_), is_del(false), is_nil(false) 
        {}

        ~HashTableElement() = default;

        T key;
        bool is_del;
        bool is_nil;
    };

    void grow_hash_table();
    Hasher hasher;
    std::vector<HashTableElement> table_data;
    size_t num_of_keys;
};

template<class T, class Hasher>
HashTable<T, Hasher>::HashTable(size_t initial_capacity) 
: table_data(initial_capacity, HashTableElement()), num_of_keys(0)
{}

template<class T, class Hasher>
HashTable<T, Hasher>::~HashTable()
{}

template<class T, class Hasher>
bool HashTable<T, Hasher>::add(const T& key) {
    if (static_cast<double>(num_of_keys) >= LAMBDA * static_cast<double>(table_data.size())) {
        grow_hash_table();
    }
    size_t hash = hasher(key) % table_data.size();

    int first_del_position = -1;
    for (size_t i = 0; i < table_data.size(); ++i) {

        if(table_data[hash].is_nil) {
            break;
        }

        if((table_data[hash].key == key) && !table_data[hash].is_del) {
            return false;
        }

        if((table_data[hash].is_del) && (first_del_position == -1)) {
            first_del_position = hash;
        }

        hash = (hash + i) % table_data.size();  
    }

    hash = ((first_del_position == -1) ? hash : first_del_position);
    table_data[hash] = HashTableElement(key);
    ++num_of_keys;
    return true;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::has(const T& key) const {
    size_t hash = hasher(key) % table_data.size();
    for (size_t i = 0; i < table_data.size(); ++i) {

        if((table_data[hash].is_nil)) {
            break;
        }

        if(table_data[hash].key == key && !table_data[hash].is_del) {
            return true;
        }

        hash = (hash + i) % table_data.size();  
    }
    return false;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::remove(const T& key) {
    size_t hash = hasher(key) % table_data.size();
    for (size_t i = 0; i < table_data.size(); ++i) {

        if((table_data[hash].is_nil)) {
            break;
        }

        if(table_data[hash].key == key && !table_data[hash].is_del) {
            table_data[hash].is_del = true;
            --num_of_keys;
            return true;
        }

        hash = (hash + i) % table_data.size();  
    }
    return false;
}

template<class T, class Hasher>
void HashTable<T, Hasher>::grow_hash_table() {
    std::vector<HashTableElement> new_table_data(table_data.size() * 2, 
                                                 HashTableElement());
    for (size_t i = 0; i < table_data.size(); ++i) {
        if(!table_data[i].is_del && !table_data[i].is_nil) {
            size_t hash = hasher(table_data[i].key) % new_table_data.size();
            size_t counter = 0;
            while(!new_table_data[hash].is_nil) {
                hash = (hash + counter) % new_table_data.size(); 
                ++counter;
            }
            new_table_data[hash].key = table_data[i].key;
            new_table_data[hash].is_nil = false;
        }
    }
    table_data = std::move(new_table_data);
    return;
}

void run(std::istream &is, std::ostream &os) {
    HashTable<std::string, StringHasher> table;
    char command;
    std::string key;
    while (is >> command >> key) {
        switch(command) {
            case '+':
                os << (table.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                os << (table.has(key) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                os << (table.remove(key) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return;
}

int main(int argc, char *argv[]) {
    run(std::cin, std::cout);
    return 0;
}
