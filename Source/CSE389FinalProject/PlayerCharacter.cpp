// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Score = 0;
	Health = 100;
	BallsLeft = 30;
	CanKick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp = FindComponentByClass<UCapsuleComponent>();

	if (CollisionComp)
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind the actions
	PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PEI->BindAction(InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	PEI->BindAction(InputKick, ETriggerEvent::Triggered, this, &APlayerCharacter::Kick);
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Empty for now will implement when needed
	//UE_LOG(LogTemp, Warning, TEXT("Ouch! Health: %d"), Health);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr) {
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		// Foward/Backward direction
		if (MoveValue.Y != 0.f) {
			// Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}

		// Right/Left direction
		if (MoveValue.X != 0.f) {
			// Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Value.ToString());

		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f) {
			AddControllerYawInput(LookValue.X);
		}

		if (LookValue.Y != 0.f) {
			AddControllerPitchInput(-LookValue.Y);
		}
	}
}

void APlayerCharacter::Kick(const FInputActionValue& Value)
{
	if (GetBallsLeft() > 0) {
		SetBallsLeft(GetBallsLeft() - 1);

		// Set ProjectileSpawn to spawn projectiles slightly in front of the character
		BallSpawn.Set(50.0f, 0.0f, -40.0f);

		// Transform ProjectileSpawn from local space to world space
		FVector SpawnLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(BallSpawn);

		// Skew the aim to be slightly upwards
		FRotator SpawnRotation = GetActorRotation();
		SpawnRotation.Pitch += 20.0f;

		// Give our projectile some metadata
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn the projectile using our locations and metadata
		ABall* Ball = GetWorld()->SpawnActor<ABall>(SpawnLocation, SpawnRotation, SpawnParams);

		if (Ball) {
			// Set the projectile's initial trajectory
			FVector LaunchDirection = SpawnRotation.Vector();
			Ball->FireInDirection(LaunchDirection);

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Kicked!"));
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Out Of Balls"));
	}
}

void APlayerCharacter::SetScore(int NewScore)
{
	Score = NewScore;
	UE_LOG(LogTemp, Warning, TEXT("%d"), Score);
}

int APlayerCharacter::GetScore()
{
	return Score;
}

int APlayerCharacter::GetHealth()
{
	return Health;
}

void APlayerCharacter::SetBallsLeft(int BallAmount)
{
	BallsLeft = BallAmount;
}

int APlayerCharacter::GetBallsLeft()
{
	return BallsLeft;
}


