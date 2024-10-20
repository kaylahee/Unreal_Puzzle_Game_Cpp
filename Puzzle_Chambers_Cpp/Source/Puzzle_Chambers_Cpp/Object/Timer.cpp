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

	// Ÿ�̸� ���� ���� �� ȭ�鿡 ǥ��
	if (TimerWidgetClass) {
		TimerWidget = CreateWidget<UUserWidget>(GetWorld(), TimerWidgetClass);
		if (TimerWidget)
		{
			TimerWidget->AddToViewport();

			// TimerText ����� TimerWidget���� ã�� ����
			TimerText = Cast<UTextBlock>(TimerWidget->GetWidgetFromName(FName("TimerText"))); // �ؽ�Ʈ ��� �̸�
		}
	}
}

// Called every frame
void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� �ð��� 0���� ū ��쿡�� Ÿ�̸� ������Ʈ
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

	// �ؽ�Ʈ ������Ʈ
	if (TimerText) {
		TimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void ATimer::OnTimerEnd()
{
	UGameplayStatics::OpenLevel(this, FName("GameOver"));
}