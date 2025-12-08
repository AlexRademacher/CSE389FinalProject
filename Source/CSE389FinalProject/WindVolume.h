// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "WindVolume.generated.h"

/**
 * 
 */
UCLASS()
class CSE389FINALPROJECT_API AWindVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
	AWindVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	float WindSpeed;

public:
	//overlap begin
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	//overlap end
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);


};
