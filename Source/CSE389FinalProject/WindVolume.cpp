// Fill out your copyright notice in the Description page of Project Settings.


#include "WindVolume.h"
#include "Ball.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AWindVolume::AWindVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AWindVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWindVolume::OnOverlapEnd);
	WindParticle = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, TEXT("/Game/Vefects/VFX_Wind.VFX_Wind")));
}

void AWindVolume::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WindParticle, this->GetActorLocation(), this->GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true);
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

			UPrimitiveComponent* UPC = Cast<UPrimitiveComponent>(Ball->GetRootComponent());

			if (UPC) {
				UPC->SetSimulatePhysics(true);

				UPC->AddForce(GetActorForwardVector() * Speed);
			}
		}
	}
}

void AWindVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
