#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Timer.generated.h"

UCLASS()
class PUZZLE_CHAMBERS_CPP_API ATimer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> TimerWidgetClass;

	UPROPERTY()
	UUserWidget* TimerWidget;

	UPROPERTY()
	UTextBlock* TimerText; // 타이머 텍스트 블록 변수 추가

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 남아있는 타이머 시간 변수
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	float RemainingTime;

private:
	// 타이머 UI 업데이트 함수
	void UpdateTimerUI();

	// 타이머 종료 처리 함수
	void OnTimerEnd();

	// 게임 종료 씬으로 전환하는 함수
	void EndGame();
};
