#include <iostream> 
#include <cmath> 
#include <stdexcept> 
#include <string> 

// Класс для пользовательских исключений 
class CustomException : public std::exception {
private:
    std::string message;
    double errorValue;
    int errorCode;

    // Конструктор и инициализация 
public:
    CustomException(const std::string& msg, double value, int code)
        : message(msg), errorValue(value), errorCode(code) {
    }

    // Возвращает сообщение об ошибке 

    const char* what() const noexcept override {
        return message.c_str();
    }

    // Получение значения ошибки 

    double getErrorValue() const {
        return errorValue;
    }

    // Получение кода ошибки 

    int getErrorCode() const {
        return errorCode;
    }
};

// Вычисление Z1 
void calculateZ1(double b, double& Z1) {

    setlocale(LC_ALL, "RU");

    if (b * b - 4 < 0) {
        throw CustomException("Ошибка: подкоренное выражение отрицательно", b, 1);
    }

    double sqrtPart = sqrt(b * b - 4);
    if (sqrtPart + b + 2 == 0) {
        throw CustomException("Ошибка: деление на ноль", b, 2);
    }

    Z1 = sqrt(2 * b + sqrtPart) / (sqrtPart + b + 2);
}

// Вычисление Z2 
void calculateZ2(double b, double& Z2) {

    setlocale(LC_ALL, "RU");

    if (b + 2 < 0) {
        throw CustomException("Ошибка: подкоренное выражение отрицательно", b, 1);
    }

    Z2 = 1 / sqrt(b + 2);
}

int main() {

    setlocale(LC_ALL, "RU");

    double b;
    double Z1 = 0, Z2 = 0;

    std::cout << "Введите значение b: ";
    std::cin >> b;

    try {
        calculateZ1(b, Z1);
        std::cout << "Z1 = " << Z1 << std::endl;

        calculateZ2(b, Z2);
        std::cout << "Z2 = " << Z2 << std::endl;

        // Проверка на равенство 
        if (fabs(Z1 - Z2) < 1e-6) {
            std::cout << "Z1 и Z2 приблизительно равны." << std::endl;
        }
        else {
            std::cout << "Z1 и Z2 не равны." << std::endl;
        }

        // Вывод сообщения об ошибке, Вывод значения ошибки, Вывод кода ошибки 

    }
    catch (const CustomException& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        std::cerr << "Значение, вызвавшее ошибку: " << e.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << e.getErrorCode() << std::endl;

        // Обработка стандартного исключения, Вывод сообщения о стандартной ошибке 

    }
    catch (const std::exception& e) {
        std::cerr << "Произошла стандартная ошибка: " << e.what() << std::endl;
    }

    return 0;
}