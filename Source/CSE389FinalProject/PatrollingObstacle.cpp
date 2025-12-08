// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingObstacle.h"
#include "Ball.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "PatrollingAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"

// Sets default values
APatrollingObstacle::APatrollingObstacle()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision Detection"));
	BallCollisionDetection->SetupAttachment(RootComponent);

	BallAttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Attack Collision"));
	BallAttackCollision->SetupAttachment(GetMesh(), TEXT("Cone"));

	ballDetected = false;
	canAttackBall = false;
}

// Called when the game starts or when spawned
void APatrollingObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	// Give our Controller over to our PatrollingAIController class an save the reference
	AIController = Cast<APatrollingAIController>(GetController());

	// When we've completed any path following (e.g., walking around), call OnAIMoveCompleted
	AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &APatrollingObstacle::OnAIMoveCompleted);
	
	// Add links to functions so tat our Enemy will react to the following events
	BallCollisionDetection->OnComponentBeginOverlap.AddDynamic(this,
		&APatrollingObstacle::OnBallDetectedOverlapBegin);

	BallCollisionDetection->OnComponentEndOverlap.AddDynamic(this,
		&APatrollingObstacle::OnBallDetectedOverlapEnd);

	BallAttackCollision->OnComponentBeginOverlap.AddDynamic(this,
		&APatrollingObstacle::OnBallAttackOverlapBegin);

	BallAttackCollision->OnComponentEndOverlap.AddDynamic(this,
		&APatrollingObstacle::OnBallAttackOverlapEnd);
}

// Called every frame
void APatrollingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrollingObstacle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrollingObstacle::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!ballDetected)
	{
		AIController->RandomPatrol();
	}
}

void APatrollingObstacle::MoveToBall()
{
	if (Ball)
		AIController->MoveToLocation(Ball->GetActorLocation(), StoppingDistance, true);
}

void APatrollingObstacle::SeekBall()
{
	// Move to the player and continue to seek the player out while the timer is running
	MoveToBall();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this,
		&APatrollingObstacle::SeekBall, 0.25f, true);
}

void APatrollingObstacle::StopSeekingBall()
{
	// When we can no longer see the player and it's time to stop looking, we clear the timer
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);
}

void APatrollingObstacle::OnBallDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Ball")) {
		Ball = Cast<AActor>(OtherActor);

		if (Ball)
		{
			ballDetected = true;
			SeekBall();
		}
	}
}

void APatrollingObstacle::OnBallDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetName().Contains("Ball")) {
		Ball = Cast<AActor>(OtherActor);

		if (Ball)
		{
			ballDetected = false;
			StopSeekingBall();
			AIController->RandomPatrol();
		}
	}
}

void APatrollingObstacle::OnBallAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Ball")) {
		Ball = Cast<AActor>(OtherActor);

		if (Ball)
		{
			ballDetected = true;
			canAttackBall = true;

			ABall* BallScript = Cast<ABall>(Ball);

			if (BallScript)
			{
				BallScript->DestoryBall();
			}

			// deal damage to the player
			UE_LOG(LogTemp, Warning, TEXT("Ball Destroyed"));
		}
	}
}

void APatrollingObstacle::OnBallAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetName().Contains("Ball")) {
		Ball = Cast<AActor>(OtherActor);

		if (Ball)
		{
			canAttackBall = false;

			SeekBall();
		}
	}
}


