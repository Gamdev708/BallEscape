// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include"Kismet/GameplayStatics.h"
// Sets default values
ABallCharacter::ABallCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	RootComponent = StaticMesh;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}



void ABallCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	bCanJump = true;
}

// Called to bind functionality to input
void ABallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABallCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABallCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed, this, &ABallCharacter::Jump);
}



void ABallCharacter::MoveForward(float AxisValue)
{
	const FVector Torque = FVector(0.f, AxisValue * RotationRate, 0.f);
	StaticMesh->AddTorqueInRadians(Torque);
}

void ABallCharacter::MoveRight(float AxisValue)
{
	const FVector Torque = FVector(-1.f * AxisValue * RotationRate, 0.f, 0.f);
	StaticMesh->AddTorqueInRadians(Torque);
}

void ABallCharacter::Jump()
{	
	if (bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpForce);
		StaticMesh->AddImpulse(Impulse);
		bCanJump = false;
	}
	
	
	//UE_LOG(LogTemp,Warning,TEXT(EMovementMode))

}





