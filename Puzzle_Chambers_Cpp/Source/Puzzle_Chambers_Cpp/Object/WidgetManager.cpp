// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/WidgetManager.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UWidgetManager::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) {
		return false;
	}

	if (PlayButton) {
		PlayButton->OnClicked.AddDynamic(this, &UWidgetManager::OnPlayClicked);
	}

	if (QuitButton) {
		QuitButton->OnClicked.AddDynamic(this, &UWidgetManager::OnQuitClicked);
	}

	if (ReturnButton) {
		ReturnButton->OnClicked.AddDynamic(this, &UWidgetManager::OnReturnClicked);
	}

	return true;
}

void UWidgetManager::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainMap"));
}

void UWidgetManager::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UWidgetManager::OnReturnClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

