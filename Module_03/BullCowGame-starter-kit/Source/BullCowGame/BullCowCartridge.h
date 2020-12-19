// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& Input) override;
		FString GenStr();
		void InitGame();
		void EndGame();
		void Calculate(const FString& Input);
		bool IsIsogram(const FString& Input) const;

	// Your declarations go below!
	private:
		FString HiddenWord;
		int32 lives;
		int32 Cow;
		int32 Bull;
		bool bGameOver;
	
};
