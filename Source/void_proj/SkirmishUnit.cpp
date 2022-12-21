// Temp
#include "SkirmishUnit.h"

#include "Engine.h"

// Sets default values
ASkirmishUnit::ASkirmishUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}


void ASkirmishUnit::OnSelect()
{
	bSelected = true;
	UE_LOG(LogTemp, Display, TEXT("Selected!"));
}

void ASkirmishUnit::OnDeselect()
{
	bSelected = false;
}

void ASkirmishUnit::MoveTo(FVector WorldLocation)
{
	CurrentWaypoint = WorldLocation;

	bMoving = true;
}

void ASkirmishUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMoving)
	{
		FVector Direction = CurrentWaypoint - GetActorLocation();
		float Distance = Direction.Size();

		// Normalize the direction and multiply by the move speed
		Direction.Normalize();
		Direction *= MoveSpeed;

		SetActorLocation(GetActorLocation() + Direction * DeltaTime);

		if (CurrentWaypoint == Direction)
		{
			UE_LOG(LogTemp, Error, TEXT("Arrived"));

			bMoving = false;
		}
		// FVector Location = GetActorLocation();
		// FVector Direction = CurrentDestination - Location;
		// float Distance = Direction.Size();
		// if (Distance > StopDistance)
		// {
		// 	UE_LOG(LogTemp, Display, TEXT("Moving!"));

		// 	Direction.Normalize();
		// 	Location += Direction * MoveSpeed * DeltaTime;
		// 	SetActorLocation(Location);
		// }
		// else
		// {
		// 	UE_LOG(LogTemp, Display, TEXT("Stopping!"));

		// 	bMoving = false;
		// }
	}
}