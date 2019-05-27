#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText getValidGuess();
bool PlayAgain();
FBullCowGame BCGame;
void PrintGameSummary();

int main() {
	do {
		PrintIntro();
		PlayGame();
	} while (PlayAgain());
	return 0;
}

void PrintIntro() {
	//Introduces the game
	int32 length = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows!\nThe isogram has " << length << " letters, can you figure it out?\n";
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Runs the game for multiple turns
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < BCGame.GetMaxTries()) {
		FText Guess = getValidGuess();
		std::cout << "You Guessed: " << Guess << "\n";
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << "\nCows = " << BullCowCount.Cows << "\n";
	}
	PrintGameSummary();
}
FText getValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		//Get Guess from the user
		std::cout << "Try #" << CurrentTry << "\nPlease Enter Your Guess:";
		std::getline(std::cin, Guess);
		Status = BCGame.IsValidGuess(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a Word With " << BCGame.GetHiddenWordLength() << " Letters\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please Enter an Isogram (No Repeating Letters)\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please Enter Word in Lowercase Letters\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, You've Won!\n";
	}
	else {
		std::cout << "Better Luck Next Time\n";
	}
}

bool PlayAgain() {
	std::cout << "Game Over, Would You Like To Play Again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}