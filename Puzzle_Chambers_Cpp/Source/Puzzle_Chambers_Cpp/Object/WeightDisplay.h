// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeightDisplay.generated.h"

class UTextRenderComponent;

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AWeightDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeightDisplay();
	void UpdateWeight(float TotalWeight);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderer;

private:
	
};
