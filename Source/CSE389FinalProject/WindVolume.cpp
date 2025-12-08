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
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	if (OtherActor->GetName().Contains("Ball")) {
		UE_LOG(LogTemp, Warning, TEXT("Ball Found"));
		AActor* Ball = Cast<AActor>(OtherActor);

		if (Ball) {
			UE_LOG(LogTemp, Warning, TEXT("Wind Applied"));
			float Speed = WindSpeed;

			Cast<ABall>(Ball)->setPMCompVelocity(FVector(1.f * Speed, 1.f, 1.f));
		}
	}
}

void AWindVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
