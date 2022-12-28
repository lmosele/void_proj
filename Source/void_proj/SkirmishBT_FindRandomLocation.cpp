// Temp


#include "SkirmishBT_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTaskOwnerInterface.h"


USkirmishBT_FindRandomLocation::USkirmishBT_FindRandomLocation()
{
    NodeName = TEXT("Find Random Location");

    //accept only vectors
    BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(USkirmishBT_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type USkirmishBT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FNavLocation Location{};
    // Get AI Pawn
    AAIController* AIController = {OwnerComp.GetAIOwner()};
    const APawn* AIPawn = {AIController->GetPawn()};

    // Get Pawn Origin
    const FVector Origin {AIPawn->GetActorLocation()};


    // Obtain Navigation System and find a random location
    const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
    
    if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
    {
        Location.Location.Z = 10.f;
        UE_LOG(LogTemp, Display, TEXT("Location: %s"), *Location.Location.ToString());

        FVector Direction = Location.Location - AIPawn->GetActorLocation();
        Direction.Normalize();

        AIController->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, this);
        AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
    }

   

    // //Signal the BehaviorTreeComponent that the task finished successfully
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

FString USkirmishBT_FindRandomLocation::GetStaticDescription() const
{
    return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}