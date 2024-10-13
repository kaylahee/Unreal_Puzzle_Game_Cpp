// Fill out your copyright notice in the Description page of Project Settings.
#include "MeasureWeight.h"
#include "Weight.h"
#include "WeightDisplay.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"
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

    TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WeightDisplay"));
    TextRenderer->SetupAttachment(RootComponent);

    TextRenderer->SetHorizontalAlignment(EHTA_Center);
    TextRenderer->SetText(FText::FromString("0.0 kg"));

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
        FString WeightString = FString::Printf(TEXT("%.f kg"), TotalWeight);
        TextRenderer->SetText(FText::FromString(WeightString));
        /*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%.2f"), TotalWeight));*/
    }
}

void AMeasureWeight::NotifyActorEndOverlap(AActor* OtherActor)
{
    if (AWeight* WeightActor = Cast<AWeight>(OtherActor))
    {
        // 무게 차감
        TotalWeight -= WeightActor->GetWeight();
        FString WeightString = FString::Printf(TEXT("%.f kg"), TotalWeight);
        TextRenderer->SetText(FText::FromString(WeightString));
    }
}