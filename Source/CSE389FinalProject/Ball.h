// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ball.generated.h"

UCLASS()
class CSE389FINALPROJECT_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	// Function that initializes the projectile's velocity in the shoot direction
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(BlueprintCallable)
	void DestoryBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision Component
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComp;

	// Static mesh displaying our bullet
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp;

	// Component that we can use to make our actor move
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* PMComp;

	// Function that is called when the projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setPMCompVelocity(FVector);

};
