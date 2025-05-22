#include <iostream>
#include <string>
#include <vector>
#include <memory>

class OrderProcessor {
private:
    void logTransaction(
        const std::string& transactionId, 
        const std::string& timestamp,
        const std::string& userId
    ) {
        std::cout << "Logging transaction: " << transactionId 
                  << " at " << timestamp 
                  << " by user: " << userId << std::endl;
    }

public:
    bool processOrder(
        int orderId,
        double totalAmount,
        const std::string& customerName,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode,
        const std::string& shippingCountry,
        const std::string& billingStreet,
        const std::string& billingCity,
        const std::string& billingState,
        const std::string& billingZipCode,
        const std::string& billingCountry
    ) {
        std::cout << "Processing order " << orderId << " for " << customerName << std::endl;
        std::cout << "Amount: $" << totalAmount << std::endl;

        std::cout << "Shipping to: " << std::endl;
        std::cout << shippingStreet << std::endl;
        std::cout << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;
        std::cout << shippingCountry << std::endl;

        std::cout << "Billing address: " << std::endl;
        std::cout << billingStreet << std::endl;
        std::cout << billingCity << ", " << billingState << " " << billingZipCode << std::endl;
        std::cout << billingCountry << std::endl;

        return true;
    }

    void updateShippingAddress(
        int customerId,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode,
        const std::string& shippingCountry
    ) {
        std::cout << "Updating shipping address for customer " << customerId << std::endl;
        std::cout << "New shipping address: " << std::endl;
        std::cout << shippingStreet << std::endl;
        std::cout << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;
        std::cout << shippingCountry << std::endl;
    }

    void updateBillingAddress(
        int customerId,
        const std::string& billingStreet,
        const std::string& billingCity,
        const std::string& billingState,
        const std::string& billingZipCode,
        const std::string& billingCountry
    ) {
        std::cout << "Updating billing address for customer " << customerId << std::endl;
        std::cout << "New billing address: " << std::endl;
        std::cout << billingStreet << std::endl;
        std::cout << billingCity << ", " << billingState << " " << billingZipCode << std::endl;
        std::cout << billingCountry << std::endl;
    }

    bool createCustomer(
        std::string name,
        std::string email,
        const std::string& shippingStreet,
        const std::string& shippingCity,
        const std::string& shippingState,
        const std::string& shippingZipCode,
        const std::string& shippingCountry,
        const std::string& billingStreet,
        const std::string& billingCity,
        const std::string& billingState,
        const std::string& billingZipCode,
        const std::string& billingCountry
    ) {
        std::string transactionId = "CUST" + std::to_string(rand() % 10000);
        std::string timestamp = "2025-05-22T07:10:00Z";
        std::string userId = "SYSTEM";
        
        logTransaction(transactionId, timestamp, userId);
        
        std::cout << "Creating customer: " << name << " (" << email << ")" << std::endl;
        std::cout << "Default shipping address: " << std::endl;
        std::cout << shippingStreet << std::endl;
        std::cout << shippingCity << ", " << shippingState << " " << shippingZipCode << std::endl;
        std::cout << shippingCountry << std::endl;

        std::cout << "Default billing address: " << std::endl;
        std::cout << billingStreet << std::endl;
        std::cout << billingCity << ", " << billingState << " " << billingZipCode << std::endl;
        std::cout << billingCountry << std::endl;
        
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
        const std::string& country,
        int capacity
    ) {
        std::cout << "Adding new warehouse: " << name << std::endl;
        std::cout << "Address: " << std::endl;
        std::cout << street << std::endl;
        std::cout << city << ", " << state << " " << zipCode << std::endl;
        std::cout << country << std::endl;
        std::cout << "Capacity: " << capacity << " units" << std::endl;
    }
};

int main() {
    OrderProcessor processor;
    
    // Process an order
    processor.processOrder(
        12345, 199.99, "John Doe",
        "123 Main St", "Anytown", "CA", "12345", "USA",
        "123 Main St", "Anytown", "CA", "12345", "USA"
    );
    
    // Update shipping address
    processor.updateShippingAddress(
        1001, "456 Oak Ave", "Somewhere", "NY", "54321", "USA"
    );
    
    // Create a new customer
    processor.createCustomer(
        "Jane Smith", "jane@example.com",
        "789 Pine Blvd", "Othertown", "TX", "67890", "USA",
        "789 Pine Blvd", "Othertown", "TX", "67890", "USA"
    );
    
    // Add a new warehouse
    InventoryManager inventory;
    inventory.addNewWarehouse(
        "Central Warehouse", "100 Storage Lane", "Centralville", "IL", "11111", "USA", 5000
    );
    
    return 0;
}
