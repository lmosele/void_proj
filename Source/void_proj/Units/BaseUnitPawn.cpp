// Temp


#include "BaseUnitPawn.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
// #include "Tasks/AITask_MoveTo.h"

#include "DrawDebugHelpers.h" 
#include "NavigationSystem.h"

// Sets default values
ABaseUnitPawn::ABaseUnitPawn()
{
	// Set size for player capsule
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	RootComponent = CapsuleComp;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
    MovementComponent->Acceleration = 1.0f;
    MovementComponent->MaxSpeed = 100.f;


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

void ABaseUnitPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    DrawDebugSphere(GetWorld(), TargetLocation, 100.0f, 12, FColor::Magenta, true, -1.0f, SDPG_Foreground, 3.0f);
}

void ABaseUnitPawn::BeginPlay()
{
    Super::BeginPlay();
    FVector CurrentLocation = GetActorLocation();
    ZIndex = CurrentLocation.Z;

	SetPatrol();
    RotateTo();

	  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABaseUnitPawn::SetPatrol, 5.f, true);
}


// This isnt interping for some reason, need to figure it out.
void ABaseUnitPawn::RotateTo()
{
    UE_LOG(LogTemp, Display, TEXT("Turning"));
    SetActorRotation(FMath::RInterpTo(
		GetActorRotation(), 
		UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation), 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		0.7f));
}

void ABaseUnitPawn::SetPatrol()
{
    FVector Result;
	if (ABaseUnitPawn::GetRandomPointInRadius(GetActorLocation(), PatrolRadius, Result)) {
		TargetLocation = Result;
        // AAIController* UnitAIController = AITask->GetAIController();
        // AITask->AIMoveTo(UnitAIController, TargetLocation);
	}
}


bool ABaseUnitPawn::GetRandomPointInRadius(const FVector& Origin, float Radius, FVector& OutResult)
{	
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
	{
		return false;
	}

	FVector Result;
	bool bSuccess = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), Origin, Result, PatrolRadius);

	OutResult = Result;
	return bSuccess;
}
