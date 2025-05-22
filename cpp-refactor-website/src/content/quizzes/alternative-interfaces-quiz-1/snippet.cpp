#include <iostream>
#include <string>
#include <vector>

// First authentication handler class
class UserAuthenticator {
public:
    UserAuthenticator() {}
    
    bool validateCredentials(const std::string& username, const std::string& password) {
        // Simulate checking credentials in a database
        std::cout << "UserAuthenticator: Validating credentials for user " << username << std::endl;
        
        // For demonstration, consider some hardcoded valid credentials
        if (username == "admin" && password == "admin123") {
            return true;
        }
        return false;
    }
    
    std::string generateSessionToken(const std::string& username) {
        // Generate a unique session token for the user
        std::cout << "UserAuthenticator: Generating token for user " << username << std::endl;
        return "UA-TOKEN-" + username + "-" + std::to_string(time(nullptr));
    }
    
    bool checkPermission(const std::string& username, const std::string& resource) {
        std::cout << "UserAuthenticator: Checking if " << username << " has access to " << resource << std::endl;
        // Simplified permission check
        return username == "admin";
    }
};

// Second authentication handler class (developed separately)
class LoginManager {
public:
    LoginManager() {}
    
    bool verifyUser(const std::string& user, const std::string& pwd) {
        // Authenticate user against stored credentials
        std::cout << "LoginManager: Verifying user " << user << std::endl;
        
        // For demonstration, consider the same hardcoded valid credentials
        if (user == "admin" && pwd == "admin123") {
            return true;
        }
        return false;
    }
    
    std::string createSession(const std::string& user) {
        // Create a new session for the user
        std::cout << "LoginManager: Creating session for user " << user << std::endl;
        return "LM-SESSION-" + user + "-" + std::to_string(time(nullptr));
    }
    
    bool hasAccess(const std::string& user, const std::string& resource) {
        std::cout << "LoginManager: Checking if " << user << " has access to " << resource << std::endl;
        // Simplified permission check
        return user == "admin";
    }
};

// Class using the first authentication handler
class AdminPortal {
private:
    UserAuthenticator authenticator;
    std::string currentUser;
    std::string sessionToken;
    
public:
    bool login(const std::string& username, const std::string& password) {
        if (authenticator.validateCredentials(username, password)) {
            currentUser = username;
            sessionToken = authenticator.generateSessionToken(username);
            return true;
        }
        return false;
    }
    
    bool accessResource(const std::string& resource) {
        if (currentUser.empty() || sessionToken.empty()) {
            std::cout << "User not logged in!" << std::endl;
            return false;
        }
        
        return authenticator.checkPermission(currentUser, resource);
    }
};

// Class using the second authentication handler
class CustomerPortal {
private:
    LoginManager loginManager;
    std::string activeUser;
    std::string sessionId;
    
public:
    bool login(const std::string& username, const std::string& password) {
        if (loginManager.verifyUser(username, password)) {
            activeUser = username;
            sessionId = loginManager.createSession(username);
            return true;
        }
        return false;
    }
    
    bool accessResource(const std::string& resource) {
        if (activeUser.empty() || sessionId.empty()) {
            std::cout << "User not logged in!" << std::endl;
            return false;
        }
        
        return loginManager.hasAccess(activeUser, resource);
    }
};

int main() {
    AdminPortal adminPortal;
    CustomerPortal customerPortal;
    
    std::cout << "Admin Portal Login: " 
              << (adminPortal.login("admin", "admin123") ? "Success" : "Failure") << std::endl;
    
    std::cout << "Admin Portal Access: " 
              << (adminPortal.accessResource("analytics") ? "Granted" : "Denied") << std::endl;
    
    std::cout << "\n---------------------------\n" << std::endl;
    
    std::cout << "Customer Portal Login: " 
              << (customerPortal.login("admin", "admin123") ? "Success" : "Failure") << std::endl;
    
    std::cout << "Customer Portal Access: " 
              << (customerPortal.accessResource("analytics") ? "Granted" : "Denied") << std::endl;
    
    return 0;
}
