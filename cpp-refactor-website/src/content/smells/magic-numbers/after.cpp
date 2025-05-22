// after.cpp
#include <iostream>
#include <vector>
#include <cmath> // For std::pow
#include <limits> // For std::numeric_limits

// Named constant for Pi
const double PI = 3.141592653589793;

double calculateCircleAreaRefactored(double radius) {
    return PI * radius * radius;
}

double calculateRectangleAreaRefactored(double width, double height) {
    return width * height;
}

// Constants for score processing
const int MAX_POSSIBLE_SCORE = 100;
const int MIN_POSSIBLE_SCORE = 0; // Assuming scores cannot be negative
const size_t MAX_SCORES_TO_DISPLAY_INDIVIDUALLY = 10;

void processScoresRefactored(const std::vector<int>& scores) {
    int highScore = MIN_POSSIBLE_SCORE; 
    int lowScore = MAX_POSSIBLE_SCORE; 

    if (scores.empty()) {
        std::cout << "No scores to process." << std::endl;
        return;
    }

    for (int score : scores) {
        if (score > highScore) highScore = score;
        if (score < lowScore) lowScore = score;
    }
    std::cout << "High score: " << highScore << std::endl;
    std::cout << "Low score: " << lowScore << std::endl;

    if (scores.size() > MAX_SCORES_TO_DISPLAY_INDIVIDUALLY) {
        std::cout << "More than " << MAX_SCORES_TO_DISPLAY_INDIVIDUALLY 
                  << " scores, summary only." << std::endl;
    }
}

// Constant for annual interest rate
const double ANNUAL_INTEREST_RATE = 0.05; // 5%

double calculateLoanInterestRefactored(double principal, double years) {
    return principal * std::pow((1 + ANNUAL_INTEREST_RATE), years) - principal;
}

// Enum for game states
enum class GameState {
    Running,
    Paused,
    GameOver
};

void printGameState(GameState state) {
    switch (state) {
        case GameState::Running:
            std::cout << "Game is Running." << std::endl;
            break;
        case GameState::Paused:
            std::cout << "Game is Paused." << std::endl;
            break;
        case GameState::GameOver:
            std::cout << "Game Over." << std::endl;
            break;
        default:
            std::cout << "Unknown game state." << std::endl;
            break;
    }
}


int main() {
    std::cout << "Area of circle with radius 5: " << calculateCircleAreaRefactored(5.0) << std::endl;
    
    std::vector<int> gameScores = {75, 88, 92, 60, 100, 85, 79, 95, 89, 91, 72, 83};
    processScoresRefactored(gameScores);
    std::vector<int> emptyScores;
    processScoresRefactored(emptyScores);


    std::cout << "Interest for $1000 over 3 years: $" << calculateLoanInterestRefactored(1000, 3) << std::endl;

    GameState currentGameState = GameState::GameOver;
    printGameState(currentGameState);
    
    currentGameState = GameState::Running;
    printGameState(currentGameState);

    return 0;
}
