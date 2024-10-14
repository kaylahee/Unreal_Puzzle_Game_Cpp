// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/GS_PlayerController.h"

void AGS_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GameSuccessWidgetClass != nullptr) {
        GameSuccessWidget = CreateWidget<UUserWidget>(this, GameSuccessWidgetClass);
        if (GameSuccessWidget != nullptr) {
            GameSuccessWidget->AddToViewport();
        }
    }
}