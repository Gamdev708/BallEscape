// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBallController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void APlayerBallController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBallController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{

		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Finished"));
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, 1.f);

}

void APlayerBallController::SetPlayerEnableState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}

