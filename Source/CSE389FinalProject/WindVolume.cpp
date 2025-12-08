// Fill out your copyright notice in the Description page of Project Settings.


#include "WindVolume.h"
#include "Ball.h"

AWindVolume::AWindVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AWindVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWindVolume::OnOverlapEnd);
}

void AWindVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AWindVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->GetName().Contains("Ball")) {
		AActor* Ball = Cast<AActor>(OtherActor);

		if (Ball) {
			FVector NewLoc = FVector(0.f, 1.f, 0.f);
			NewLoc = WindDirection;

			Cast<ABall>(Ball)->setPMCompVelocity(NewLoc);
		}
	}
}

void AWindVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
