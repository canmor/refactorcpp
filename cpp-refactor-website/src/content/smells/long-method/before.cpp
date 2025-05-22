// before.cpp
#include <iostream>
#include <vector>
#include <string>
#include <numeric> // Required for std::accumulate

void processOrder(const std::vector<double>& prices, const std::vector<int>& quantities, double discount, double taxRate, const std::string& customerName) {
    if (prices.empty() || quantities.empty() || prices.size() != quantities.size()) {
        std::cerr << "Error: Invalid input for order processing." << std::endl;
        return;
    }

    double subtotal = 0;
    for (size_t i = 0; i < prices.size(); ++i) {
        subtotal += prices[i] * quantities[i];
    }
    
    // Apply discount
    double discountedPrice = subtotal * (1 - discount);
    
    // Add tax
    double totalAmount = discountedPrice * (1 + taxRate);
    
    // Log order
    std::cout << "Order for customer: " << customerName << std::endl;
    for (size_t i = 0; i < prices.size(); ++i) {
        std::cout << " - Item " << (i + 1) << ": Price $" << prices[i] << ", Quantity " << quantities[i] << std::endl;
    }
    std::cout << "Subtotal: $" << subtotal << std::endl;
    std::cout << "Discount applied: " << (discount * 100) << "%" << std::endl;
    std::cout << "Price after discount: $" << discountedPrice << std::endl;
    std::cout << "Tax applied: " << (taxRate * 100) << "%" << std::endl;
    std::cout << "Total amount: $" << totalAmount << std::endl;
    
    // Imagine more steps here: payment processing, inventory update, notification sending etc.
    // Making this function very long.
    std::cout << "Order processed successfully for " << customerName << "." << std::endl;
}

int main() {
    std::vector<double> prices = {10.0, 20.0, 5.0};
    std::vector<int> quantities = {2, 1, 5};
    processOrder(prices, quantities, 0.1, 0.07, "John Doe");
    return 0;
}
