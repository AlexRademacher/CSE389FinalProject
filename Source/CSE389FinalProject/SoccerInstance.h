// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SoccerInstance.generated.h"

/**
 * 
 */
UCLASS()
class CSE389FINALPROJECT_API USoccerInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	// Score saved between levels
	UPROPERTY(BlueprintReadWrite)
	int32 SavedScore = 0;
};
