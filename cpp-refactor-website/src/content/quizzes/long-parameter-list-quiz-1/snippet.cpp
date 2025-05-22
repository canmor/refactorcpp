#include <iostream>
#include <string>

class ReportGenerator {
public:
    void generateSalesReport(
        const std::string& startDate, 
        const std::string& endDate, 
        const std::string& region, 
        const std::string& productCategory, 
        bool includeVAT, 
        double taxRate, 
        bool groupByProduct, 
        bool groupByRegion, 
        const std::string& currencyFormat, 
        const std::string& outputFormat, 
        bool includeCharts
    ) {
        std::cout << "Generating sales report from " << startDate << " to " << endDate << "\n";
        std::cout << "Region: " << region << "\n";
        std::cout << "Product Category: " << productCategory << "\n";
        
        double totalSales = calculateSales(startDate, endDate, region, productCategory);
        
        if (includeVAT) {
            totalSales += totalSales * (taxRate / 100.0);
        }
        
        std::cout << "Total Sales (" << currencyFormat << "): " << totalSales << "\n";
        
        if (groupByProduct) {
            generateProductBreakdown(startDate, endDate, region, productCategory);
        }
        
        if (groupByRegion) {
            generateRegionBreakdown(startDate, endDate, productCategory);
        }
        
        if (includeCharts) {
            generateChart(outputFormat, startDate, endDate, region);
        }
    }

private:
    double calculateSales(const std::string& startDate, const std::string& endDate, 
                          const std::string& region, const std::string& productCategory) {
        // Simulation of sales calculation
        return 12345.67;
    }
    
    void generateProductBreakdown(const std::string& startDate, const std::string& endDate,
                                 const std::string& region, const std::string& productCategory) {
        std::cout << "Product breakdown...\n";
    }
    
    void generateRegionBreakdown(const std::string& startDate, const std::string& endDate,
                                const std::string& productCategory) {
        std::cout << "Region breakdown...\n";
    }
    
    void generateChart(const std::string& chartType, const std::string& startDate,
                      const std::string& endDate, const std::string& region) {
        std::cout << "Generating " << chartType << " chart...\n";
    }
};

// Example of a function with another long parameter list
void processCustomerData(
    const std::string& customerId,
    const std::string& firstName, 
    const std::string& lastName,
    const std::string& email,
    const std::string& phone,
    const std::string& addressLine1,
    const std::string& addressLine2,
    const std::string& city,
    const std::string& state,
    const std::string& zipCode,
    const std::string& country,
    bool isVIP,
    double creditLimit
) {
    std::cout << "Processing data for customer " << customerId << "\n";
    std::cout << "Name: " << firstName << " " << lastName << "\n";
    std::cout << "Contact: " << email << ", " << phone << "\n";
    std::cout << "Address: " << addressLine1;
    if (!addressLine2.empty()) std::cout << ", " << addressLine2;
    std::cout << ", " << city << ", " << state << " " << zipCode << ", " << country << "\n";
    std::cout << "VIP Status: " << (isVIP ? "Yes" : "No") << "\n";
    std::cout << "Credit Limit: " << creditLimit << "\n";
}

int main() {
    ReportGenerator generator;
    
    generator.generateSalesReport(
        "2025-01-01", "2025-03-31", "North America", "Electronics", 
        true, 7.5, true, true, "USD", "bar", true
    );
    
    processCustomerData(
        "C12345", "John", "Doe", "john@example.com", "555-1234",
        "123 Main St", "Apt 4B", "Anytown", "CA", "12345", "USA",
        true, 5000.0
    );
    
    return 0;
}
