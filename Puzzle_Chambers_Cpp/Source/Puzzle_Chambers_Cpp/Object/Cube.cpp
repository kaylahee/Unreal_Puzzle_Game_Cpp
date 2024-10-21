// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/Cube.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	shape = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	RootComponent = shape;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
	bIsSnapped = false;
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACube::Fix()
{
	bIsSnapped = true;
	shape->SetSimulatePhysics(false);
}

void ACube::NotFix()
{
	shape->SetSimulatePhysics(true);
}