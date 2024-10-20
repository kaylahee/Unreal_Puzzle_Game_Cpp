// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetManager.h"
#include "GameManager.h"
#include "MyGameMode.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWidgetManager> WidgetManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSuccess")
	TSubclassOf<UUserWidget> GameSuccessWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameOver")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

private:
	UWidgetManager* MainMenuWidgetInstance;
	UUserWidget* GameSuccessWidget;
	UUserWidget* GameOverWidget;

	UWorld* World = GetWorld();
};
