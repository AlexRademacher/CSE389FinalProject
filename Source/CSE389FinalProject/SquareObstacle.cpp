// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareObstacle.h"

// Sets default values
ASquareObstacle::ASquareObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASquareObstacle::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
	
}

// Called every frame
void ASquareObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	double X = Location.X;
	double Y = Location.Y;
	

	if (Location == StartingLocation)
	{
		Direction = FVector(5.0f, 0.0f, 0.0f);
	}
	if (X >= (StartingLocation.X + 100) && Y == StartingLocation.Y)
	{
		Direction = FVector(0.0f, 5.0f, 0.0f);
	}
	if (Y >= (StartingLocation.Y + 100) && X >= (StartingLocation.X + 100))
	{
		Direction = FVector(-5.0f, 0.0f, 0.0f);
	}
	if (X <= StartingLocation.X && Y >= StartingLocation.Y + 100)
	{
		Direction = FVector(0.0f, -5.0f, 0.0f);
	}

	AddActorWorldOffset(Direction);

}

