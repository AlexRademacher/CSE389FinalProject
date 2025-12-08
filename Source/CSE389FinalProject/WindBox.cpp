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
	Cast<ABall>(OtherActor)->setPMCompVelocity(FVector(0.f, 10.f, 0.f));
}

void AWindBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
