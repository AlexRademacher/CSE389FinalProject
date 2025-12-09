// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrollingObstacle.generated.h"

UCLASS()
class CSE389FINALPROJECT_API APatrollingObstacle : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatrollingObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	// Booleans for detecting the player and attacking
	bool ballDetected;

	UPROPERTY(BlueprintReadOnly)
	bool canAttackBall;

	// A variable to hold a reference to our Player when we need it
	class AActor* Ball;

	// Collision for detecting the player near the enemy
	UPROPERTY(EditAnywhere)
	class USphereComponent* BallCollisionDetection;

	// Collision for detecting if the player can be attacked
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BallAttackCollision;

	class APatrollingAIController* AIController;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	UPROPERTY(EditAnywhere)
	float StoppingDistance = 200.0f;

	FTimerHandle SeekPlayerTimerHandle;

	UFUNCTION()
	void MoveToBall();

	UFUNCTION()
	void SeekBall();

	UFUNCTION()
	void StopSeekingBall();

	UFUNCTION()
	void OnBallDetectedOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBallDetectedOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBallAttackOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBallAttackOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
