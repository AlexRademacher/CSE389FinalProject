// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TriggerVolume.h"
#include "GoalVolume.generated.h"

/**
 * 
 */
UCLASS()
class CSE389FINALPROJECT_API AGoalVolume : public ATriggerVolume
{
	GENERATED_BODY()
public:
    AGoalVolume();

protected:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* Box;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
