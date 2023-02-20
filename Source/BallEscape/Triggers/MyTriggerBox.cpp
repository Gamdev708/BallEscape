#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "MyTriggerBox.h"
#include "BallEscape/Controllers/PlayerBallController.h"
#include "BallEscape/GameMode/GM_GameModeBase.h"
// include draw debug helpers header file
#include "DrawDebugHelpers.h"
#include"Kismet/GameplayStatics.h"


AMyTriggerBox::AMyTriggerBox()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this,&AMyTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor)
    {
        print("Overlap Begin");
        printFString("Overlapping Actor = %s", *OtherActor->GetName());
        GameModeRef->HandleGameOver(true);
    }
}

void AMyTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor)
    {
        print("Overlap End");
        printFString("%s has left the Trigger Box", *OtherActor->GetName());
    }
}

void AMyTriggerBox::BeginPlay()
{
    Super::BeginPlay();
    GameModeRef = Cast<AGM_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, -1, 0, 5);
}


