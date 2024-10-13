// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeasureWeight.h"
#include "Door.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void CompareWeights();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeightA")
	AMeasureWeight* WeightA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeightB")
	AMeasureWeight* WeightB;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Door;
};
