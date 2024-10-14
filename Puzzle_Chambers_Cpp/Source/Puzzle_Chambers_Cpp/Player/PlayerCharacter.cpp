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

	// Physics Handle ������Ʈ �ʱ�ȭ
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Physics Handle�� �����ϴ��� Ȯ��
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle is missing on %s!"), *GetOwner()->GetName());
	}

	FlashLight = Cast<AFlashLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AFlashLight::StaticClass()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��ü�� ��� �ִٸ�, ��ü�� ��ġ�� ������Ʈ
	if (bIsGrabbingObject && PhysicsHandle && PhysicsHandle->GrabbedComponent) {
		UpdateGrabbedObjectLocation();
	}

	// ���� Ʈ���̽��� ����Ͽ� ��ü ����
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
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
	// ���� Ʈ���̽��� ����Ͽ� �÷��̾� ���� ��ü�� ����
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("1 Hit"));

	// ������ ��ü�� �ִٸ�
	if (HitResult.GetActor()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("2 Actor"));

		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		// ��ü�� ��ġ�� Physics Handle�� ���
		if (PhysicsHandle) {
			// ��ü�� �̹� ������ ���, ���� �ùķ��̼��� Ȱ��ȭ�Ͽ� �ٽ� ����
			if (ComponentToGrab->IsSimulatingPhysics()) {
				// ��ü�� ���
				PhysicsHandle->GrabComponentAtLocationWithRotation(
					ComponentToGrab,
					NAME_None,
					HitResult.ImpactPoint,
					HitResult.GetActor()->GetActorRotation()
				);

				bIsGrabbingObject = true;
			}
			// ��ü�� ������ ���¶��
			else {
				// ������ ��ü�� ���� �ùķ��̼��� Ȱ��ȭ
				ComponentToGrab->SetSimulatePhysics(true);

				// ��ü�� �ٽ� ����
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
	// Physics Handle�� ���� ��ü�� ����
	if (bIsGrabbingObject && PhysicsHandle) {
		// ���� ��� �ִ� ��ü ��������
		UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	
		if (GrabbedComponent)
		{
			GrabbedComponent->SetSimulatePhysics(false);
		}

		PhysicsHandle->ReleaseComponent();
		bIsGrabbingObject = false;
	}
}


FHitResult APlayerCharacter::GetFirstPhysicsBodyInReach() const
{
	//�÷��̾��� ��ġ�� ������ ������
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * 500.0f);

	FHitResult HitResult;

	//���� Ʈ���̽��� ����Ͽ� ��ü ����
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