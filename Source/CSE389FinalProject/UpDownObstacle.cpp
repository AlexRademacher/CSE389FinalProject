// Fill out your copyright notice in the Description page of Project Settings.


#include "UpDownObstacle.h"

// Sets default values
AUpDownObstacle::AUpDownObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUpDownObstacle::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
}

// Called every frame
void AUpDownObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	double Z = Location.Z;

	if (Location == StartingLocation) 
		Direction = FVector(0.0f, 0.0f, 5.0f);
	else if (Z >= (StartingLocation.Z + 300))
		Direction = FVector(0.0f, 0.0f, -5.0f);

	AddActorWorldOffset(Direction);
}

