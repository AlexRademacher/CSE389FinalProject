// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalVolume.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AGoalVolume::AGoalVolume()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetCollisionProfileName("OverlapAllDynamic");
	Box->OnComponentBeginOverlap.AddDynamic(this, &AGoalVolume::OnOverlapBegin);

}
void AGoalVolume::PauseGame()
{
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}
void AGoalVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor->IsA(ABall::StaticClass()))
    {

        APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

        if (Player)
        {
            int32 NewScore = Player->GetScore() + 1;
            Player->SetScore(NewScore);
            if (GoalEffect)
            {
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    GoalEffect,
                    GetActorLocation()
                );
            }
            AGameModeBase* GM = GetWorld()->GetAuthGameMode(); 
            if (GM)
            {
                FName FunctionName = "ShowNextLevel"; 
                UFunction* Function = GM->FindFunction(FunctionName);
                if (Function)
                {
                    GM->ProcessEvent(Function, nullptr); 
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Function %s not found in GameMode!"), *FunctionName.ToString());
                }
            }
            OtherActor->Destroy();

            GetWorldTimerManager().SetTimer(PauseHandle,this,&AGoalVolume::PauseGame,2.0f,false
            );
        }
    }
}
