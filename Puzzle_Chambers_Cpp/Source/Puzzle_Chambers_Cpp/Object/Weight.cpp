// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/Weight.h"

// Sets default values
AWeight::AWeight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = 5.0f;

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// 충돌 설정
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

// Called when the game starts or when spawned
void AWeight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AWeight::GetWeight() const
{
	return Mass;
}
