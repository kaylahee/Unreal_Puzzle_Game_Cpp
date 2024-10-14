// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GS_PlayerController.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AGS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSuccess")
	TSubclassOf<UUserWidget> GameSuccessWidgetClass;

private:
	UUserWidget* GameSuccessWidget;
};
