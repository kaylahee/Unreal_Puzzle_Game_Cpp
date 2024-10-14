// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/MyGameMode.h"
#include "MainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass) {
		UMainMenuWidget* MainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenu) {
			MainMenu->AddToViewport();
		}
	}
}
