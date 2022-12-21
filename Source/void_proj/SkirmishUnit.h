// Temp

#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "SkirmishUnit.generated.h"

UCLASS()
class VOID_PROJ_API ASkirmishUnit : public AActor
{
	GENERATED_BODY()

public:
	ASkirmishUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float zIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	float StopDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	bool bSelected;

	// Called when the player selects this unit
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void OnSelect();

	// Called when the player deselects this unit
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void OnDeselect();

	// Move the unit to the specified location
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void MoveTo(FVector Destination);

private:
	FVector CurrentWaypoint;
	bool bMoving;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
