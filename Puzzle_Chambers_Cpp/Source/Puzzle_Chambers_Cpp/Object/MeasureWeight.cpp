// Fill out your copyright notice in the Description page of Project Settings.
#include "Puzzle_Chambers_Cpp/Object/MeasureWeight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Puzzle_Chambers_Cpp/Object/Weight.h"
#include "Engine.h"

// Sets default values
AMeasureWeight::AMeasureWeight()
{
    PrimaryActorTick.bCanEverTick = true;

    // Cylinder 초기화
    Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
    RootComponent = Cylinder;
    
    // TriggerBox 초기화
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);

    TotalWeight = 0.0f;
}

// Called when the game starts or when spawned
void AMeasureWeight::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeasureWeight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeasureWeight::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (AWeight* WeightActor = Cast<AWeight>(OtherActor))
    {
        // 무게 합산
        TotalWeight += WeightActor->GetWeight();
        /*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%.2f"), TotalWeight));*/
        UpdateWeightDisplay();
    }
}

void AMeasureWeight::NotifyActorEndOverlap(AActor* OtherActor)
{
    if (AWeight* WeightActor = Cast<AWeight>(OtherActor))
    {
        // 무게 차감
        TotalWeight -= WeightActor->GetWeight();
        UpdateWeightDisplay();
    }
}

void AMeasureWeight::UpdateWeightDisplay()
{
    WeightDisplay->UpdateWeight(TotalWeight);
}