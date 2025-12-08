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
	
	this->SetLifeSpan(10.f);

	actorYaw = GetActorRotation().Yaw;
}

// Called every frame
void AObstacleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	//Change new location by 5 along x and change rotation by 5 along roll axis
	FRotator oldRotation = GetActorRotation();
	
	SetActorRotation(FRotator(0.f, actorYaw, 0.f));


	FVector NewLoc = FVector(250.f, 0.f, 0.f) * DeltaTime;
	AddActorLocalOffset(NewLoc);

	SetActorRotation(oldRotation);
	FRotator NewRot = FRotator(-90.0f, 0.0f, 0.0f) * DeltaTime;
	
	AddActorLocalRotation(NewRot);
}

