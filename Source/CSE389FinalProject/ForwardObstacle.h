// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForwardObstacle.generated.h"

UCLASS()
class CSE389FINALPROJECT_API AForwardObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForwardObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	FVector Direction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
