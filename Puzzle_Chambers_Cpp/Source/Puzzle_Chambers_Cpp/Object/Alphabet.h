// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Alphabet.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AAlphabet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlphabet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TextRenderer;

	/*UPROPERTY(EditAnywhere)
	UBoxComponent* Back;*/

	void ShowText();
	void HideText();
};
