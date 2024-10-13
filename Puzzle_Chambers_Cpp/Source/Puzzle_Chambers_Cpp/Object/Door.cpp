// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle_Chambers_Cpp/Object/Door.h"
#include "Engine.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	RootComponent = Door;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CompareWeights();
}

void ADoor::CompareWeights()
{
	if (WeightA && WeightB)
	{
		float a = WeightA->GetTotalWeight();
		float b = WeightB->GetTotalWeight();

		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("a : %.2f"), a));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("b : %.2f"), b));*/

		if (a != 0 && b != 0 && a == b) {
			Destroy();
		}
	}
}