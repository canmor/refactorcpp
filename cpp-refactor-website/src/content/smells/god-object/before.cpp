// before.cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>

// God Object: SmartHomeSystem manages everything
class SmartHomeSystem {
public:
    // User Management
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
        std::cout << currentUser << " logged out." << std::endl;
        currentUser = "";
    }

    void addUser(const std::string& username, const std::string& password) {
        if (users.find(username) == users.end()) {
            users[username] = password;
            std::cout << "User " << username << " added." << std::endl;
        } else {
            std::cout << "User " << username << " already exists." << std::endl;
        }
    }

    // Device Control - Lights
    void turnOnLight(int lightId) {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        lightsStatus[lightId] = true;
        std::cout << "Light " << lightId << " turned on." << std::endl;
    }

    void turnOffLight(int lightId) {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        lightsStatus[lightId] = false;
        std::cout << "Light " << lightId << " turned off." << std::endl;
    }

    // Device Control - Thermostat
    void setThermostat(double temperature) {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        thermostatTemp = temperature;
        std::cout << "Thermostat set to " << temperature << " degrees." << std::endl;
    }

    // Device Control - Security System
    void armSecuritySystem() {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        securityArmed = true;
        std::cout << "Security system armed." << std::endl;
    }

    void disarmSecuritySystem() {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        securityArmed = false;
        std::cout << "Security system disarmed." << std::endl;
    }
    
    // Scheduling
    void addSchedule(const std::string& device, const std::string& time, const std::string& action) {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        schedules.push_back({device, time, action});
        std::cout << "Scheduled " << action << " for " << device << " at " << time << std::endl;
    }

    void viewSchedules() {
        if (currentUser.empty()) { std::cout << "No user logged in." << std::endl; return; }
        std::cout << "--- Schedules ---" << std::endl;
        for(const auto& s : schedules) {
            std::cout << s.device << " at " << s.time << " -> " << s.action << std::endl;
        }
        std::cout << "-----------------" << std::endl;
    }

    void printSystemStatus() {
        std::cout << "\n--- Smart Home System Status ---" << std::endl;
        std::cout << "Current User: " << (currentUser.empty() ? "None" : currentUser) << std::endl;
        std::cout << "Lights On: ";
        for(auto const& [id, status] : lightsStatus) if(status) std::cout << id << " ";
        std::cout << "\nThermostat: " << thermostatTemp << " degrees" << std::endl;
        std::cout << "Security: " << (securityArmed ? "Armed" : "Disarmed") << std::endl;
        viewSchedules();
        std::cout << "------------------------------\n" << std::endl;
    }

private:
    struct Schedule { std::string device, time, action; };

    std::map<std::string, std::string> users;
    std::string currentUser;
    std::map<int, bool> lightsStatus;
    double thermostatTemp = 20.0;
    bool securityArmed = false;
    std::vector<Schedule> schedules;
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
    return 0;
}
