// Fill out your copyright notice in the Description page of Project Settings.


#include "ForwardObstacle.h"

// Sets default values
AForwardObstacle::AForwardObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AForwardObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	this->SetLifeSpan(10.f);
}

// Called every frame
void AForwardObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLoc = Direction;
	AddActorWorldOffset(NewLoc);
}

