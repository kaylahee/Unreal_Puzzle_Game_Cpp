// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/FlashLight.h"
#include "Puzzle_Chambers_Cpp/Player/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine.h"

// Sets default values
AFlashLight::AFlashLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);

	FlashLight_Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	FlashLight_Light->SetupAttachment(RootComponent);

	FlashLight_Light->SetVisibility(false);
}

// Called when the game starts or when spawned
void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//�÷��̾ triggersphere ������ �������� ������ �� �ֵ���
void AFlashLight::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(OtherActor))
	{
		bcanAttach = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player In"));
	}
}

//�÷��̾ triggersphere �ۿ����� ���� �Ұ�
void AFlashLight::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(OtherActor))
	{
		bcanAttach = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Out"));
	}
}

void AFlashLight::Attach()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. E pressed")));
	
}

void AFlashLight::TurnOn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. R pressed")));
	
}