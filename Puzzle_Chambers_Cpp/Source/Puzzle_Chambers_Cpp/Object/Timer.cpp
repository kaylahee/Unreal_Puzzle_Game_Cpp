// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/Timer.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATimer::ATimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RemainingTime = 300.0f;
}

// Called when the game starts or when spawned
void ATimer::BeginPlay()
{
	Super::BeginPlay();

	// 타이머 위젯 생성 및 화면에 표시
	if (TimerWidgetClass) {
		TimerWidget = CreateWidget<UUserWidget>(GetWorld(), TimerWidgetClass);
		if (TimerWidget)
		{
			TimerWidget->AddToViewport();

			// TimerText 블록을 TimerWidget에서 찾아 설정
			TimerText = Cast<UTextBlock>(TimerWidget->GetWidgetFromName(FName("TimerText"))); // 텍스트 블록 이름
		}
	}
}

// Called every frame
void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 남은 시간이 0보다 큰 경우에만 타이머 업데이트
	if (RemainingTime > 0.0f) {
		RemainingTime -= DeltaTime; 
		UpdateTimerUI();

		if (RemainingTime <= 1.0f) {
			OnTimerEnd();
		}
	}
}

void ATimer::UpdateTimerUI()
{
	int32 Minutes = FMath::FloorToInt(RemainingTime / 60);
	int32 Seconds = FMath::FloorToInt(RemainingTime) % 60;

	// 텍스트 업데이트
	if (TimerText) {
		TimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void ATimer::OnTimerEnd()
{
	UGameplayStatics::OpenLevel(this, FName("GameOver"));
}