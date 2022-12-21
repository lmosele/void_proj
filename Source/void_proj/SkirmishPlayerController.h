// Temp

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkirmishPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VOID_PROJ_API ASkirmishPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASkirmishPlayerController();

protected:
	virtual void SetupInputComponent() override;

private:
	// Maximum distance for unit selection
	UPROPERTY(EditAnywhere, Category = "Unit Selection")
	float MaxSelectionDistance;

	// Called when the player selects a unit
	void OnSelectPressed();
	void OnWaypoint(FVector Destination);
	void OnWayPointSelect();
};
