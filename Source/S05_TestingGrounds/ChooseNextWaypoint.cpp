// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"

UChooseNextWaypoint::UChooseNextWaypoint()
{
}
EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get The Patrol Route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() < 1) 
	{
		UE_LOG(LogTemp, Warning, TEXT("A Guard Is Missing Patrol Points"));
		return EBTNodeResult::Failed;
	}

	//Get Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle The Index
	auto NextWaypoint = (Index + 1) % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextWaypoint);

	return EBTNodeResult::Succeeded;
}