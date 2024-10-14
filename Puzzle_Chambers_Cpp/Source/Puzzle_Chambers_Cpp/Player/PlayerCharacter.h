// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AFlashLight;

UCLASS()
class PUZZLE_CHAMBERS_CPP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	AFlashLight* FlashLight;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* AttachPoint;

	void AttachFlashLight();
	void ToggleLight();

	//물체 잡기 상태 확인
	bool bIsGrabbingObject = false;

protected:
	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void Turn(float InputValue);
	void LookUp(float Value);

	float BaseTurnRate = 45.0f;
	float BaseLookUpRate = 45.0f;

	bool bCanGetLight = false;
	bool bHasFlashLight = false;
	bool bIsLightTurnOn = false;

private:
	//Physics Handle 컴포넌트
	UPROPERTY(VisibleAnywhere)
	class UPhysicsHandleComponent* PhysicsHandle;

	//물체 잡기 및 놓기 함수
	void Grab();
	void Release();

	//플레이어가 보는 방향으로 라인 트레이스하여 물체 감지
	FHitResult GetFirstPhysicsBodyInReach() const;

	//물체 잡고 있는 동안 물체의 위치 업데이트
	void UpdateGrabbedObjectLocation();
};
