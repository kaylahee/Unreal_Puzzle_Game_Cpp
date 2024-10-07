// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeightDisplay.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MeasureWeight.generated.h"

class AWeight;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AMeasureWeight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeasureWeight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cylinder;

	float TotalWeight;

	UPROPERTY(EditAnywhere)
	AWeightDisplay* WeightDisplay;

	void UpdateWeightDisplay() const;
};
