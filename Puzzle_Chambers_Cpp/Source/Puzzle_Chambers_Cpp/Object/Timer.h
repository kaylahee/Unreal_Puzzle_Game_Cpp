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
	UTextBlock* TimerText; // Ÿ�̸� �ؽ�Ʈ ��� ���� �߰�

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �����ִ� Ÿ�̸� �ð� ����
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	float RemainingTime;

private:
	// Ÿ�̸� UI ������Ʈ �Լ�
	void UpdateTimerUI();

	// Ÿ�̸� ���� ó�� �Լ�
	void OnTimerEnd();

	// ���� ���� ������ ��ȯ�ϴ� �Լ�
	void EndGame();
};
