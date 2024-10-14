// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Chambers_Cpp/Object/FlashLight.h"
#include "Puzzle_Chambers_Cpp/Player/PlayerCharacter.h"
#include "Puzzle_Chambers_Cpp/Object/Alphabet.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine.h"
#include "RunTime/Engine/Classes/Kismet/GameplayStatics.h"


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

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerLight"));
	SphereComponent->SetupAttachment(FlashLight_Light);

	FVector OriginalPos = FVector(715.0f, 710.0f, 160.0f);
	FRotator OriginalRot = FRotator(-90.0f, 0.0f, 0.0f);
	FVector OriginalScale = FVector(0.5f, 0.5f, 0.7f);
	OriginalTransform = FTransform(OriginalRot, OriginalPos, OriginalScale);
}

// Called when the game starts or when spawned
void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerActor = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
	FlashLight_Light->SetVisibility(false);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttached)
	{
		FVector NewPos = PlayerActor->AttachPoint->GetComponentLocation();
		FRotator NewRot = PlayerActor->AttachPoint->GetComponentRotation();
		FVector NewScale = FVector(0.5f, 0.5f, 0.7f);
		FTransform NewTransform(NewRot, NewPos, NewScale);

		this->SetActorTransform(NewTransform);
	}
}

//플레이어가 triggersphere 안으로 들어왔을때 장착할 수 있도록
void AFlashLight::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* P = Cast<APlayerCharacter>(OtherActor))
	{
		bcanAttach = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player In"));
	}

	if (AAlphabet* alphabet = Cast<AAlphabet>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("3. ShowAlphabet")));
		alphabet->ShowText();
	}
}

//플레이어가 triggersphere 밖에서는 장착 불가
void AFlashLight::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* P = Cast<APlayerCharacter>(OtherActor))
	{
		bcanAttach = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Out"));
	}

	if (AAlphabet* alphabet = Cast<AAlphabet>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("3. ShowAlphabet")));
		alphabet->HideText();
	}
}

void AFlashLight::Attach()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. Attached")));
	bIsAttached = true;
}

void AFlashLight::Detach()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. Detached")));
	bIsAttached = false;
	this->SetActorTransform(OriginalTransform);
}

void AFlashLight::TurnOn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. TurnOn")));
	FlashLight_Light->SetVisibility(true);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AFlashLight::TurnOff()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("2. TurnOff")));
	FlashLight_Light->SetVisibility(false);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}