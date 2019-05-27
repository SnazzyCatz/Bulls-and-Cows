#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	
	FBullCowCount SubmitValidGuess(FString);

	void Reset();
	EGuessStatus IsValidGuess(FString) const;

private:
	bool isIsogram(FString) const;
	bool isAllLower(FString) const;
	bool bGameIsWon;
	int32 MyCurrentTry; //See constructor
	int32 MyMaxTries;
	FString HiddenWord;
	FString RandomWord();
};