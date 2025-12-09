// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TriggerVolume.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
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

    FTimerHandle PauseHandle;

protected:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* Box;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UNiagaraSystem* GoalEffect;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
    UFUNCTION()
    void PauseGame();
};
