// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/GO_PlayerController.h"

void AGO_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GameOverWidgetClass != nullptr) {
        GameOverWidget = CreateWidget<UUserWidget>(this, GameOverWidgetClass);
        if (GameOverWidget != nullptr) {
            GameOverWidget->AddToViewport();
        }
    }
}