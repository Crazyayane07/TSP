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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SetUp")
	int NumberOfCities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float MaxRandomX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float MaxRandomY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetUp")
	float CitySpawnHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SetUp")
	TArray<ATSPCity*> Cities;

protected:
	virtual void BeginPlay() override;
};
