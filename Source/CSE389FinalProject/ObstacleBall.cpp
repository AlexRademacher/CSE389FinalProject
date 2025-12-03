// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBall.h"

// Sets default values
AObstacleBall::AObstacleBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Change new location by 5 along x and change rotation by 5 along roll axis
	FVector NewLoc = FVector(5.0f, 0.0f, 0.0f);
	FRotator NewRot = FRotator(-5.0f, 0.0f, 0.0f);

	AddActorWorldOffset(NewLoc);
	AddActorLocalRotation(NewRot);
}

