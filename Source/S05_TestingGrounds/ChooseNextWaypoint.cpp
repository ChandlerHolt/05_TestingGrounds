// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"




UChooseNextWaypoint::UChooseNextWaypoint()
{
}
EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Donkey"));
	return EBTNodeResult::Succeeded;
}