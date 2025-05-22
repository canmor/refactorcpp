// snippet.cpp
#include <iostream>
#include <vector>
#include <string>

void generateReport(const std::vector<int>& data, const std::string& reportName) {
    // Part 1: Calculate statistics
    double sum = 0;
    for (int val : data) {
        sum += val;
    }
    double average = data.empty() ? 0 : sum / data.size();

    // Part 2: Format the report header
    std::string reportContent = "Report: " + reportName + "\n";
    reportContent += "Generated on: 2024-07-28\n"; // Assume current date
    reportContent += "--------------------------\n";

    // Part 3: Add statistics to report
    reportContent += "Count: " + std::to_string(data.size()) + "\n";
    reportContent += "Sum: " + std::to_string(sum) + "\n";
    reportContent += "Average: " + std::to_string(average) + "\n";

    // Part 4: Print the report to console
    std::cout << reportContent << std::endl;

    // Part 5: (Imagine) Save report to a file
    // FILE* f = fopen((reportName + ".txt").c_str(), "w");
    // if (f) {
    //     fprintf(f, "%s", reportContent.c_str());
    //     fclose(f);
    // }
}
