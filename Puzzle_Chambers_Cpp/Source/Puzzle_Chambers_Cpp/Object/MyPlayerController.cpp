// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (CrosshairWidgetClass != nullptr) {
        CrosshairWidget = CreateWidget<UUserWidget>(this, CrosshairWidgetClass);
        if (CrosshairWidget != nullptr) {
            CrosshairWidget->AddToViewport();
        }
    }
}