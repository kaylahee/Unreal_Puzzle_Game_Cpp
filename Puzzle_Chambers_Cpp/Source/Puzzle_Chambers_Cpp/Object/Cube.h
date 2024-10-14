// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FString C_color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FString C_shape;
	
	void Fix();
	void NotFix();
};
