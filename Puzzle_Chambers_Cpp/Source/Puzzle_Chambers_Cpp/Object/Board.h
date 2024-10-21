// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Board.generated.h"

class AGameManager;

UCLASS()
class PUZZLE_CHAMBERS_CPP_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Block;

	UPROPERTY(EditAnywhere)
	UArrowComponent* Position;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BlockTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FString B_color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FString B_shape;

	bool CompareProperties(FString CubeColor, FString CubeShape);

	UPROPERTY(VisibleAnywhere)
	int cnt;

	AGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage1")
	bool IsStage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage2")
	bool IsStage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage3")
	bool IsStage3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage4")
	bool IsStage4;

	bool isSnapped = false;
};
