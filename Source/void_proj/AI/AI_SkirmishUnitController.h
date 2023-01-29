// Temp

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_SkirmishUnitController.generated.h"


class UBehaviorTreeComponent;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class VOID_PROJ_API AAI_SkirmishUnitController : public AAIController
{
	GENERATED_BODY()

public:
	AAI_SkirmishUnitController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;


};
