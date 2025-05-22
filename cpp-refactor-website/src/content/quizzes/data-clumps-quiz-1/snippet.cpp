#include <iostream>
#include <string>

class OrderProcessor {
public:
    bool processOrder(
        int orderId,
        double totalAmount,
        const std::string& customerName,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode,
        const std::string& billingStreet,
        const std::string& billingCity,
        const std::string& billingState,
        const std::string& billingZipCode
    ) {
        std::cout << "Processing order " << orderId << " for " << customerName << std::endl;

        std::cout << "Shipping to: " << shippingStreet << ", " 
                  << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;

        std::cout << "Billing to: " << billingStreet << ", "
                  << billingCity << ", " << billingState << " " << billingZipCode << std::endl;

        return true;
    }

    void updateShippingAddress(
        int customerId,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode
    ) {
        std::cout << "Updating shipping address for customer " << customerId << std::endl;
        std::cout << "New shipping address: " << shippingStreet << ", " 
                  << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;
    }

    bool createCustomer(
        std::string name,
        std::string email,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode,
        const std::string& billingStreet,
        const std::string& billingCity,
        const std::string& billingState,
        const std::string& billingZipCode
    ) {
        std::cout << "Creating customer: " << name << " (" << email << ")" << std::endl;
        std::cout << "Default shipping: " << shippingStreet << ", " 
                  << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;
        std::cout << "Default billing: " << billingStreet << ", " 
                  << billingCity << ", " << billingState << " " << billingZipCode << std::endl;
        return true;
    }
};

class InventoryManager {
public:
    void addNewWarehouse(
        std::string name,
        const std::string& street,
        const std::string& city,
        const std::string& state,
        const std::string& zipCode,
        int capacity
    ) {
        std::cout << "Adding new warehouse: " << name << std::endl;
        std::cout << "Address: " << street << ", " << city << ", " << state << " " << zipCode << std::endl;
        std::cout << "Capacity: " << capacity << " units" << std::endl;
    }
};

int main() {
    OrderProcessor processor;
    
    // Process an order
    processor.processOrder(
        12345, 199.99, "John Doe",
        "123 Main St", "Anytown", "CA", "12345",
        "123 Main St", "Anytown", "CA", "12345"
    );
    
    // Update shipping address
    processor.updateShippingAddress(
        1001, "456 Oak Ave", "Somewhere", "NY", "54321"
    );
    
    // Create a new customer
    processor.createCustomer(
        "Jane Smith", "jane@example.com",
        "789 Pine Blvd", "Othertown", "TX", "67890",
        "789 Pine Blvd", "Othertown", "TX", "67890"
    );
    
    // Add a new warehouse
    InventoryManager inventory;
    inventory.addNewWarehouse(
        "Central Warehouse", "100 Storage Lane", "Centralville", "IL", "11111", 5000
    );
    
    return 0;
}
