// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WindBox.generated.h"

/**
 * 
 */
UCLASS()
class CSE389FINALPROJECT_API AWindBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AWindBox();

protected:
	virtual void BeginPlay() override;

public:
	//overlap begin
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	//overlap end
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);


};
