#include "Puzzle_Chambers_Cpp/Player/PlayerCharacter.h"
#include "Puzzle_Chambers_Cpp/Object/FlashLight.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "RunTime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	AttachPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point"));
	AttachPoint->SetupAttachment(Camera);

	// AttachPoint의 로컬 위치를 설정 (예: 카메라의 바로 아래쪽에 위치하도록 조정)
	//AttachPoint->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f)); // 카메라 아래쪽으로 50 유닛 이동
	//AttachPoint->SetRelativeRotation(FRotator::ZeroRotator); // 회전 없이 기본 회전 유지

	// Physics Handle 컴포넌트 초기화
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Physics Handle이 존재하는지 확인
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle is missing on %s!"), *GetOwner()->GetName());
	}

	FlashLight = Cast<AFlashLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AFlashLight::StaticClass()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 물체를 잡고 있다면, 물체의 위치를 업데이트
	if (bIsGrabbingObject && PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		UpdateGrabbedObjectLocation();
	}

	// 라인 트레이스를 사용하여 물체 감지
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	static TWeakObjectPtr<AActor> LastHitActor; // 마지막 감지된 액터를 저장하기 위한 변수

	// 감지된 물체의 색상 변경
	if (HitResult.GetActor())
	{
		UPrimitiveComponent* ComponentToHighlight = HitResult.GetComponent();

		// 마지막으로 감지된 액터와 현재 감지된 액터가 다를 경우에만 색상 변경
		if (LastHitActor != HitResult.GetActor())
		{
			// 이전 감지된 액터의 색상 복원
			if (LastHitActor.IsValid())
			{
				UPrimitiveComponent* ComponentToRestore = LastHitActor->FindComponentByClass<UPrimitiveComponent>();
				if (ComponentToRestore)
				{
					UMaterialInstanceDynamic* DynamicMaterial = ComponentToRestore->CreateAndSetMaterialInstanceDynamic(0);
					if (DynamicMaterial)
					{
						DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::White); // 원래 색상으로 복원
					}
				}
			}

			// 현재 감지된 액터의 색상 변경
			UMaterialInstanceDynamic* DynamicMaterial = ComponentToHighlight->CreateAndSetMaterialInstanceDynamic(0);
			if (DynamicMaterial)
			{
				// 색상을 빨간색으로 변경
				DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Yellow);
			}

			// 마지막 감지된 액터 업데이트
			LastHitActor = HitResult.GetActor();
		}
	}
	else
	{
		// 라인 트레이스가 감지된 물체가 없을 때, 마지막 감지된 액터의 색상 복원
		if (LastHitActor.IsValid())
		{
			UPrimitiveComponent* ComponentToRestore = LastHitActor->FindComponentByClass<UPrimitiveComponent>();
			if (ComponentToRestore)
			{
				UMaterialInstanceDynamic* DynamicMaterial = ComponentToRestore->CreateAndSetMaterialInstanceDynamic(0);
				if (DynamicMaterial)
				{
					DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::White); // 원래 색상으로 복원
				}
			}
			LastHitActor = nullptr; // 마지막 감지된 액터 초기화
		}
	}
}



// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::Grab);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &APlayerCharacter::Release);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("AttachFlashLight", IE_Pressed, this, &APlayerCharacter::AttachFlashLight);
	PlayerInputComponent->BindAction("ToggleLight", IE_Pressed, this, &APlayerCharacter::ToggleLight);
}

void APlayerCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void APlayerCharacter::Turn(float InputValue)
{
	AddControllerYawInput(InputValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(-InputValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Grab()
{
	// 라인 트레이스를 사용하여 플레이어 앞의 물체를 감지
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	// 감지된 물체가 있다면
	if (HitResult.GetActor())
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		// 물체의 위치를 Physics Handle로 잡기
		if (PhysicsHandle)
		{
			// 물체가 이미 스냅된 경우, 물리 시뮬레이션을 활성화하여 다시 집기
			if (ComponentToGrab->IsSimulatingPhysics())
			{
				// 물체를 잡기
				PhysicsHandle->GrabComponentAtLocationWithRotation(
					ComponentToGrab,
					NAME_None,
					HitResult.ImpactPoint,
					HitResult.GetActor()->GetActorRotation()
				);

				bIsGrabbingObject = true;
			}
			else // 물체가 스냅된 상태라면
			{
				// 스냅된 물체의 물리 시뮬레이션을 활성화
				ComponentToGrab->SetSimulatePhysics(true);

				// 물체를 다시 집기
				PhysicsHandle->GrabComponentAtLocationWithRotation(
					ComponentToGrab,
					NAME_None,
					HitResult.ImpactPoint,
					HitResult.GetActor()->GetActorRotation()
				);

				bIsGrabbingObject = true;
			}
		}
	}
}

void APlayerCharacter::Release()
{
	// Physics Handle로 잡은 물체를 놓기
	if (bIsGrabbingObject && PhysicsHandle)
	{
		// 현재 잡고 있는 물체 가져오기
		UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();

		// 물체의 색상 복원 및 물리 시뮬레이션 비활성화
		if (GrabbedComponent)
		{
			GrabbedComponent->SetSimulatePhysics(false); // 물리 시뮬레이션 비활성화하여 고정
		}

		PhysicsHandle->ReleaseComponent();
		bIsGrabbingObject = false;
	}
}


FHitResult APlayerCharacter::GetFirstPhysicsBodyInReach() const
{
	//플레이어의 위치와 방향을 가져옴
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * 500.0f);

	FHitResult HitResult;

	//라인 트레이스를 사용하여 물체 감지
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	);

	return HitResult;
}

void APlayerCharacter::UpdateGrabbedObjectLocation()
{
	if (!PhysicsHandle) return;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector TargetLocation = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * 300.0f);
	PhysicsHandle->SetTargetLocation(TargetLocation);
}

void APlayerCharacter::AttachFlashLight()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("1. Q pressed")));
	if (bHasFlashLight) {
		bHasFlashLight = false;
	}
	else {
		bHasFlashLight = true;
	}

	if (bHasFlashLight) {
		if (FlashLight->bcanAttach) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("1. Q in")));
			FlashLight->Attach();
		}
	}
	else {
		FlashLight->Detach();
	}
}

void APlayerCharacter::ToggleLight()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("1. R pressed")));
	if (bIsLightTurnOn) {
		bIsLightTurnOn = false;
	}
	else {
		bIsLightTurnOn = true;
	}

	if (FlashLight->bIsAttached && bHasFlashLight) {
		if (bIsLightTurnOn) {
			FlashLight->TurnOn();
		}
		else {
			FlashLight->TurnOff();
		}
	}
}