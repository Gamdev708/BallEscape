// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_GameModeBase.h"
#include "EngineUtils.h"
#include "BallEscape/Pawns/BallCharacter.h"
#include "BallEscape/Controllers/PlayerBallController.h"
#include"Kismet/GameplayStatics.h"

void AGM_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	BallPlayer = Cast<ABallCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerController = Cast<APlayerBallController>(UGameplayStatics::GetPlayerController(this, 0));
}

void AGM_GameModeBase::HandleGameOver(bool Playerwon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == Playerwon;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
	if (!Playerwon)
	{
		if (PlayerController)
		{
			PlayerController->SetPlayerEnableState(false);
		}
	}
}

void AGM_GameModeBase::ActorDied(AActor* DeadActor)
{
	
	if (DeadActor==BallPlayer)
	{
		//BallPlayer->HandleDestruction();
		HandleGameOver(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Died"));
	}
}
