#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
concept ComplexConcept = requires(T t) {
    // Проверяем наличие метода hash(), который возвращает тип, конвертируемый в long
    { t.hash() } -> std::convertible_to<long>;

    // Проверяем наличие метода toString(), который возвращает std::string
    { t.toString() } -> std::same_as<std::string>;

    // Проверяем отсутствие виртуального деструктора
    requires !std::has_virtual_destructor<T>;
};

// Пример использования концепта
class MyType {
public:
    long hash() const {
        return 42;
    }

    std::string toString() const {
        return "MyType";
    }
};

class DerivedType : public MyType {
public:
    // Виртуальный деструктор
    virtual ~DerivedType() {}
};

int main() {
    static_assert(ComplexConcept<MyType>);
    // static_assert(ComplexConcept<DerivedType>); // Не проходит компиляцию из-за виртуального деструктора
    return 0;
}
