#include "Puzzle_Chambers_Cpp/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	// Physics Handle ������Ʈ �ʱ�ȭ
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Physics Handle�� �����ϴ��� Ȯ��
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle is missing on %s!"), *GetOwner()->GetName());
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��ü�� ��� �ִٸ�, ��ü�� ��ġ�� ������Ʈ
	if (bIsGrabbingObject && PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		UpdateGrabbedObjectLocation();
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
	//���� Ʈ���̽��� ����Ͽ� �÷��̾� ���� ��ü�� ����
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	//������ ��ü�� �ִٸ�
	if (HitResult.GetActor())
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		FVector GrabLocation = HitResult.ImpactPoint;

		FRotator GrabRotation = HitResult.GetActor()->GetActorRotation();

		//��ü�� ��ġ�� Physics Handle�� ���
		if (PhysicsHandle)
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				ComponentToGrab,
				NAME_None,
				GrabLocation,
				GrabRotation
			);

			bIsGrabbingObject = true;
			ComponentToGrab->SetSimulatePhysics(true);
		}
	}
}

void APlayerCharacter::Release()
{
	//Physics Handle�� ���� ��ü�� ����
	if (bIsGrabbingObject && PhysicsHandle)
	{
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