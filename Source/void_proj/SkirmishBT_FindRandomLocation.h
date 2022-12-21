// Temp

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SkirmishBT_FindRandomLocation.generated.h"

/**
 * BTTask for finding a random location on a Navmesh
 */
UCLASS()
class VOID_PROJ_API USkirmishBT_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USkirmishBT_FindRandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float SearchRadius {500.f};

};
