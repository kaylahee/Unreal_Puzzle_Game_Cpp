// Fill out your copyright notice in the Description page of Project Settings.
#include "Puzzle_Chambers_Cpp/Object/MeasureWeight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Puzzle_Chambers_Cpp/Object/Weight.h"

// Sets default values
AMeasureWeight::AMeasureWeight()
{
    PrimaryActorTick.bCanEverTick = true;

    // TriggerBox 초기화
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

    // Cylinder 초기화
    Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));

    // 실린더 메시 설정 (기본 제공 메시 사용)
    //static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder")); // Unreal Engine 기본 실린더 메시 경로

    TotalWeight = 0.0f;

    // 충돌 설정
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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

void AMeasureWeight::UpdateWeightDisplay() const
{
    if (WeightDisplay)
    {
        WeightDisplay->UpdateWeight(TotalWeight);
    }
}