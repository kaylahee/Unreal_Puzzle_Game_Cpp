// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class ABoard;
class ADoor;

UCLASS()
class PUZZLE_CHAMBERS_CPP_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	TArray<ABoard*> AllBoards;
	TArray<ABoard*> AllBoard2s;
	TArray<ABoard*> AllBoard3s;
	TArray<ABoard*> AllBoard4s;

	void CheckAllBoardsCnt();
	void CheckAllBoardsCnt2();
	void CheckAllBoardsCnt3();
	void CheckAllBoardsCnt4();

	ABoard* B;

	UPROPERTY(EditAnywhere, Category = "Door")
	ADoor* D1;
	UPROPERTY(EditAnywhere)
	ADoor* D2;

	UPROPERTY(EditAnywhere, Category = "Visibility")
	AActor* HiddenActor1;

	UPROPERTY(EditAnywhere, Category = "Visibility")
	AActor* HiddenActor2;

	UPROPERTY(EditAnywhere, Category = "Visibility")
	AActor* HiddenActor3;

	void ShowHiddenActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
