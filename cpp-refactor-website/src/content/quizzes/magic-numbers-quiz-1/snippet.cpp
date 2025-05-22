// snippet.cpp
#include <iostream>

// Assuming this function is part of a larger system for resource management
// where resources are consumed or generated per second.
double calculateTotalDailyConsumption(double consumptionRatePerSecond) {
    // What does 86400 represent?
    double totalDaily = consumptionRatePerSecond * 86400; 
    return totalDaily;
}

int main() {
    double waterUsagePerSecond = 0.5; // e.g., liters per second
    double dailyWaterUsage = calculateTotalDailyConsumption(waterUsagePerSecond);
    std::cout << "Total daily water consumption: " << dailyWaterUsage << " liters." << std::endl;

    double energyGenerationPerSecond = 1.2; // e.g., kWh per second
    double dailyEnergyGeneration = calculateTotalDailyConsumption(energyGenerationPerSecond);
    std::cout << "Total daily energy generation: " << dailyEnergyGeneration << " kWh." << std::endl;
    
    return 0;
}
