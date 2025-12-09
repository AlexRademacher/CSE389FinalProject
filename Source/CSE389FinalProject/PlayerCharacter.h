// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Ball.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CSE389FINALPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputKick;

	// Yoinking collision component from BP of Character
	UCapsuleComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BallSpawn;

	// Variable to hold the score when you shoot something
	int Score;

	// Score variable for Controllable Character
	int Health;

	// Number of Balls left
	int BallsLeft;

	// If the player can kick
	bool CanKick;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Function that handles wasd movement
	void Move(const FInputActionValue& Value);
	// Function that handles mouse looking around
	void Look(const FInputActionValue& Value);
	// Function that handles mouse looking around
	void Kick(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Setter for Score Variable
	UFUNCTION()
	void SetScore(int NewScore);

	// Getter for Score Variable
	UFUNCTION(BlueprintCallable)
	int GetScore();

	UFUNCTION(BlueprintCallable)
	int GetHealth();

	UFUNCTION()
	void SetBallsLeft(int BallAmount);

	UFUNCTION(BlueprintCallable)
	int GetBallsLeft();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
