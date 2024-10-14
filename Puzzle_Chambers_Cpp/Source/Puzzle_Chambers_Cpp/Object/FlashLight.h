// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"
#include "FlashLight.generated.h"

class APlayerCharacter;

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
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attach();
	void Detach();
	void TurnOn();
	void TurnOff();
	void ShowAlphabet();
	void HideAlphabet();

	bool bcanAttach = false;
	bool bIsAttached = false;
	bool bIsLightOn = false;

	FTransform OriginalTransform;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* TriggerSphere;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	USpotLightComponent* FlashLight_Light;

	UPROPERTY(EditAnywhere)
	APlayerCharacter* PlayerActor;
};
