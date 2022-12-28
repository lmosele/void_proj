// Temp


#include "AI_SkirmishUnitController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAI_SkirmishUnitController::AAI_SkirmishUnitController()
{
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AAI_SkirmishUnitController::BeginPlay()
{
    Super::BeginPlay();
    if (IsValid(BehaviorTree.Get()))
    {
        RunBehaviorTree(BehaviorTree.Get());
        BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
    }
}

void AAI_SkirmishUnitController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
    {
        Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
    }
}
