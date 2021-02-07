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
}

void ATSPProblemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateFitness();
	NormalizeFitness();
	CalculateNextGeneration();
	DrawSolution();

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

void ATSPProblemManager::CalculateFitness()
{
	for (int i = 0; i < Populations.Num(); i++)
	{
		float Distance = CalculateDistance(Populations[i]);
		Fitness.Add(1 / (Distance + 1));

		if (Distance < RecordDistance || RecordDistance == -1.0f)
		{
			RecordDistance = Distance;
			BestCitiesOrder = Populations[i];
			ShowNewBest(BestCitiesOrder, RecordDistance);
		}
	}
}

void ATSPProblemManager::NormalizeFitness()
{
	float sum = 0.0f;

	for (int i = 0; i < Fitness.Num(); i++) 
	{
		sum += Fitness[i];
	}
	for (int i = 0; i < Fitness.Num(); i++)
	{
		Fitness[i] = Fitness[i] / sum;
	}
}

void ATSPProblemManager::CalculateNextGeneration()
{
	TArray<TArray<int>> NewPopulations;

	for (int i = 0; i < Populations.Num(); i++) 
	{
		TArray<int> PopulationA = GetPopulation();
		TArray<int> PopulationB = GetPopulation();

		TArray<int> Population = Crossover(PopulationA, PopulationB);

		Mutate(Population);
		NewPopulations.Add(Population);
	}

	Populations.Empty();
	Populations.Append(NewPopulations);
}

TArray<int> ATSPProblemManager::GetPopulation()
{
	int id = 0;
	float r = FMath::FRandRange(0.0f, 1.0f);

	while (r > 0.0f) {
		r = r - Fitness[id];
		id++;
	}
	id--;

	if (id < 0)
	{
		return Populations[0];
	}

	if (id >= Populations.Num())
	{
		return Populations[Populations.Num()-1];
	}

	return Populations[id];
}

TArray<int> ATSPProblemManager::Crossover(const TArray<int>& PopulationA, const TArray<int>& PopulationB)
{
	int startOrder = FMath::FRandRange(0.0f, PopulationA.Num() - 1);
	int endOrder = FMath::FRandRange(startOrder, PopulationA.Num() - 1);

	TArray<int> NewPopulation;

	for (int i = startOrder; i <= endOrder; i++)
	{
		NewPopulation.Add(PopulationA[i]);
	}

	for (int i = 0; i < PopulationB.Num(); i++) 
	{
		int City = PopulationB[i];
		if (!NewPopulation.Contains(City)) 
		{
			NewPopulation.Add(City);
		}
	}

	return NewPopulation;
}

void ATSPProblemManager::Mutate(TArray<int>& Array)
{
	int idA = FMath::RandRange(0, Array.Num() - 1);
	int idB = FMath::RandRange(0, Array.Num() - 1);

	int temp = Array[idA];
	Array[idA] = Array[idB];
	Array[idB] = temp;
}

