#include <iostream>
#include <string>
#include <list>
using namespace std;

class Vehicle 
{
protected:

    string manufacturer;
    string model;
    string color;
    int year;
    int maxSpeed;

public:

    Vehicle(const string& manufacturer, const string& model, const string& color, int year, int maxSpeed): manufacturer(manufacturer), model(model), color(color), year(year), maxSpeed(maxSpeed) 
    {

    }

    virtual void drive() const = 0; 
    virtual void display() const = 0;
    virtual ~Vehicle() = default; 
};

class Car : public Vehicle 
{
    double price;

public:

    Car(const string& manufacturer, const string& model, const string& color, int year, int maxSpeed, double price): Vehicle(manufacturer, model, color, year, maxSpeed), price(price) 
    {

    }

    void drive() const override 
    {
        cout << "Driving a car from 0 to " << maxSpeed << " km/h!" << endl;
    }

    void display() const override 
    {
        cout << "Car - Manufacturer: " << manufacturer << ", Model: " << model << ", Color: " << color << ", Year: " << year << ", Max Speed: " << maxSpeed << ", Price: " << price << "$" << endl;
    }

    double getPrice() const 
    { 
        return price; 
    }
};

class Motorcycle : public Vehicle 
{
    double price;
    double rentPricePerDay;
    bool isRented;

public:

    Motorcycle(const string& manufacturer, const string& model, const string& color, int year, int maxSpeed, double price, double rentPricePerDay): Vehicle(manufacturer, model, color, year, maxSpeed), price(price), rentPricePerDay(rentPricePerDay), isRented(false) 
    {

    }

    void drive() const override 
    {
        cout << "Riding a motorcycle from 0 to " << maxSpeed / 2 << " km/h!" << endl;
    }

    void display() const override 
    {
        cout << "Motorcycle - Manufacturer: " << manufacturer << ", Model: " << model << ", Color: " << color << ", Year: " << year << ", Max Speed: " << maxSpeed << ", Price: " << price << "$, Rent Per Day: " << rentPricePerDay << "$"  << ", Rented: " << (isRented ? "Yes" : "No") << endl;
    }

    double getPrice() const 
    { 
        return price; 
    }
    double getRentPrice() const 
    { 
        return rentPricePerDay; 
    }

    bool rent() 
    { 
        if (isRented)
        {
            return false;
        }  
        isRented = true;
        return true;
    }
    void returnItem() 
    { 
        isRented = false; 
    }
};

class Bicycle : public Vehicle 
{
    double rentPricePerDay;
    bool isRented;

public:

    Bicycle(const string& manufacturer, const string& model, const string& color, int year, int maxSpeed, double rentPricePerDay): Vehicle(manufacturer, model, color, year, maxSpeed), rentPricePerDay(rentPricePerDay), isRented(false) 
    {

    }

    void drive() const override 
    {
        for (int i = 0; i < maxSpeed; ++i) 
        {
            cout << "Pedaling ";
        }
        cout << endl;
    }

    void display() const override 
    {
        cout << "Bicycle - Manufacturer: " << manufacturer << ", Model: " << model << ", Color: " << color << ", Year: " << year << ", Max Speed: " << maxSpeed << ", Rent Per Day: " << rentPricePerDay << "$, Rented: " << (isRented ? "Yes" : "No") << endl;
    }

    double getRentPrice() const 
    { 
        return rentPricePerDay; 
    }

    bool rent() 
    { 
        if (isRented)
        {
            return false;
        }  
        isRented = true;
        return true;
    }
    void returnItem() 
    { 
        isRented = false; 
    }
};

class Store 
{
    list<Vehicle*> inventory;

public:

    ~Store() 
    {
        for (Vehicle* item : inventory) 
        {
            delete item;
        }
    }

    void addItem(Vehicle* item) 
    {
        inventory.push_back(item);
    }

    void showItems() const 
    {
        for (const auto& item : inventory) 
        {
            item->display();
        }
    }

    void sellItem(int index) 
    {
        auto it = inventory.begin();
        advance(it, index);
        Vehicle* item = *it;

        if (Car* car = dynamic_cast<Car*>(item)) 
        {
            cout << "Selling car for " << car->getPrice() << "$" << endl;
            delete item; 
            inventory.erase(it);
        } 
        else if (Motorcycle* motorcycle = dynamic_cast<Motorcycle*>(item)) 
        {
            if (!motorcycle->rent()) 
            {
                cout << "Selling motorcycle for " << motorcycle->getPrice() << "$" << endl;
                delete item; 
                inventory.erase(it);
            } 
            else 
            {
                cout << "Motorcycle is rented and cannot be sold." << endl;
            }
        } 
        else 
        {
            cout << "This item cannot be sold!" << endl;
        }
    }

    void rentItem(int index, int days) 
    {
        auto it = inventory.begin();
        advance(it, index);
        Vehicle* item = *it;

        if (Motorcycle* motorcycle = dynamic_cast<Motorcycle*>(item)) 
        {
            if (motorcycle->rent()) 
            {
                cout << "Renting motorcycle for " << motorcycle->getRentPrice() * days << "$" << endl;
            } 
            else 
            {
                cout << "Motorcycle is already rented!" << endl;
            }
        } 
        else if (Bicycle* bicycle = dynamic_cast<Bicycle*>(item)) 
        {
            if (bicycle->rent()) 
            {
                cout << "Renting bicycle for " << bicycle->getRentPrice() * days << "$" << endl;
            } 
            else 
            {
                cout << "Bicycle is already rented!" << endl;
            }
        } 
        else 
        {
            cout << "This item cannot be rented!" << endl;
        }
    }
};

int main() 
{
    Store store;

    store.addItem(new Car("BMW", "M3 GTR", "White and Blue", 2005, 300, 50000));
    store.addItem(new Motorcycle("Yamaha", "R1", "Red", 2022, 200, 15000, 100));
    store.addItem(new Bicycle("Trek", "FX 3", "Black", 2021, 20, 10));

    cout << "Store inventory:\n";
    store.showItems();

    cout << "\nSelling the first item:\n";
    store.sellItem(0);

    cout << "\nRenting the second item for 3 days:\n";
    store.rentItem(0, 3);

    cout << "\nStore inventory after transactions:\n";
    store.showItems();

    return 0;
}
