#include <iostream>
#include <vector>
#include <string>

class Vehicle {
public:
    Vehicle(std::string id, double maxSpeed) : id(id), maxSpeed(maxSpeed) {}
    
    virtual void startEngine() {
        std::cout << "Engine started" << std::endl;
        engineRunning = true;
    }
    
    virtual void stopEngine() {
        std::cout << "Engine stopped" << std::endl;
        engineRunning = false;
    }
    
    virtual void accelerate(double amount) {
        if (engineRunning) {
            currentSpeed = std::min(currentSpeed + amount, maxSpeed);
            std::cout << "Speed: " << currentSpeed << " mph" << std::endl;
        } else {
            std::cout << "Cannot accelerate - engine is not running" << std::endl;
        }
    }
    
    virtual void brake(double amount) {
        currentSpeed = std::max(currentSpeed - amount, 0.0);
        std::cout << "Speed: " << currentSpeed << " mph" << std::endl;
    }
    
    virtual void refuel(double amount) {
        fuelLevel += amount;
        std::cout << "Fuel level: " << fuelLevel << " gallons" << std::endl;
    }
    
    virtual void checkFluids() {
        std::cout << "Checking oil, coolant, and brake fluid levels" << std::endl;
    }
    
    virtual void changeTires() {
        std::cout << "Changing tires" << std::endl;
    }
    
    std::string getId() const { return id; }
    double getCurrentSpeed() const { return currentSpeed; }

protected:
    std::string id;
    double maxSpeed;
    double currentSpeed = 0.0;
    double fuelLevel = 0.0;
    bool engineRunning = false;
};

class ElectricBicycle : public Vehicle {
public:
    ElectricBicycle(std::string id, double maxSpeed, int batteryCapacity)
        : Vehicle(id, maxSpeed), batteryCapacity(batteryCapacity) {}
    
    void startEngine() override {
        std::cout << "Electric bicycle doesn't have an engine. Turning on electric assist." << std::endl;
        assistOn = true;
    }
    
    void stopEngine() override {
        std::cout << "Turning off electric assist." << std::endl;
        assistOn = false;
    }
    
    void accelerate(double amount) override {
        if (assistOn) {
            currentSpeed = std::min(currentSpeed + amount, maxSpeed);
            std::cout << "Speed with electric assist: " << currentSpeed << " mph" << std::endl;
            batteryLevel -= amount * 0.05;
        } else {
            currentSpeed = std::min(currentSpeed + amount/2, maxSpeed/2);
            std::cout << "Speed without assist: " << currentSpeed << " mph" << std::endl;
        }
    }
    
    // This method doesn't really apply to an electric bicycle
    void refuel(double amount) override {
        throw std::logic_error("Electric bicycles don't use fuel!");
    }
    
    // Not applicable to electric bicycles either
    void checkFluids() override {
        throw std::logic_error("Electric bicycles don't have fluids to check!");
    }
    
    void chargeBattery(double amount) {
        batteryLevel = std::min(batteryLevel + amount, (double)batteryCapacity);
        std::cout << "Battery charged to " << batteryLevel << " Wh" << std::endl;
    }
    
    double getBatteryLevel() const { return batteryLevel; }

private:
    int batteryCapacity;    // Watt-hours
    double batteryLevel = 0.0;
    bool assistOn = false;
};

int main() {
    Vehicle car("C123", 120.0);
    ElectricBicycle ebike("EB456", 25.0, 500);
    
    car.startEngine();
    car.accelerate(30.0);
    car.refuel(10.0);
    
    std::cout << "\n";
    
    ebike.startEngine();
    ebike.accelerate(15.0);
    try {
        ebike.refuel(5.0);  // This will throw an exception
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    ebike.chargeBattery(250.0);
    
    return 0;
}
