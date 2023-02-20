// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerBallController.generated.h"

/**
 * 
 */
UCLASS()
class BALLESCAPE_API APlayerBallController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void SetPlayerEnableState(bool SetPlayerEnabled);

private:
	UPROPERTY(EditAnywhere) TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere) TSubclassOf<class UUserWidget> WinScreenClass;
	
	FTimerHandle RestartTimer;
};
