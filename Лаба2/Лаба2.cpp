#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

using namespace std;

/* Разработать шаблонный класс MMap, для представления ключей и
значений(словаря).Словарь может хранить повторяющиеся ключи.Элементы в
словаре хранятся отсортированными */

template <typename K, typename V>
class MMap {
public:

    // Конструктор по умолчанию

    MMap() = default;

    // initializer_list

    MMap(initializer_list<pair<K, V>> initList) 
    {
        for (const auto& item : initList) 
        {
            insert(item.first, item.second);
        }
    }

    // Конструктор + копирующий оператор

    MMap(const MMap& other) : data(other.data) {}

    MMap& operator=(const MMap& other) 
    {
        if (this != &other) 
        {
            data = other.data;
        }
        return *this;
    }

    // Конструктор + перемещающий оператор

    MMap(MMap&& other) noexcept : data(move(other.data)) {}

    MMap& operator=(MMap&& other) noexcept 
    {
        if (this != &other) 
        {
            data = move(other.data);
        }
        return *this;
    }

    // Операция индексирования

    V& operator[](size_t index) {
        if (index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index].second;
    }

    const V& operator[](size_t index) const {
        if (index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index].second;
    }

    // Вставка ключа и значения

    void insert(const K& key, const V& value) {
        data.push_back(make_pair(key, value));

        // Сортировка

        sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
            });
    }

    // Удаление ключа

    void erase(const K& key) {
        data.erase(
            remove_if(data.begin(), data.end(),
                [&key](const auto& pair) { return pair.first == key; }),
            data.end());
    }

    // Поиск всех значений для ключа

    vector<V> find(const K& key) const {
        vector<V> values;
        for (const auto& pair : data) {
            if (pair.first == key) {
                values.push_back(pair.second);
            }
        }
        return values;
    }

    // Добавление

    void insertAt(size_t position, const K& key, const V& value) {
        if (position > data.size()) {
            throw out_of_range("Position out of range");
        }
        data.insert(data.begin() + position, make_pair(key, value));
    }

    // Отображение

    void display() const {
        for (const auto& pair : data) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

private:

    vector<pair<K, V>> data;
};

int main() {

    setlocale(LC_ALL, "RU");

    MMap<int, string> mmap;

    mmap.insert(3, "apple");
    mmap.insert(2, "banana");
    mmap.insert(7, "qqq");
    mmap.insert(3, "cherry");
    mmap.insert(4, "car");
    mmap.insert(2, "orange");
    mmap.insert(5, "train");
    mmap.insert(1, "wagon");

    cout << "Содержимое MMap:\n";
    mmap.display();

    mmap.insert(4, "date");
    cout << "\nПосле добавления пары {4, 'date'}:\n";
    mmap.display();

    cout << "\nЗначения для ключа 2:\n";
    auto values = mmap.find(2);
    for (const auto& value : values) {
        cout << value << "\n";
    }

    cout << "\nУдаляем ключ 3...\n";
    mmap.erase(3);
    mmap.display();

    cout << "\nВставляем пару {5, 'fig'} на позицию 1:\n";
    mmap.insertAt(1, 5, "fig");
    mmap.display();

    cout << "\nЭлемент на позиции 0: " << mmap[0] << endl;

    return 0;
}
