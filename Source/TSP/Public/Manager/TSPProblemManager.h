// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSPProblemManager.generated.h"

class ATSPCity;

UCLASS()
class TSP_API ATSPProblemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATSPProblemManager();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category="Helper")
	TArray<int> Shuffle(const TArray<int>& OriginalArray);

	UFUNCTION(BlueprintImplementableEvent, Category = "Helper")
	void DrawSolution();

	float CalculateDistance(const TArray<int>& Array);

	void CalculateDFitness();

	void NormalizeFitness();

	void CalculateNextGeneration();

	TArray<int> PickOne();

	void Mutate(TArray<int>& Array);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SetUp")
	int NumberOfCities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	int NumberOfPopulations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float MaxRandomX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float MaxRandomY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float CitySpawnHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SetUp")
	TArray<ATSPCity*> Cities;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TSP")
	float RecordDistance = -1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TSP")
	TArray<int> BestCitiesOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TSP")
	TArray<int> DefaultOrder;

	TArray<TArray<int>> Populations;

	TArray<float> Fitness;

protected:
	virtual void BeginPlay() override;
};
