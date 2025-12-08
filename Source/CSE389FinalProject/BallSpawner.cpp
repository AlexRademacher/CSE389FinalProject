// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawner.h"
#include "Components/BoxComponent.h"
#include "ObstacleBall.h"

// Sets default values
ABallSpawner::ABallSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnActor();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABallSpawner::SpawnActor, timer, true);
}

// Called every frame
void ABallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallSpawner::SpawnActor()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	FVector SpawnScale = GetActorScale3D();

	AActor* spawnedBall = GetWorld()->SpawnActor<AActor>(ObstacleBall, GetActorLocation(), GetActorRotation());

	spawnedBall->SetActorScale3D(SpawnScale);

	
	//GetWorld()->SpawnActor<AObstacleBall>(SpawnLocation, SpawnRotation);
}