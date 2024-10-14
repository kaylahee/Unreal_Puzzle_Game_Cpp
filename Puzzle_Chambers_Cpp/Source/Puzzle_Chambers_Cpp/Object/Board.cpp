// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/Board.h"
#include "Cube.h"
#include "GameManager.h"
#include "Puzzle_Chambers_Cpp/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoard::ABoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	RootComponent = Block;

	Position = CreateDefaultSubobject<UArrowComponent>(TEXT("Position"));
	Position->SetupAttachment(RootComponent);

	BlockTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockTrigger"));
	BlockTrigger->SetupAttachment(Block);

	cnt = 0;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));

	if (GameManager && IsStage1)
	{
		GameManager->AllBoards.Add(this);
	}

	if (GameManager && IsStage2)
	{
		GameManager->AllBoard2s.Add(this);
	}

	if (GameManager && IsStage3)
	{
		GameManager->AllBoard3s.Add(this);
	}
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (ACube* C = Cast<ACube>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube Snap"));
		
		C->SetActorLocation(Position->GetComponentLocation());
		C->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		C->Fix();

		FString CubeColor = C->C_color;
		FString CubeShape = C->C_shape;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), CompareProperties(CubeColor, CubeShape)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), cnt));

		if (CompareProperties(CubeColor, CubeShape)) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube Match"));
			cnt = 1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), cnt));

			if (IsStage1) {
				GameManager->CheckAllBoardsCnt();
			}
			if (IsStage2) {
				GameManager->CheckAllBoardsCnt2();
			}
			if (IsStage3) {
				GameManager->CheckAllBoardsCnt3();
			}
		}
		else {
			cnt = 0;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube Not Match"));
		}
	}
}

void ABoard::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (ACube* C = Cast<ACube>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube Snap Out"));
	}
}

bool ABoard::CompareProperties(FString CubeColor, FString CubeShape)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CubeColor: %s, CubeShape: %s, B_Color: %s, B_Shape: %s"), *CubeColor, *CubeShape, *B_color, *B_shape));
	return (B_color == CubeColor) && (B_shape == CubeShape);
}