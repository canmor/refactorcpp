#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class FinancialReport {
private:
    std::string companyName;
    int fiscalYear;
    double revenue;
    double expenses;
    
    // Fields used only during tax calculation
    double depreciationRate;
    double taxableAssets;
    double overseasIncome;
    double previousYearLosses;
    
    // Fields used only during annual report generation
    std::vector<std::string> departmentNames;
    std::vector<double> departmentExpenses;
    std::string ceoStatement;
    std::string auditorOpinion;

public:
    FinancialReport(const std::string& name, int year, double rev, double exp)
        : companyName(name), fiscalYear(year), revenue(rev), expenses(exp),
          depreciationRate(0.0), taxableAssets(0.0), overseasIncome(0.0),
          previousYearLosses(0.0) {}
    
    double calculateNetIncome() const {
        return revenue - expenses;
    }
    
    double calculateTaxes() {
        // Initializing variables needed for tax calculation
        depreciationRate = 0.1;  // 10% annual depreciation
        taxableAssets = 5000000.0;
        overseasIncome = revenue * 0.3;  // 30% of revenue is from overseas
        previousYearLosses = 200000.0;
        
        // Calculate taxable income
        double taxableIncome = revenue - expenses;
        
        // Apply depreciation
        double depreciationDeduction = taxableAssets * depreciationRate;
        taxableIncome -= depreciationDeduction;
        
        // Deduct previous year losses if applicable
        if (previousYearLosses > 0) {
            taxableIncome -= previousYearLosses;
        }
        
        // Calculate tax (simplified)
        double taxRate = 0.25;
        return taxableIncome * taxRate;
    }
    
    void generateAnnualReport() {
        // Initialize fields needed for annual report
        departmentNames = {"Sales", "Marketing", "R&D", "Administration", "Production"};
        departmentExpenses = {expenses * 0.2, expenses * 0.15, expenses * 0.3, expenses * 0.1, expenses * 0.25};
        ceoStatement = "Our company had a strong financial performance this year.";
        auditorOpinion = "The financial statements present fairly, in all material respects.";
        
        std::cout << "ANNUAL REPORT FOR " << companyName << " - FISCAL YEAR " << fiscalYear << std::endl;
        std::cout << "========================================================" << std::endl;
        std::cout << "Total Revenue: $" << revenue << std::endl;
        std::cout << "Total Expenses: $" << expenses << std::endl;
        std::cout << "Net Income: $" << calculateNetIncome() << std::endl;
        
        std::cout << "CEO STATEMENT: " << ceoStatement << std::endl;
        
        std::cout << "DEPARTMENTAL BREAKDOWN" << std::endl;
        for (size_t i = 0; i < departmentNames.size(); i++) {
            std::cout << departmentNames[i] << ": Expenses $" << departmentExpenses[i] << std::endl;
        }
        
        std::cout << "AUDITOR OPINION: " << auditorOpinion << std::endl;
    }
    
    void displayBasicInfo() {
        std::cout << "Company: " << companyName << std::endl;
        std::cout << "Fiscal Year: " << fiscalYear << std::endl;
        std::cout << "Revenue: $" << revenue << std::endl;
        std::cout << "Expenses: $" << expenses << std::endl;
    }
};

int main() {
    FinancialReport report("TechCorp", 2025, 15000000.0, 12000000.0);
    
    report.displayBasicInfo();
    std::cout << "Taxes: $" << report.calculateTaxes() << std::endl;
    report.generateAnnualReport();
    
    return 0;
}

int main() {
    FinancialReport report("TechCorp Inc.", 2025, 15000000.0, 12000000.0);
    
    // Display basic information
    report.displayBasicInfo();
    std::cout << std::endl;
    
    // Calculate and display taxes
    double taxes = report.calculateTaxes();
    std::cout << "Estimated Taxes: $" << std::fixed << std::setprecision(2) << taxes << std::endl;
    std::cout << std::endl;
    
    // Generate annual report
    report.generateAnnualReport();
    
    return 0;
}
