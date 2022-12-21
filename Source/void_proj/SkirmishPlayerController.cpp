// Temp


#include "SkirmishPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "SkirmishUnit.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ASkirmishPlayerController::ASkirmishPlayerController()
{
	MaxSelectionDistance = 10000.0f;
    bShowMouseCursor = true;
}

void ASkirmishPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Display, TEXT("Started!"));

	InputComponent->BindAction("Select", IE_Pressed, this, &ASkirmishPlayerController::OnSelectPressed);
    InputComponent->BindAction("Point", IE_Pressed, this, &ASkirmishPlayerController::OnWayPointSelect);

}

void ASkirmishPlayerController::OnSelectPressed()
{
	// Raycast from the camera to the cursor position to find a unit
	FVector StartLocation;
	FRotator StartRotation;
	GetPlayerViewPoint(StartLocation, StartRotation);
	FVector EndLocation = StartLocation + StartRotation.Vector() * 100.f;
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		// Check if the hit actor is a unit and select it if it is
		ASkirmishUnit* Unit = Cast<ASkirmishUnit>(HitResult.GetActor());
		if (Unit)
		{
            UE_LOG(LogTemp, Display, TEXT("Unit: %s"), *Unit->GetActorNameOrLabel());

			Unit->OnSelect();
		}
	}
}

void ASkirmishPlayerController::OnWayPointSelect()
{
	
    FVector2D MousePosition;
    GetMousePosition(MousePosition.X, MousePosition.Y);
      // Convert the mouse position to a world location
    FVector WorldLocation;
    FVector WorldDirection;
    DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

    FHitResult HitResult;
    FVector Start = PlayerCameraManager->GetCameraLocation();
    FVector End = Start + WorldDirection * 10000.0f;
    GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);

    if (HitResult.bBlockingHit)
    {
        // HitResult.Location contains the location of the hit in the world
        FVector Destination = HitResult.Location;
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.0f, 0, 5.0f);
        OnWaypoint(Destination);
    }
	
}

void ASkirmishPlayerController::OnWaypoint(FVector WorldLocation)
{
    UE_LOG(LogTemp, Display, TEXT("OnWaypoint"));
	// Find all selected units
	TArray<AActor*> SelectedUnits;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkirmishUnit::StaticClass(), SelectedUnits);
	for (AActor* Actor : SelectedUnits)
	{
		ASkirmishUnit* Unit = Cast<ASkirmishUnit>(Actor);
		if (Unit && Unit->bSelected)
		{
			// Call the MoveTo function on the unit
			Unit->MoveTo(WorldLocation);
		}
	}
}