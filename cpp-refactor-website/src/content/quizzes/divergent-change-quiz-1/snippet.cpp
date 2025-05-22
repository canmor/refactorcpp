#include <iostream>
#include <vector>
#include <string>
#include <map>

enum class PaymentType { CreditCard, BankTransfer, PayPal, Crypto };
enum class ShippingMethod { Standard, Express, Overnight };

class Product {
public:
    Product(int id, std::string name, double price) : id(id), name(name), price(price) {}
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }

private:
    int id;
    std::string name;
    double price;
};

// This class handles ordering, payment processing, inventory management, 
// shipping, notifications, and customer data management
class OrderManager {
public:
    OrderManager() {
        // Initialize some sample products
        inventory[1] = 10;  // 10 units of product 1
        inventory[2] = 15;  // 15 units of product 2
        inventory[3] = 8;   // 8 units of product 3
        
        productCatalog.push_back(Product(1, "Laptop", 1200.00));
        productCatalog.push_back(Product(2, "Smartphone", 800.00));
        productCatalog.push_back(Product(3, "Tablet", 500.00));
    }
    
    // Order processing methods
    int createOrder(int customerId, const std::vector<int>& productIds) {
        static int nextOrderId = 1001;
        int orderId = nextOrderId++;
        
        std::cout << "Creating order #" << orderId << " for customer #" << customerId << std::endl;
        
        orders[orderId] = productIds;
        orderCustomers[orderId] = customerId;
        
        for (int productId : productIds) {
            if (inventory[productId] > 0) {
                inventory[productId]--;
            } else {
                std::cout << "Warning: Product #" << productId << " is out of stock!" << std::endl;
            }
        }
        
        return orderId;
    }
    
    double calculateOrderTotal(int orderId) {
        double total = 0.0;
        
        for (int productId : orders[orderId]) {
            for (const auto& product : productCatalog) {
                if (product.getId() == productId) {
                    total += product.getPrice();
                    break;
                }
            }
        }
        
        return total;
    }
    
    void cancelOrder(int orderId) {
        std::cout << "Cancelling order #" << orderId << std::endl;
        
        // Return products to inventory
        for (int productId : orders[orderId]) {
            inventory[productId]++;
        }
        
        // Remove order records
        orders.erase(orderId);
        orderCustomers.erase(orderId);
        orderPayments.erase(orderId);
        orderShipping.erase(orderId);
    }
    
    // Payment processing methods
    void processPayment(int orderId, PaymentType paymentType, const std::string& paymentDetails) {
        double amount = calculateOrderTotal(orderId);
        
        std::cout << "Processing payment of $" << amount << " for order #" << orderId << std::endl;
        
        switch (paymentType) {
            case PaymentType::CreditCard:
                processCreditCardPayment(amount, paymentDetails);
                break;
            case PaymentType::BankTransfer:
                processBankTransferPayment(amount, paymentDetails);
                break;
            case PaymentType::PayPal:
                processPayPalPayment(amount, paymentDetails);
                break;
            case PaymentType::Crypto:
                processCryptoPayment(amount, paymentDetails);
                break;
        }
        
        orderPayments[orderId] = paymentType;
        
        // Update database records
        updatePaymentRecords(orderId, amount, paymentType);
        
        // Send payment notification
        sendPaymentConfirmation(orderId, amount);
    }
    
    // Shipping methods
    void arrangeShipping(int orderId, ShippingMethod method, const std::string& address) {
        std::cout << "Arranging shipping for order #" << orderId << " to: " << address << std::endl;
        
        switch (method) {
            case ShippingMethod::Standard:
                std::cout << "Standard shipping (3-5 business days)" << std::endl;
                break;
            case ShippingMethod::Express:
                std::cout << "Express shipping (2 business days)" << std::endl;
                break;
            case ShippingMethod::Overnight:
                std::cout << "Overnight shipping (next business day)" << std::endl;
                break;
        }
        
        orderShipping[orderId] = method;
        orderAddresses[orderId] = address;
        
        // Update shipping status in database
        updateShippingRecords(orderId, method);
        
        // Generate shipping label
        generateShippingLabel(orderId, address);
        
        // Notify warehouse
        notifyWarehouseForFulfillment(orderId);
    }
    
    // Customer management
    void addCustomer(int customerId, const std::string& name, const std::string& email) {
        customerNames[customerId] = name;
        customerEmails[customerId] = email;
        
        // Register customer in loyalty program
        registerCustomerForLoyalty(customerId);
        
        // Send welcome email
        sendWelcomeEmail(customerId);
    }
    
    void updateCustomerInfo(int customerId, const std::string& name, const std::string& email) {
        customerNames[customerId] = name;
        customerEmails[customerId] = email;
        
        // Update customer in database
        updateCustomerDatabase(customerId);
        
        // Sync changes with external systems
        syncCustomerWithCRM(customerId);
    }
    
    // Inventory management
    void addInventory(int productId, int quantity) {
        inventory[productId] += quantity;
        std::cout << "Added " << quantity << " units of product #" << productId << std::endl;
        
        // Update inventory database
        updateInventoryDatabase(productId);
        
        // Generate restock report
        if (isLowStock(productId)) {
            generateRestockAlert(productId);
        }
    }
    
    void displayProductInfo(int productId) {
        for (const auto& product : productCatalog) {
            if (product.getId() == productId) {
                std::cout << "Product #" << productId << ": " << product.getName() 
                         << " - $" << product.getPrice() << std::endl;
                std::cout << "In stock: " << inventory[productId] << " units" << std::endl;
                return;
            }
        }
        std::cout << "Product #" << productId << " not found!" << std::endl;
    }

private:
    // Helper methods for payment processing
    void processCreditCardPayment(double amount, const std::string& cardDetails) {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
    
    void processBankTransferPayment(double amount, const std::string& accountDetails) {
        std::cout << "Processing bank transfer of $" << amount << std::endl;
    }
    
    void processPayPalPayment(double amount, const std::string& paypalEmail) {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
    
    void processCryptoPayment(double amount, const std::string& walletAddress) {
        std::cout << "Processing cryptocurrency payment of $" << amount << std::endl;
    }
    
    // Database and notification methods
    void updatePaymentRecords(int orderId, double amount, PaymentType type) {
        std::cout << "Updating payment records in database..." << std::endl;
    }
    
    void sendPaymentConfirmation(int orderId, double amount) {
        int customerId = orderCustomers[orderId];
        std::string email = customerEmails[customerId];
        std::cout << "Sending payment confirmation to: " << email << std::endl;
    }
    
    void updateShippingRecords(int orderId, ShippingMethod method) {
        std::cout << "Updating shipping records in database..." << std::endl;
    }
    
    void generateShippingLabel(int orderId, const std::string& address) {
        std::cout << "Generating shipping label for order #" << orderId << std::endl;
    }
    
    void notifyWarehouseForFulfillment(int orderId) {
        std::cout << "Notifying warehouse to fulfill order #" << orderId << std::endl;
    }
    
    void registerCustomerForLoyalty(int customerId) {
        std::cout << "Registering customer #" << customerId << " for loyalty program" << std::endl;
    }
    
    void sendWelcomeEmail(int customerId) {
        std::cout << "Sending welcome email to: " << customerEmails[customerId] << std::endl;
    }
    
    void updateCustomerDatabase(int customerId) {
        std::cout << "Updating customer #" << customerId << " in database" << std::endl;
    }
    
    void syncCustomerWithCRM(int customerId) {
        std::cout << "Syncing customer #" << customerId << " with CRM system" << std::endl;
    }
    
    void updateInventoryDatabase(int productId) {
        std::cout << "Updating inventory database for product #" << productId << std::endl;
    }
    
    bool isLowStock(int productId) {
        return inventory[productId] < 5;  // Low stock threshold
    }
    
    void generateRestockAlert(int productId) {
        std::cout << "ALERT: Product #" << productId << " is low in stock!" << std::endl;
    }

    // Data storage
    std::map<int, std::vector<int>> orders;  // orderId -> productIds
    std::map<int, int> orderCustomers;       // orderId -> customerId
    std::map<int, PaymentType> orderPayments; // orderId -> paymentType
    std::map<int, ShippingMethod> orderShipping; // orderId -> shippingMethod
    std::map<int, std::string> orderAddresses; // orderId -> shippingAddress
    
    std::map<int, std::string> customerNames; // customerId -> name
    std::map<int, std::string> customerEmails; // customerId -> email
    
    std::map<int, int> inventory;  // productId -> quantity
    std::vector<Product> productCatalog;
};

int main() {
    OrderManager manager;
    
    // Add a customer
    manager.addCustomer(101, "Jane Smith", "jane@example.com");
    
    // Create an order
    std::vector<int> productIds = {1, 3};
    int orderId = manager.createOrder(101, productIds);
    
    // Process payment
    manager.processPayment(orderId, PaymentType::CreditCard, "4111-1111-1111-1111");
    
    // Arrange shipping
    manager.arrangeShipping(orderId, ShippingMethod::Express, "123 Main St, Anytown, USA");
    
    // Display product info
    manager.displayProductInfo(1);
    
    return 0;
}
