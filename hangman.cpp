#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

// Function to check if a character is present in the secret word
bool isCharPresent(char guess, const std::string& word) {
    for (char c : word) {
        if (c == guess) {
            return true;
        }
    }
    return false;
}

// Function to update the display string with correctly guessed characters
void updateDisplayString(char guess, const std::string& word, std::string& displayString) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (word[i] == guess) {
            displayString[i] = guess;
        }
    }
}

// Function to print the hangman figure based on the number of incorrect guesses
void printHangman(int incorrectGuesses) {
    std::vector<std::string> hangmanFigure = {
        "  +---+",
        "  |   |",
        "  O   |",
        " /|\\  |",
        " / \\  |",
        "      |",
        "========="
    };

    for (int i = 0; i <= incorrectGuesses; ++i) {
        std::cout << hangmanFigure[i] << std::endl;
    }
}

// Function to randomly pick a word from the specified word set
std::string pickRandomWord(const std::vector<std::string>& wordSet) {
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<int> dist(0, wordSet.size() - 1);
    return wordSet[dist(rng)];
}

int main() {
    std::vector<std::string> easyWords = {"cat", "dog", "sun", "moon", "tree", "bird", "fish", "book", "lamp", "rain", "fire", "rose", "ship", "star", "cake"};  // Set of easy words
    std::vector<std::string> mediumWords = {"jungle", "planet", "bridge", "puzzle", "castle", "ticket", "camera", "planet", "jacket", "artist", "summer", "flower", "garden", "pencil", "beauty"};  // Set of medium words
    std::vector<std::string> hardWords = {"fantastic","chocolate","butterfly","waterfall","beautiful","adventure","wonderful","pineapple","breathtaking","elephant","magnificent","fascinating","butterflies","extraordinary","captivating"};  // Set of hard words

    std::string difficulty;
    std::cout << "Welcome to Hangman! Choose a difficulty level (easy/medium/hard): ";
    std::cin >> difficulty;

    std::string secretWord;
    if (difficulty == "easy") {
        secretWord = pickRandomWord(easyWords);
    } else if (difficulty == "medium") {
        secretWord = pickRandomWord(mediumWords);
    } else if (difficulty == "hard") {
        secretWord = pickRandomWord(hardWords);
    } else {
        std::cout << "Invalid difficulty level. Exiting the game." << std::endl;
        return 0;
    }

    std::string displayString(secretWord.length(), '_');
    int maxIncorrectGuesses = 6;
    int incorrectGuesses = 0;
    std::vector<char> incorrectChars;

    std::cout << "Guess the word. Good luck!" << std::endl;

    while (incorrectGuesses < maxIncorrectGuesses) {
        std::cout << "Current word: " << displayString << std::endl;
        std::cout << "Incorrect guesses: ";
        for (char c : incorrectChars) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

        char guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        if (isCharPresent(guess, secretWord)) {
            updateDisplayString(guess, secretWord, displayString);
            if (displayString == secretWord) {
                std::cout << "Congratulations! You guessed the word: " << secretWord << std::endl;
                return 0;
            }
        } else {
            incorrectGuesses++;
            incorrectChars.push_back(guess);
            std::cout << "Incorrect guess." << std::endl;
            printHangman(incorrectGuesses);
        }
    }

    std::cout << "You lost! The word was: " << secretWord << std::endl;
    return 0;
}
