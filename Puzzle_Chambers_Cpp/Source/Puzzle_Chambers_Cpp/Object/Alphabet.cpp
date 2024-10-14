// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/Alphabet.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AAlphabet::AAlphabet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Alphabet"));
	TextRenderer->SetupAttachment(RootComponent);

	/*Back = CreateDefaultSubobject<UBoxComponent>(TEXT("BackGround"));
	Back->SetupAttachment(RootComponent);*/
}

// Called when the game starts or when spawned
void AAlphabet::BeginPlay()
{
	Super::BeginPlay();
	
	TextRenderer->SetVisibility(false);
}

// Called every frame
void AAlphabet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAlphabet::ShowText()
{
	TextRenderer->SetVisibility(true);
}

void AAlphabet::HideText()
{
	TextRenderer->SetVisibility(false);
}