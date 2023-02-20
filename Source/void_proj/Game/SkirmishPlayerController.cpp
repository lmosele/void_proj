// Temp


#include "SkirmishPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "../Units/Skirmish_Unit.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ASkirmishPlayerController::ASkirmishPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ASkirmishPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


void ASkirmishPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// // Pawn Control
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ASkirmishPlayerController::OnInputStarted);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ASkirmishPlayerController::OnSetDestinationTriggered);
		// EnhancedInputComponent->BindAction(SetSelectionClickAction, ETriggerEvent::Triggered, this, &ASkirmishPlayerController::OnSelectUnit);

		// Camera Inputs
		EnhancedInputComponent->BindAction(SetCameraForwardAxis, ETriggerEvent::Triggered, this, &ASkirmishPlayerController::OnSetCameraForwardAxis);
		EnhancedInputComponent->BindAction(SetCameraSidewaysAxis, ETriggerEvent::Triggered, this, &ASkirmishPlayerController::OnSetCameraSidewaysAxis);
	}
}


void ASkirmishPlayerController::OnInputStarted()
{
	StopMovement();
}


// Triggered every frame when the input is held down
void ASkirmishPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
		CachedDestination.Z = 1.f;
	}
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		// UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		// UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

		// FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		// ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);

		
	}
}

/**
 * @brief Triggers the SELECTION action on the ASkirmish_Unit class
 */
void ASkirmishPlayerController::OnSelectUnit()
{
    FHitResult HitResult;
	bool bHitSuccessful = false;
	bHitSuccessful =  GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
   
    if (bHitSuccessful && HitResult.bBlockingHit)
    {
		AActor* HitActor = HitResult.GetActor();
        ASkirmish_Unit* SelectedUnit = Cast<ASkirmish_Unit>(HitActor);
        // SelectedUnit->OnSelected();

		UWorld* World = GetWorld();
		APlayerController* PC = World->GetFirstPlayerController();
		PC->Possess(SelectedUnit);
    }
}

void ASkirmishPlayerController::OnSetCameraForwardAxis()
{

}
void ASkirmishPlayerController::OnSetCameraSidewaysAxis()
{

}
