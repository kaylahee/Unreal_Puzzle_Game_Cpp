// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/MyGameMode.h"
#include "WidgetManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	FString worldName = World->GetMapName();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, World->GetMapName());

	if (worldName == "UEDPIE_0_MainMenu") {
		MainMenuWidgetInstance = CreateWidget<UWidgetManager>(GetWorld(), WidgetManagerClass);
		if (MainMenuWidgetInstance) {
			MainMenuWidgetInstance->AddToViewport();
		}
	}

	if (worldName == "UEDPIE_0_GameSuccess") {
		GameSuccessWidget = CreateWidget<UUserWidget>(GetWorld(), GameSuccessWidgetClass);
		if (GameSuccessWidget) {
			GameSuccessWidget->AddToViewport();
		}
	}

	if (worldName == "UEDPIE_0_GameOver") {
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidget) {
			GameOverWidget->AddToViewport();
		}
	}
}
