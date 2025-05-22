#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
        bool includeCharts, 
        const std::string& chartType, 
        int percentagePrecision, 
        bool includeRawData, 
        bool compareWithPrevPeriod) 
    {
        std::cout << "Generating sales report from " << startDate << " to " << endDate << "\n";
        std::cout << "Region: " << region << "\n";
        std::cout << "Product Category: " << productCategory << "\n";
        
        double totalSales = calculateSales(startDate, endDate, region, productCategory);
        
        if (includeVAT) {
            totalSales += totalSales * (taxRate / 100.0);
        }
        
        std::cout << "Total Sales (" << currencyFormat << "): ";
        
        if (outputFormat == "html") {
            std::cout << "<strong>" << std::fixed << std::setprecision(percentagePrecision) << totalSales << "</strong>\n";
        } else {
            std::cout << std::fixed << std::setprecision(percentagePrecision) << totalSales << "\n";
        }
        
        if (groupByProduct) {
            generateProductBreakdown(startDate, endDate, region, productCategory, currencyFormat, percentagePrecision);
        }
        
        if (groupByRegion) {
            generateRegionBreakdown(startDate, endDate, productCategory, currencyFormat, percentagePrecision);
        }
        
        if (includeCharts) {
            generateChart(chartType, startDate, endDate, region, productCategory);
        }
        
        if (includeRawData) {
            outputRawData(startDate, endDate, region, productCategory);
        }
        
        if (compareWithPrevPeriod) {
            compareSalesWithPreviousPeriod(startDate, endDate, region, productCategory, currencyFormat, percentagePrecision);
        }
    }

private:
    double calculateSales(const std::string& startDate, const std::string& endDate, 
                          const std::string& region, const std::string& productCategory) {
        // Simulation of sales calculation
        return 12345.67;
    }
    
    void generateProductBreakdown(const std::string& startDate, const std::string& endDate,
                                 const std::string& region, const std::string& productCategory,
                                 const std::string& currencyFormat, int percentagePrecision) {
        std::cout << "Product breakdown...\n";
        // Implementation details omitted for brevity
    }
    
    void generateRegionBreakdown(const std::string& startDate, const std::string& endDate,
                                const std::string& productCategory, const std::string& currencyFormat,
                                int percentagePrecision) {
        std::cout << "Region breakdown...\n";
        // Implementation details omitted for brevity
    }
    
    void generateChart(const std::string& chartType, const std::string& startDate,
                      const std::string& endDate, const std::string& region, 
                      const std::string& productCategory) {
        std::cout << "Generating " << chartType << " chart...\n";
        // Implementation details omitted for brevity
    }
    
    void outputRawData(const std::string& startDate, const std::string& endDate,
                      const std::string& region, const std::string& productCategory) {
        std::cout << "Outputting raw data...\n";
        // Implementation details omitted for brevity
    }
    
    void compareSalesWithPreviousPeriod(const std::string& startDate, const std::string& endDate,
                                       const std::string& region, const std::string& productCategory,
                                       const std::string& currencyFormat, int percentagePrecision) {
        std::cout << "Comparing with previous period...\n";
        // Implementation details omitted for brevity
    }
};

int main() {
    ReportGenerator generator;
    
    generator.generateSalesReport(
        "2025-01-01", "2025-03-31", "North America", "Electronics", 
        true, 7.5, true, true, "USD", "text", 
        true, "bar", 2, false, true
    );
    
    return 0;
}
