// after.cpp
#include <iostream>
#include <vector>
#include <string>
#include <numeric> // Required for std::accumulate

// Helper function to calculate subtotal
double calculateSubtotal(const std::vector<double>& prices, const std::vector<int>& quantities) {
    double subtotal = 0;
    for (size_t i = 0; i < prices.size(); ++i) {
        subtotal += prices[i] * quantities[i];
    }
    return subtotal;
}

// Helper function to apply discount
double applyDiscount(double amount, double discount) {
    return amount * (1 - discount);
}

// Helper function to apply tax
double applyTax(double amount, double taxRate) {
    return amount * (1 + taxRate);
}

// Helper function to log order details
void logOrderDetails(const std::string& customerName, const std::vector<double>& prices, const std::vector<int>& quantities, double subtotal, double discount, double discountedPrice, double taxRate, double totalAmount) {
    std::cout << "Order for customer: " << customerName << std::endl;
    for (size_t i = 0; i < prices.size(); ++i) {
        std::cout << " - Item " << (i + 1) << ": Price $" << prices[i] << ", Quantity " << quantities[i] << std::endl;
    }
    std::cout << "Subtotal: $" << subtotal << std::endl;
    std::cout << "Discount applied: " << (discount * 100) << "%" << std::endl;
    std::cout << "Price after discount: $" << discountedPrice << std::endl;
    std::cout << "Tax applied: " << (taxRate * 100) << "%" << std::endl;
    std::cout << "Total amount: $" << totalAmount << std::endl;
}

void processOrderRefactored(const std::vector<double>& prices, const std::vector<int>& quantities, double discount, double taxRate, const std::string& customerName) {
    if (prices.empty() || quantities.empty() || prices.size() != quantities.size()) {
        std::cerr << "Error: Invalid input for order processing." << std::endl;
        return;
    }

    double subtotal = calculateSubtotal(prices, quantities);
    double discountedPrice = applyDiscount(subtotal, discount);
    double totalAmount = applyTax(discountedPrice, taxRate);
    
    logOrderDetails(customerName, prices, quantities, subtotal, discount, discountedPrice, taxRate, totalAmount);
    
    // Further steps (payment, inventory, notifications) would also be extracted into their own functions.
    std::cout << "Order processed successfully for " << customerName << "." << std::endl;
}

int main() {
    std::vector<double> prices = {10.0, 20.0, 5.0};
    std::vector<int> quantities = {2, 1, 5};
    processOrderRefactored(prices, quantities, 0.1, 0.07, "Jane Doe");
    return 0;
}
