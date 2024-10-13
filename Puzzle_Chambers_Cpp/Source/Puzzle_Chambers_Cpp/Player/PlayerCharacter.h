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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	FTransform FlashlightAttachTransform;

	UPROPERTY(EditAnywhere)
	AFlashLight* FlashLight;

	void AttachFlashLight();
	void ToggleLight();

protected:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void Turn(float InputValue);
	void LookUp(float Value);

	float BaseTurnRate = 45.0f;
	float BaseLookUpRate = 45.0f;

	bool bCanGetLight;
	bool bHasFlashLight;
	bool bIsLightTurnOn;

private:
	//Physics Handle ������Ʈ
	UPROPERTY(VisibleAnywhere)
	class UPhysicsHandleComponent* PhysicsHandle;

	//��ü ��� ���� Ȯ��
	bool bIsGrabbingObject = false;

	//��ü ��� �� ���� �Լ�
	void Grab();
	void Release();

	//�÷��̾ ���� �������� ���� Ʈ���̽��Ͽ� ��ü ����
	FHitResult GetFirstPhysicsBodyInReach() const;

	//��ü ��� �ִ� ���� ��ü�� ��ġ ������Ʈ
	void UpdateGrabbedObjectLocation();
};
