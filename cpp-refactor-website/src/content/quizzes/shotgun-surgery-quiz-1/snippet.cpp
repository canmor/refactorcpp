#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Customer information
class Customer {
public:
    Customer(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email), loyaltyPoints(0) {}
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getLoyaltyPoints() const { return loyaltyPoints; }
    void addLoyaltyPoints(int points) { loyaltyPoints += points; }

private:
    int id;
    std::string name;
    std::string email;
    int loyaltyPoints;
};

// Product with pricing information
class Product {
public:
    Product(int id, const std::string& name, double price)
        : id(id), name(name), price(price) {}
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    
    double getPrice() const { return price; }
    void setPrice(double newPrice) { price = newPrice; }
    
    // Calculate price for a specific customer
    double getPriceForCustomer(const Customer& customer) const {
        // Apply loyalty discount: 1% off for every 100 points
        double discount = (customer.getLoyaltyPoints() / 100) * 0.01;
        if (discount > 0.2) discount = 0.2; // Max 20% discount
        
        return price * (1.0 - discount);
    }

private:
    int id;
    std::string name;
    double price;
};

// Order that contains products for a customer
class Order {
public:
    Order(int id, const Customer& customer)
        : id(id), customer(customer) {}
    
    void addItem(const Product& product, int quantity) {
        items.push_back({product, quantity});
        // Add loyalty points: 1 point per dollar spent
        int pointsEarned = static_cast<int>(product.getPriceForCustomer(customer) * quantity);
        const_cast<Customer&>(customer).addLoyaltyPoints(pointsEarned);
    }
    
    double getTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.product.getPriceForCustomer(customer) * item.quantity;
        }
        return total;
    }
    
    void printOrderSummary() const {
        std::cout << "Order #" << id << " for " << customer.getName() << "\n";
        std::cout << "----------------------------------------\n";
        
        for (const auto& item : items) {
            double itemPrice = item.product.getPriceForCustomer(customer);
            std::cout << item.product.getName() 
                      << " x" << item.quantity 
                      << " @ $" << itemPrice
                      << " = $" << (itemPrice * item.quantity) << "\n";
        }
        
        std::cout << "----------------------------------------\n";
        std::cout << "Total: $" << getTotal() << "\n";
        std::cout << "Customer earned " 
                  << customer.getLoyaltyPoints() << " loyalty points\n";
    }

private:
    struct OrderItem {
        Product product;
        int quantity;
    };
    
    int id;
    Customer customer;
    std::vector<OrderItem> items;
};

// Email notification service
class EmailService {
public:
    void sendOrderConfirmation(const Order& order, const Customer& customer) {
        std::cout << "Sending order confirmation to " << customer.getEmail() << "\n";
        std::cout << "Your order total is $" << order.getTotal() << "\n";
        std::cout << "You have earned " << customer.getLoyaltyPoints() << " loyalty points\n";
    }
    
    void sendLoyaltyUpdate(const Customer& customer) {
        std::cout << "Sending loyalty program update to " << customer.getEmail() << "\n";
        std::cout << "Your current loyalty points balance is " 
                  << customer.getLoyaltyPoints() << " points\n";
        
        // Calculate their tier
        std::string tier = "Standard";
        if (customer.getLoyaltyPoints() >= 5000) tier = "Platinum";
        else if (customer.getLoyaltyPoints() >= 1000) tier = "Gold";
        else if (customer.getLoyaltyPoints() >= 500) tier = "Silver";
        
        std::cout << "Your current tier is: " << tier << "\n";
    }
};

// Analytics service for business reporting
class AnalyticsService {
public:
    void trackPurchase(const Order& order, const Customer& customer) {
        std::cout << "Recording purchase analytics:\n";
        std::cout << "Customer #" << customer.getId() 
                  << " completed order worth $" << order.getTotal() << "\n";
        std::cout << "Customer loyalty tier: ";
        
        // Calculate their tier
        if (customer.getLoyaltyPoints() >= 5000) std::cout << "Platinum\n";
        else if (customer.getLoyaltyPoints() >= 1000) std::cout << "Gold\n";
        else if (customer.getLoyaltyPoints() >= 500) std::cout << "Silver\n";
        else std::cout << "Standard\n";
    }
    
    void generateLoyaltyReport() {
        std::cout << "Generating loyalty program effectiveness report\n";
        // Complex reporting code that uses hard-coded tier thresholds
        // 500 for Silver, 1000 for Gold, 5000 for Platinum
    }
};

// Customer support service
class CustomerSupportService {
public:
    void displayCustomerInfo(const Customer& customer) {
        std::cout << "Customer Information:\n";
        std::cout << "ID: " << customer.getId() << "\n";
        std::cout << "Name: " << customer.getName() << "\n";
        std::cout << "Email: " << customer.getEmail() << "\n";
        std::cout << "Loyalty Points: " << customer.getLoyaltyPoints() << "\n";
        std::cout << "Loyalty Tier: ";
        
        // Calculate their tier
        if (customer.getLoyaltyPoints() >= 5000) std::cout << "Platinum\n";
        else if (customer.getLoyaltyPoints() >= 1000) std::cout << "Gold\n";
        else if (customer.getLoyaltyPoints() >= 500) std::cout << "Silver\n";
        else std::cout << "Standard\n";
    }
    
    void processRefund(Order& order, const Customer& customer) {
        std::cout << "Processing refund for order #" << &order << "\n";
        std::cout << "Customer " << customer.getName() 
                  << " will lose " << customer.getLoyaltyPoints() << " points\n";
        
        // Determine priority based on tier
        std::string priority = "Normal";
        if (customer.getLoyaltyPoints() >= 5000) priority = "Highest";
        else if (customer.getLoyaltyPoints() >= 1000) priority = "High";
        else if (customer.getLoyaltyPoints() >= 500) priority = "Medium";
        
        std::cout << "Refund priority: " << priority << "\n";
    }
};

// Marketing campaign service
class MarketingService {
public:
    void sendPromotionalEmail(const Customer& customer) {
        std::cout << "Planning promotional email for " << customer.getEmail() << "\n";
        
        // Determine offers based on tier
        std::cout << "Offers to include: ";
        if (customer.getLoyaltyPoints() >= 5000) {
            std::cout << "Platinum exclusive offers, VIP event invitations\n";
        }
        else if (customer.getLoyaltyPoints() >= 1000) {
            std::cout << "Gold member offers, free shipping\n";
        }
        else if (customer.getLoyaltyPoints() >= 500) {
            std::cout << "Silver member offers\n";
        }
        else {
            std::cout << "Standard offers, loyalty program invitation\n";
        }
    }
};

int main() {
    // Create a customer
    Customer john(101, "John Smith", "john@example.com");
    
    // Create some products
    Product laptop(1, "Laptop", 1200.0);
    Product headphones(2, "Headphones", 100.0);
    
    // Create an order
    Order order(1001, john);
    order.addItem(laptop, 1);
    order.addItem(headphones, 2);
    
    // Print the order summary
    order.printOrderSummary();
    
    // Various services interacting with the customer
    EmailService emailService;
    emailService.sendOrderConfirmation(order, john);
    emailService.sendLoyaltyUpdate(john);
    
    AnalyticsService analyticsService;
    analyticsService.trackPurchase(order, john);
    
    CustomerSupportService supportService;
    supportService.displayCustomerInfo(john);
    
    MarketingService marketingService;
    marketingService.sendPromotionalEmail(john);
    
    return 0;
}
