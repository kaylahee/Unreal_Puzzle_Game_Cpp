// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/WeightDisplay.h"
#include "Components/TextRenderComponent.h"
#include "Engine.h"

// Sets default values
AWeightDisplay::AWeightDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WeightDisplay"));

    TextRenderer->SetupAttachment(RootComponent);
    TextRenderer->SetHorizontalAlignment(EHTA_Center);
    TextRenderer->SetText(FText::FromString("0.0 kg"));
}

// Called when the game starts or when spawned
void AWeightDisplay::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeightDisplay::UpdateWeight(float TotalWeight)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%.2f"), TotalWeight));
    /*FString WeightString = FString::Printf(TEXT("%.f kg"), TotalWeight);
    TextRenderer->SetText(FText::FromString(WeightString));*/
}

