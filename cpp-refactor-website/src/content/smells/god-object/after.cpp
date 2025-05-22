// after.cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>

// --- User Management Subsystem ---
class UserManager {
public:
    bool login(const std::string& username, const std::string& password) {
        if (users.count(username) && users[username] == password) {
            currentUser = username;
            std::cout << username << " logged in successfully." << std::endl;
            return true;
        }
        std::cout << "Login failed for " << username << "." << std::endl;
        return false;
    }

    void logout() {
        if (!currentUser.empty()) {
            std::cout << currentUser << " logged out." << std::endl;
            currentUser = "";
        }
    }

    void addUser(const std::string& username, const std::string& password) {
        if (users.find(username) == users.end()) {
            users[username] = password;
            std::cout << "User " << username << " added." << std::endl;
        } else {
            std::cout << "User " << username << " already exists." << std::endl;
        }
    }
    
    bool isUserLoggedIn() const { return !currentUser.empty(); }
    std::string getCurrentUser() const { return currentUser; }

private:
    std::map<std::string, std::string> users;
    std::string currentUser;
};

// --- Device Control Subsystems ---
class LightManager {
public:
    void turnOn(int lightId) {
        lightsStatus[lightId] = true;
        std::cout << "Light " << lightId << " turned on." << std::endl;
    }
    void turnOff(int lightId) {
        lightsStatus[lightId] = false;
        std::cout << "Light " << lightId << " turned off." << std::endl;
    }
    void printStatus() const {
        std::cout << "Lights On: ";
        for(auto const& [id, status] : lightsStatus) if(status) std::cout << id << " ";
        std::cout << std::endl;
    }
private:
    std::map<int, bool> lightsStatus;
};

class ThermostatManager {
public:
    void setTemperature(double temperature) {
        currentTemp = temperature;
        std::cout << "Thermostat set to " << temperature << " degrees." << std::endl;
    }
    void printStatus() const {
        std::cout << "Thermostat: " << currentTemp << " degrees" << std::endl;
    }
private:
    double currentTemp = 20.0;
};

class SecurityManager {
public:
    void arm() {
        isArmed = true;
        std::cout << "Security system armed." << std::endl;
    }
    void disarm() {
        isArmed = false;
        std::cout << "Security system disarmed." << std::endl;
    }
    void printStatus() const {
        std::cout << "Security: " << (isArmed ? "Armed" : "Disarmed") << std::endl;
    }
private:
    bool isArmed = false;
};

// --- Scheduling Subsystem ---
class Scheduler {
public:
    struct ScheduleItem { std::string device, time, action; };
    void add(const std::string& device, const std::string& time, const std::string& action) {
        items.push_back({device, time, action});
        std::cout << "Scheduled " << action << " for " << device << " at " << time << std::endl;
    }
    void view() const {
        std::cout << "--- Schedules ---" << std::endl;
        for(const auto& s : items) {
            std::cout << s.device << " at " << s.time << " -> " << s.action << std::endl;
        }
        std::cout << "-----------------" << std::endl;
    }
private:
    std::vector<ScheduleItem> items;
};

// --- SmartHomeSystem (Coordinator) ---
class SmartHomeSystem {
public:
    SmartHomeSystem() : userManager(), lightManager(), thermostatManager(), securityManager(), scheduler() {}

    // User actions delegated
    bool login(const std::string& username, const std::string& password) { return userManager.login(username, password); }
    void logout() { userManager.logout(); }
    void addUser(const std::string& username, const std::string& password) { userManager.addUser(username, password); }

    // Device actions delegated, with login check
    void turnOnLight(int lightId) { if(checkLogin()) lightManager.turnOn(lightId); }
    void turnOffLight(int lightId) { if(checkLogin()) lightManager.turnOff(lightId); }
    void setThermostat(double temperature) { if(checkLogin()) thermostatManager.setTemperature(temperature); }
    void armSecuritySystem() { if(checkLogin()) securityManager.arm(); }
    void disarmSecuritySystem() { if(checkLogin()) securityManager.disarm(); }
    void addSchedule(const std::string& device, const std::string& time, const std::string& action) { if(checkLogin()) scheduler.add(device, time, action); }

    void printSystemStatus() {
        std::cout << "\n--- Smart Home System Status ---" << std::endl;
        std::cout << "Current User: " << (userManager.isUserLoggedIn() ? userManager.getCurrentUser() : "None") << std::endl;
        lightManager.printStatus();
        thermostatManager.printStatus();
        securityManager.printStatus();
        if(checkLogin()) scheduler.view();
        std::cout << "------------------------------\n" << std::endl;
    }

private:
    UserManager userManager;
    LightManager lightManager;
    ThermostatManager thermostatManager;
    SecurityManager securityManager;
    Scheduler scheduler;

    bool checkLogin() {
        if (!userManager.isUserLoggedIn()) {
            std::cout << "No user logged in. Please login to perform this action." << std::endl;
            return false;
        }
        return true;
    }
};

int main() {
    SmartHomeSystem myHome;
    myHome.addUser("admin", "password123");
    myHome.login("admin", "password123");

    myHome.turnOnLight(1);
    myHome.setThermostat(22.5);
    myHome.armSecuritySystem();
    myHome.addSchedule("Light 1", "22:00", "Turn Off");
    
    myHome.printSystemStatus();
    
    myHome.logout();

    // Try action without login
    myHome.turnOnLight(2);
    return 0;
}
