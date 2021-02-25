// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    this->InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (this->bGameOver)
    {
        PrintLine(TEXT("RESTART..."));
        this->InitGame();
    }
    else
    {
        if (!(this->IsIsogram(Input)))
        {
            PrintLine(TEXT("Please enter word without duplicate characters!"));
            return ;
        }
        this->Calculate(Input);
        PrintLine(TEXT("Bull: %i\nCow: %i"), this->Bull, this->Cow);
        if (this->Bull == this->HiddenWord.Len() && this->Cow == 0)
        {
            PrintLine(TEXT("You Win!!!"));
            PrintLine(TEXT("Is %s"), *(this->HiddenWord));
            this->EndGame();
        }
        else
        {
            this->lives--;
            PrintLine(TEXT("Lives: %i"), this->lives);
            if (this->lives == 0)
            {
                PrintLine(TEXT("You Lose!!!"));
                PrintLine(TEXT("Is %s"), *(this->HiddenWord));
                this->EndGame();
            }
            else
            {
                PrintLine(TEXT("Nope! try again..."));
            }
        }
        this->Bull = 0;
        this->Cow = 0;
    }
}

FString UBullCowCartridge::GenStr()
{
    return (HiddenWordsArray[FMath::RandRange(0, HiddenWordsArray.Num() - 1)]);
}

void UBullCowCartridge::InitGame()
{
    this->HiddenWord = this->GenStr();
    this->lives = this->HiddenWord.Len();
    this->Bull = 0;
    this->Cow = 0;
    this->bGameOver = false;
    PrintLine(TEXT("Welcome to BULL COWS"));
    PrintLine(TEXT("Guess the %i letter word"), this->HiddenWord.Len());
    PrintLine(TEXT("Press enter you word..."));
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("GameOver"));
    PrintLine(TEXT("Press enter for restart game"));
    this->bGameOver = true;
}

//Warning! maybe dont work with duplicate letters
void UBullCowCartridge::Calculate(FString Input)
{
    for (int32 i = 0; i < Input.Len(); i++)
    {
        for (int32 j = 0; j < this->HiddenWord.Len(); j++)
        {
            if (Input[i] == this->HiddenWord[j] && i == j)
            {
                this->Bull++;
            }
            else if (Input[i] == this->HiddenWord[j] && i != j)
            {
                if ((j - 1 >= 0) && Input[i] == this->HiddenWord[j - 1])
                    continue ;
                this->Cow++;
            }
        }
    }
}

bool UBullCowCartridge::IsIsogram(FString Input) const
{
    int32 size = Input.Len();
    for (int32 i = 0; i < size; i++)
    {
        for (int32 j = i + 1; j < size; j++)
        {
            if (Input[i] == Input[j])
                return (false);
        }
    }
    return (true);
}
