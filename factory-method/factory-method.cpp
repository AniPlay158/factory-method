#include <iostream>
using namespace std;

/*
Інтерфейс Продукту повідомляє операції, які повинні виконувати всі конкретні продукти.
*/

class Product {
public:
    virtual ~Product() {}
    virtual string Operation() const = 0;
};

/*
Конкретні продукти надають різні реалізації інтерфейсу продукту.
*/
class ConcreteProduct1 : public Product {
public:
    string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public Product {
public:
    string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

/**
 Клас Творець оголошує фабричний метод, який має повертати об'єкт
 класу Продукт. Підкласи Творця зазвичай надають реалізацію цього
 методу.
 */

class Creator {
    /*
     Зауважте, що Творець може також забезпечити реалізацію фабричного методу за умовчанням.
     */
public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;
    /*
    Також зауважте, що, незважаючи на назву, основний обов'язок Творця
    не полягає у створенні продуктів. Зазвичай він містить деяку базову
    бізнес-логіку, яка заснована на об'єктах Продуктів, що повертаються
    Фабричним способом. Підкласи можуть опосередковано змінювати цю бізнес-логіку,
    перевизначаючи фабричний метод та повертаючи з нього інший тип продукту.
     */

    string SomeOperation() const {
        // Викликаємо фабричний метод, щоби отримати об'єкт-продукт.
        Product* product = this->FactoryMethod();
        // Далі працюємо з цим продуктом.
        string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

/*
 Конкретні Творці перевизначають фабричний метод для того, щоб змінити тип результуючого продукту.
 */
class ConcreteCreator1 : public Creator {
    /*
     Зверніть увагу, що сигнатура методу, як і раніше, використовує тип
    абстрактного продукту, хоча фактично з методу повертається конкретний
    продукт. Таким чином, Творець може залишатися незалежним від
    конкретних класів товарів.
     */
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

/*
    Клієнтський код працює з екземпляром конкретного творця, хоча через нього
    базовий інтерфейс. Поки що клієнт продовжує працювати зі творцем через базовий
    інтерфейс, ви можете передати йому будь-який підклас творця.
 */
void ClientCode(const Creator& creator) {
    
    cout << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << endl;
    
}

/*
 Програма вибирає тип творця залежно від конфігурації чи середовища.
 */

int main() {
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    cout << endl;
    cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}