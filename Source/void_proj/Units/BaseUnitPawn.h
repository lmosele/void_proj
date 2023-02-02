// Temp

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseUnitPawn.generated.h"

/**
 * 
 */
UCLASS()
class VOID_PROJ_API ABaseUnitPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnitPawn();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void OnSelected();
	void RotateTo();
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FVector TargetLocation;

	float SensorRange = 1000.f;
	float PatrolRadius = 400.f;
	float ZIndex;
	float EngageDistance;
	bool CanMove;
	bool IsTurning;

	void SetPatrol();
	bool GetRandomPointInRadius(const FVector& Origin, float Radius, FVector& OutResult);

	class  UAITask_MoveTo* AITask;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp; 
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;

};
