// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a generic SceneComponent as the root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision profile name to "Projectile"
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("SoccerBall"));
	// Event called when component hits something
	CollisionComp->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	// Set the sphere's collision radius
	CollisionComp->InitSphereRadius(6.0f);

	// Set the root component to be the collision component
	RootComponent = CollisionComp;

	// Create and set up the mesh component to be our imported bullet mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Game/Assets/soccer-ball-football/source/Football.Football"));

	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
		MeshComp->SetRelativeScale3D(FVector(1.25f, 1.25f, 1.25f));

		static ConstructorHelpers::FObjectFinder<UMaterial> SoccerBall(TEXT("/Game/Assets/soccer-ball-football/textures/Football_Mat.Football_Mat"));

		// If we successfully found our material, apply it to our mesh
		if (SoccerBall.Succeeded()) {
			MeshComp->SetMaterial(0, SoccerBall.Object);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *SoccerBall.Object.GetName());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Material Unsuccessful"));
		}
	}

	// Use this to drive this projectile's movement
	PMComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	PMComp->SetUpdatedComponent(CollisionComp);
	PMComp->InitialSpeed = 1500.f;
	PMComp->MaxSpeed = 1500.f;
	PMComp->bRotationFollowsVelocity = true;
	PMComp->bShouldBounce = true;
	PMComp->Bounciness = 0.8f;
	PMComp->ProjectileGravityScale = 1.0f; // no gravity

	InitialLifeSpan = 8.0f;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABall::setPMCompVelocity(FVector wind)
{
	PMComp->Velocity = wind * PMComp->Velocity;
}

void ABall::FireInDirection(const FVector& ShootDirection)
{
	PMComp->Velocity = ShootDirection * PMComp->InitialSpeed;
}

void ABall::DestoryBall()
{
	this->Destroy();
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
		//OtherComponent->AddImpulseAtLocation(PMComp->Velocity * 100.0f, Hit.ImpactPoint);
	}
}