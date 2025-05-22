// Product Management System with Primitive Obsession
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

class ProductSystem {
public:
    // Constants for product category types
    static const int CATEGORY_ELECTRONICS = 1;
    static const int CATEGORY_BOOKS = 2;
    static const int CATEGORY_CLOTHING = 3;
    static const int CATEGORY_FOOD = 4;
    
    // Constants for product status
    static const int STATUS_IN_STOCK = 10;
    static const int STATUS_LOW_STOCK = 20;
    static const int STATUS_OUT_OF_STOCK = 30;
    static const int STATUS_DISCONTINUED = 40;
    
    // Constants for shipping methods
    static const int SHIPPING_STANDARD = 1;
    static const int SHIPPING_EXPRESS = 2;
    static const int SHIPPING_OVERNIGHT = 3;
    
    // Constants used for array indexes
    static const std::string FIELD_ID;
    static const std::string FIELD_NAME;
    static const std::string FIELD_PRICE;
    static const std::string FIELD_CATEGORY;
    static const std::string FIELD_STATUS;
    static const std::string FIELD_WEIGHT;

private:
    // Products stored as maps of string->value where value could be string, int, or double
    std::vector<std::map<std::string, std::string>> products;

public:
    // Add a product using primitive types
    void addProduct(const std::string& id, const std::string& name, double price, 
                    int category, int status, double weight) {
        
        std::map<std::string, std::string> product;
        product[FIELD_ID] = id;
        product[FIELD_NAME] = name;
        product[FIELD_PRICE] = std::to_string(price);
        product[FIELD_CATEGORY] = std::to_string(category);
        product[FIELD_STATUS] = std::to_string(status);
        product[FIELD_WEIGHT] = std::to_string(weight);
        
        products.push_back(product);
    }
    
    // Get a product by ID
    std::map<std::string, std::string>* getProduct(const std::string& id) {
        for (auto& product : products) {
            if (product[FIELD_ID] == id) {
                return &product;
            }
        }
        return nullptr;
    }
    
    // Calculate shipping cost using primitive types
    double calculateShipping(const std::string& productId, int shippingMethod, std::string zipCode) {
        auto product = getProduct(productId);
        if (!product) {
            return 0.0;
        }
        
        double baseRate = 0.0;
        switch (shippingMethod) {
            case SHIPPING_STANDARD:
                baseRate = 5.99;
                break;
            case SHIPPING_EXPRESS:
                baseRate = 12.99;
                break;
            case SHIPPING_OVERNIGHT:
                baseRate = 24.99;
                break;
            default:
                return 0.0;
        }
        
        // Using primitives to represent weight and calculate shipping
        double weight = std::stod((*product)[FIELD_WEIGHT]);
        double additionalCost = weight > 5.0 ? (weight - 5.0) * 0.5 : 0.0;
        
        // Using primitives and string manipulation to determine shipping zone
        std::string zonePrefix = zipCode.substr(0, 1);
        double zoneMultiplier = 1.0;
        if (zonePrefix == "9") {
            zoneMultiplier = 1.2; // West coast
        } else if (zonePrefix == "0" || zonePrefix == "1") {
            zoneMultiplier = 1.1; // East coast
        }
        
        return (baseRate + additionalCost) * zoneMultiplier;
    }
    
    // Process an order with primitives for money, quantity, and discount
    void processOrder(const std::string& productId, int quantity, 
                      double discountPercent, bool isExpedited) {
        auto product = getProduct(productId);
        if (!product) {
            std::cout << "Product not found!" << std::endl;
            return;
        }
        
        // Convert price from string to double for calculations
        double price = std::stod((*product)[FIELD_PRICE]);
        double subtotal = price * quantity;
        
        // Apply discount
        double discount = subtotal * (discountPercent / 100.0);
        double total = subtotal - discount;
        
        // Add expedited fee
        if (isExpedited) {
            total += 15.0;
        }
        
        // Update inventory (represented as an integer in a string)
        int status = std::stoi((*product)[FIELD_STATUS]);
        if (status == STATUS_IN_STOCK && quantity > 10) {
            (*product)[FIELD_STATUS] = std::to_string(STATUS_LOW_STOCK);
        } else if (status == STATUS_LOW_STOCK) {
            (*product)[FIELD_STATUS] = std::to_string(STATUS_OUT_OF_STOCK);
        }
        
        // Print order summary
        std::cout << "Order Summary:" << std::endl;
        std::cout << "Product: " << (*product)[FIELD_NAME] << std::endl;
        std::cout << "Quantity: " << quantity << std::endl;
        std::cout << "Price per unit: $" << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "Subtotal: $" << std::fixed << std::setprecision(2) << subtotal << std::endl;
        std::cout << "Discount: $" << std::fixed << std::setprecision(2) << discount 
                  << " (" << discountPercent << "%)" << std::endl;
        if (isExpedited) {
            std::cout << "Expedited Fee: $15.00" << std::endl;
        }
        std::cout << "Total: $" << std::fixed << std::setprecision(2) << total << std::endl;
    }
    
    // Print product details
    void printProductDetails(const std::string& productId) {
        auto product = getProduct(productId);
        if (!product) {
            std::cout << "Product not found!" << std::endl;
            return;
        }
        
        std::cout << "Product Details:" << std::endl;
        std::cout << "ID: " << (*product)[FIELD_ID] << std::endl;
        std::cout << "Name: " << (*product)[FIELD_NAME] << std::endl;
        std::cout << "Price: $" << std::fixed << std::setprecision(2) 
                  << std::stod((*product)[FIELD_PRICE]) << std::endl;
        
        // Convert category code to string using primitives
        int category = std::stoi((*product)[FIELD_CATEGORY]);
        std::string categoryName;
        switch (category) {
            case CATEGORY_ELECTRONICS:
                categoryName = "Electronics";
                break;
            case CATEGORY_BOOKS:
                categoryName = "Books";
                break;
            case CATEGORY_CLOTHING:
                categoryName = "Clothing";
                break;
            case CATEGORY_FOOD:
                categoryName = "Food";
                break;
            default:
                categoryName = "Unknown";
        }
        std::cout << "Category: " << categoryName << std::endl;
        
        // Convert status code to string using primitives
        int status = std::stoi((*product)[FIELD_STATUS]);
        std::string statusName;
        switch (status) {
            case STATUS_IN_STOCK:
                statusName = "In Stock";
                break;
            case STATUS_LOW_STOCK:
                statusName = "Low Stock";
                break;
            case STATUS_OUT_OF_STOCK:
                statusName = "Out of Stock";
                break;
            case STATUS_DISCONTINUED:
                statusName = "Discontinued";
                break;
            default:
                statusName = "Unknown";
        }
        std::cout << "Status: " << statusName << std::endl;
        std::cout << "Weight: " << std::stod((*product)[FIELD_WEIGHT]) << " kg" << std::endl;
    }
};

// Static constants definitions
const std::string ProductSystem::FIELD_ID = "id";
const std::string ProductSystem::FIELD_NAME = "name";
const std::string ProductSystem::FIELD_PRICE = "price";
const std::string ProductSystem::FIELD_CATEGORY = "category";
const std::string ProductSystem::FIELD_STATUS = "status";
const std::string ProductSystem::FIELD_WEIGHT = "weight";

// Example usage
int main() {
    ProductSystem system;
    
    // Add products using primitive values
    system.addProduct("P001", "Smartphone", 699.99, 
                      ProductSystem::CATEGORY_ELECTRONICS,
                      ProductSystem::STATUS_IN_STOCK, 0.3);
                      
    system.addProduct("B001", "Programming C++ Book", 49.99,
                      ProductSystem::CATEGORY_BOOKS,
                      ProductSystem::STATUS_IN_STOCK, 1.2);
    
    // Display product details
    system.printProductDetails("P001");
    
    std::cout << "\n----------------\n" << std::endl;
    
    // Process an order
    system.processOrder("P001", 15, 10.0, true);
    
    std::cout << "\n----------------\n" << std::endl;
    
    // Calculate shipping
    double shippingCost = system.calculateShipping("B001", 
                                                  ProductSystem::SHIPPING_EXPRESS, 
                                                  "90210");
    std::cout << "Shipping Cost: $" << std::fixed << std::setprecision(2) << shippingCost << std::endl;
    
    return 0;
}
