// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "FlashLight.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AFlashLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachFlashLight();
	void DetachFlashLight();

	void ToggleLight();

	bool bIsAttached;
	bool bIsLightOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
};
