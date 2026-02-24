#include <iostream>
using namespace std;

class Mechanic;  // forward declaration

class Car {
private:
    int engineNumber;

public:
    Car(int num) : engineNumber(num) {}

    friend class Mechanic;  // Mechanic class ko special access
};

class Mechanic {
public:
    void inspectCar(Car c) {
        cout << "Engine Number: " << c.engineNumber << endl;
    }
};

int main() {
    Car myCar(12345);
    Mechanic m;
    m.inspectCar(myCar);
}