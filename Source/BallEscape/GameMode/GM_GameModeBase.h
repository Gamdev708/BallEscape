// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BallEscape/Pawns/BallCharacter.h"
#include "GM_GameModeBase.generated.h"

class APlayerBallController;
/**
 * 
 */
UCLASS()
class BALLESCAPE_API AGM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	ABallCharacter* BallPlayer;
	APlayerBallController* PlayerController;

public:
	void ActorDied(AActor* DeadActor);
	void HandleGameOver(bool Playerwon);
};
