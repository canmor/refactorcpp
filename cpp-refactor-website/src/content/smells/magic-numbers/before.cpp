// before.cpp
#include <iostream>
#include <vector>
#include <cmath> // For std::pow

double calculateCircleArea(double radius) {
    return 3.14159 * radius * radius; // Magic number for Pi
}

double calculateRectangleArea(double width, double height) {
    return width * height;
}

void processScores(const std::vector<int>& scores) {
    int highScore = 0;
    int lowScore = 101; // Magic number, assumes scores are 0-100

    for (int score : scores) {
        if (score > highScore) highScore = score;
        if (score < lowScore) lowScore = score;
    }
    std::cout << "High score: " << highScore << std::endl;
    std::cout << "Low score: " << lowScore << std::endl;

    if (scores.size() > 10) { // Magic number for max displayable scores
        std::cout << "More than 10 scores, summary only." << std::endl;
    }
}

double calculateLoanInterest(double principal, double years) {
    // Magic number for annual interest rate (e.g., 5%)
    return principal * std::pow((1 + 0.05), years) - principal;
}

int main() {
    std::cout << "Area of circle with radius 5: " << calculateCircleArea(5.0) << std::endl;
    
    std::vector<int> gameScores = {75, 88, 92, 60, 100, 85, 79, 95, 89, 91, 72, 83};
    processScores(gameScores);

    std::cout << "Interest for $1000 over 3 years: $" << calculateLoanInterest(1000, 3) << std::endl;

    // Example with game states, where 0=Running, 1=Paused, 2=GameOver
    int gameState = 2; // Magic number for game state
    if (gameState == 0) {
        std::cout << "Game is Running." << std::endl;
    } else if (gameState == 1) {
        std::cout << "Game is Paused." << std::endl;
    } else if (gameState == 2) {
        std::cout << "Game Over." << std::endl;
    }
    return 0;
}
