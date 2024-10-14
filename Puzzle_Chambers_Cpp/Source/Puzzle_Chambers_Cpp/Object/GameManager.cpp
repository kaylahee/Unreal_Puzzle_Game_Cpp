// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/GameManager.h"
#include "Board.h"
#include "Door.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::CheckAllBoardsCnt()
{
	bool bAllCntAreOne = true;

	// ��� ������ cnt ���� Ȯ��
	for (ABoard* Board : AllBoards) {
		if (Board && Board->cnt != 1) {
			bAllCntAreOne = false;
			break;
		}
	}

	// ��� ������ cnt�� 1�̸� Ư�� ���� ����
	if (bAllCntAreOne) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("All boards' cnt is 1!"));
		ShowHiddenActors();
	}
}

void AGameManager::ShowHiddenActors()
{
	for (ABoard* Board : AllBoard2s) {
		Board->GetRootComponent()->SetVisibility(true);
	}
}

void AGameManager::CheckAllBoardsCnt2()
{
	bool bAllCntAreOne = true;

	// ��� ������ cnt ���� Ȯ��
	for (ABoard* Board : AllBoard2s) {
		if (Board && Board->cnt != 1) {
			bAllCntAreOne = false;
			break;
		}
	}

	// ��� ������ cnt�� 1�̸� Ư�� ���� ����
	if (bAllCntAreOne) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Door destroy"));
		D1->Destroy();
	}
}

void AGameManager::CheckAllBoardsCnt3()
{
	bool bAllCntAreOne = true;

	// ��� ������ cnt ���� Ȯ��
	for (ABoard* Board : AllBoard3s) {
		if (Board && Board->cnt != 1) {
			bAllCntAreOne = false;
			break;
		}
	}

	// ��� ������ cnt�� 1�̸� Ư�� ���� ����
	if (bAllCntAreOne) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Door destroy"));
		D2->Destroy();
	}
}