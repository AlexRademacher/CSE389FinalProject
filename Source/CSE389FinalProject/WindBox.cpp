// Fill out your copyright notice in the Description page of Project Settings.


#include "WindBox.h"
#include "Ball.h"

AWindBox::AWindBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AWindBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWindBox::OnOverlapEnd);
}

void AWindBox::BeginPlay()
{
	Super::BeginPlay();
}

void AWindBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector NewLoc = FVector(0.f, 1.f, 0.f);
	NewLoc = WindDirection;
	Cast<ABall>(OtherActor)->setPMCompVelocity(NewLoc);
}

void AWindBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
