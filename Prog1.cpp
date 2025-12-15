#include <iostream>

using namespace std;

class Vehicle
{
protected:
    int VehicleID;
    string Manufacturer;
    string Model;
    int Year;

public:
    static int TotalVehicles;

    Vehicle()
    {
    }

    Vehicle(int id, string man, string mod, int yr)
    {
        VehicleID = id;
        Manufacturer = man;
        Model = mod;
        Year = yr;
        TotalVehicles++;
    }

    int getVehicleID() { return VehicleID; }

    virtual void display()
    {
        cout << "Vehicle ID : " << VehicleID << endl;
        cout << "Manufacturer : " << Manufacturer << endl;
        cout << "Model : " << Model << endl;
        cout << "Year : " << Year << endl;
    }
};

int Vehicle::TotalVehicles = 0;

class Car : public Vehicle
{
protected:
    string FuelType;

public:
    Car() {}

    Car(int id, string manufacture, string model, int yr, string fuel)
        : Vehicle(id, manufacture, model, yr)
    {
        FuelType = fuel;
    }

    void display()
    {
        Vehicle::display();
        cout << "Fuel Type: " << FuelType << endl;
    }
};

class ElectricCar : public Car
{
protected:
    int BatteryCapacity;

public:
    ElectricCar() {}

    ElectricCar(int id, string manufacture, string model, int yr, string fuel, int battery)
        : Car(id, manufacture, model, yr, fuel)
    {
        BatteryCapacity = battery;
    }

    void display()
    {
        Car::display();
        cout << "Battery Capacity: " << BatteryCapacity << " kWh" << endl;
    }
};

class Aircraft
{
protected:
    int FlightRange;

public:
    Aircraft() {}

    Aircraft(int range)
    {
        FlightRange = range;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar() {}

    FlyingCar(int id, string manufacture, string model, int yr, string fuel, int range)
        : Car(id, manufacture, model, yr, fuel), Aircraft(range) {}

    void display()
    {
        Car::display();
        cout << "Flight Range: " << FlightRange << " km" << endl;
    }
};

class SportsCar : public ElectricCar
{
protected:
    int TopSpeed;

public:
    SportsCar() {}

    SportsCar(int id, string manufacture, string model, int yr, string fuel, int battery, int speed)
        : ElectricCar(id, manufacture, model, yr, fuel, battery)
    {
        TopSpeed = speed;
    }

    void display()
    {
        ElectricCar::display();
        cout << "Top Speed: " << TopSpeed << " km/h" << endl;
    }
};

class Sedan : public Car
{
public:
    Sedan(int id, string manufacture, string model, int yr, string fuel)
        : Car(id, manufacture, model, yr, fuel) {}
};

class SUV : public Car
{
public:
    SUV(int id, string manufacture, string model, int yr, string fuel)
        : Car(id, manufacture, model, yr, fuel) {}
};

class VehicleRegistry
{
public:
    Vehicle *v[50];
    int count;

    VehicleRegistry()
    {
        count = 0;
    }

    void add(Vehicle *V)
    {
        v[count++] = V;
        cout << "Vehicle Added!" << endl;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "No vehicles." << endl;
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << endl
                 << "Vehicle " << i + 1 << "" << endl;
            v[i]->display();
        }
    }

    void search(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (v[i]->getVehicleID() == id)
            {
                cout << "Vehicle Found:" << endl;
                v[i]->display();
                return;
            }
        }
        cout << "Not Found!" << endl;
    }
};

int main()
{
    VehicleRegistry reg;
    int choice;

    do
    {
        cout << endl << "----- MENU -----" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. Display All Vehicles" << endl;
        cout << "3. Search" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int type;
            cout << endl<< "1.Car" << endl << "2.Electric" << endl << "3.Flying" << endl << "4.Sports" << endl << "5.Sedan" << endl << "6.SUV" << endl << "Choice:";
            cin >> type;

            int id, yr;
            string man, mod, fuel;
            int battery, range, speed;

            cout << "ID: ";
            cin >> id;

            cout << "Manufacturer: ";
            cin >> man;

            cout << "Model: ";
            cin >> mod;

            cout << "Year: ";
            cin >> yr;

            switch (type)
            {
            case 1:
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new Car(id, man, mod, yr, fuel));
                break;

            case 2:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> battery;
                reg.add(new ElectricCar(id, man, mod, yr, fuel, battery));
                break;

            case 3:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Range: ";
                cin >> range;
                reg.add(new FlyingCar(id, man, mod, yr, fuel, range));
                break;

            case 4:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> battery;
                cout << "Speed: ";
                cin >> speed;
                reg.add(new SportsCar(id, man, mod, yr, fuel, battery, speed));
                break;

            case 5:
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new Sedan(id, man, mod, yr, fuel));
                break;

            case 6:
                cout << "Fuel: ";
                cin >> fuel;
                reg.add(new SUV(id, man, mod, yr, fuel));
                break;
            }
            break;
        }

        case 2:
            reg.display();
            break;

        case 3:
        {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            reg.search(id);
            break;
        }

        case 4:
            cout << "Exited Succesfully..." << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}