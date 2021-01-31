// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/TSPProblemManager.h"
#include "Math/Vector.h"
#include "City/TSPCity.h"

ATSPProblemManager::ATSPProblemManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATSPProblemManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < Cities.Num(); i++) 
	{
		DefaultOrder.Add(i);
	}

	for (int i = 0; i < NumberOfPopulations; i++) 
	{
		TArray<int> ArrayToAdd;
		ArrayToAdd.Append(Shuffle(DefaultOrder));

		Populations.Add(ArrayToAdd);
	}

	for (int i = 0; i < Populations.Num(); i++)
	{
		Fitness.Add(CalculateDistance(Populations[i]));

		if (Fitness[i] < RecordDistance || RecordDistance == -1.0f)
		{
			RecordDistance = Fitness[i];
			BestCitiesOrder = Populations[i];
		}
	}

	DrawSolution();
}

void ATSPProblemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATSPProblemManager::CalculateDistance(const TArray<int>& Array)
{
	float sum = 0.0f;

	for (int i = 0; i < Array.Num() - 1; i++)
	{
		int CityAId = Array[i];
		int CityBId = Array[i + 1];

		float dist = FVector::Dist(Cities[CityAId]->GetActorLocation(), Cities[CityBId]->GetActorLocation());

		sum += dist;
	}

	return sum;
}

