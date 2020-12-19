// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    srand(time(nullptr));
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
        if (Input.Len() != 4)
        {
            PrintLine(TEXT("Please enter 4 char of word!"));
            return ;
        }
        if (!(this->IsIsogram(Input)))
        {
            PrintLine(TEXT("Please enter word without duplicate characters!"));
            return ;
        }
        this->Calculate(Input);
        PrintLine(FString::Printf(TEXT("Bull: %i\nCow: %i"), this->Bull, this->Cow));
        if (this->Bull == 4 && this->Cow == 0)
        {
            PrintLine(TEXT("You Win!!!"));
            PrintLine(FString::Printf(TEXT("Is %s"), *(this->HiddenWord)));
            this->EndGame();
        }
        else
        {
            this->lives--;
            PrintLine(FString::Printf(TEXT("Lives: %i"), this->lives));
            if (this->lives == 0)
            {
                PrintLine(TEXT("You Lose!!!"));
                PrintLine(FString::Printf(TEXT("Is %s"), *(this->HiddenWord)));
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
    TArray<FString> str;
    str.Add(TEXT("cake"));
    str.Add(TEXT("bike"));
    str.Add(TEXT("bear"));
    str.Add(TEXT("rose"));
    str.Add(TEXT("road"));
    str.Add(TEXT("year"));
    str.Add(TEXT("kite"));
    str.Add(TEXT("wine"));
    return (str[rand() % (str.Num() - 1)]);
}

void UBullCowCartridge::InitGame()
{
    this->HiddenWord = this->GenStr();
    this->lives = this->HiddenWord.Len();
    this->Bull = 0;
    this->Cow = 0;
    this->bGameOver = false;
    PrintLine(TEXT("Welcome to BULL COWS"));
    PrintLine(TEXT("Guess the 4 letter word"));
    PrintLine(TEXT("Press enter you word..."));
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("GameOver"));
    PrintLine(TEXT("Press enter for restart game"));
    this->bGameOver = true;
}

//Warning! maybe dont work with duplicate letters
void UBullCowCartridge::Calculate(const FString& Input)
{
    for (int32 i = 0; i < 4; i++)
    {
        for (int32 j = 0; j < 4; j++)
        {
            if (Input[i] == this->HiddenWord[j] && i == j)
            {
                this->Bull++;
            }
            else if (Input[i] == this->HiddenWord[j] && i != j)
            {
                if (Input[i] == this->HiddenWord[j - 1])
                    continue ;
                this->Cow++;
            }
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const
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
