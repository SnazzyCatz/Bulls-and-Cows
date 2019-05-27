#pragma once
#include "FBullCowGame.h"
#include <map>
#include <time.h>
#define TMap std::map
using int32 = int;

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;

	const FString HIDDEN_WORD = RandomWord();
	HiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;
}

FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetMaxTries() const {
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	int32 WordLength = HiddenWord.length();
	return WordLength;
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = HiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) {
		for (int32 j = 0; j < HiddenWordLength; j++) {
			if (Guess[j] == HiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::IsValidGuess(FString guess) const {
	if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!isAllLower(guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::isIsogram(FString guess) const {
	if (guess.length() <= 1) {
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::isAllLower(FString guess) const {
	for (auto Letter : guess) {
		if (isupper(Letter)) {
			return false;
		}
	}
	return true;
}

FString FBullCowGame::RandomWord() {
	srand(time(NULL));
	FString WordList[10] = { "cat", "smah", "leagu", "dank", "doger", "witer", "loha", "gym", "gainz", "elmo" };
	return WordList[(rand() % 10)];
}
