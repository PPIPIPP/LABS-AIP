#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <initializer_list>

// *** Умный указатель ***
template<typename T>
class SmartPointer {
private:
    T* ptr;

public:
  
    SmartPointer() : ptr(nullptr) {}

    explicit SmartPointer(T* p) : ptr(p) {}

    ~SmartPointer() {
        delete ptr;
    }

    SmartPointer(const SmartPointer& other) {
        if (other.ptr) {
            ptr = new T(*other.ptr);
        }
        else {
            ptr = nullptr;
        }
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr ? new T(*other.ptr) : nullptr;
        }
        return *this;
    }

    SmartPointer(SmartPointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        if (!ptr) throw std::runtime_error("Dereferencing a null pointer");
        return *ptr;
    }

    T* operator->() const {
        if (!ptr) throw std::runtime_error("Accessing a null pointer");
        return ptr;
    }

    T* get() const {
        return ptr;
    }
};

// *** Обработчик исключений ***
class VectorException : public std::exception {
private:
    std::string message;

public:
    explicit VectorException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// *** Целевой класс Vect ***
template<typename T>
class Vect {
private:
    std::list<T> data;

public:

    Vect() = default;

    Vect(std::initializer_list<T> init) : data(init) {}

    Vect(const Vect& other) : data(other.data) {}

    Vect& operator=(const Vect& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    Vect(Vect&& other) noexcept : data(std::move(other.data)) {}

    Vect& operator=(Vect&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    void push_back(const T& value) {
        data.push_back(value);
    }

    void pop_back() {
        if (data.empty()) {
            throw VectorException("Cannot pop from an empty vector");
        }
        data.pop_back();
    }

    size_t size() const {
        return data.size();
    }

    T& at(size_t index) {
        if (index >= data.size()) {
            throw VectorException("Index out of bounds");
        }
        auto it = data.begin();
        std::advance(it, index);
        return *it;
    }

    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// *** Меню для клиента ***
void menu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add element\n";
    std::cout << "2. Remove last element\n";
    std::cout << "3. Get element by index\n";
    std::cout << "4. Print all elements\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose an option: ";
}

// *** Тестирование Vect для конкретного типа ***
template<typename T>
void testVect() {
    Vect<T> vect;

    int choice;
    do {
        menu();
        std::cin >> choice;

        try {
            switch (choice) {
            case 1: {
                T value;
                std::cout << "Enter value: ";
                std::cin >> value;
                vect.push_back(value);
                break;
            }
            case 2:
                vect.pop_back();
                break;
            case 3: {
                size_t index;
                std::cout << "Enter index: ";
                std::cin >> index;
                std::cout << "Element at index " << index << ": " << vect.at(index) << std::endl;
                break;
            }
            case 4:
                vect.print();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
            }
        }
        catch (const VectorException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } while (choice != 5);
}

// *** Главная функция ***
int main() {
    int typeChoice;
    std::cout << "Choose type:\n1. int\n2. double\n3. std::string\n";
    std::cin >> typeChoice;

    switch (typeChoice) {
    case 1:
        testVect<int>();
        break;
    case 2:
        testVect<double>();
        break;
    case 3:
        testVect<std::string>();
        break;
    default:
        std::cout << "Invalid type. Exiting...\n";
    }

    return 0;
}