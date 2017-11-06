// Copyleft

#include "OpenDoor.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UOpenDoor::AGetPlayer()
{
	if (GetWorld() != nullptr && GetWorld()->GetFirstPlayerController() != nullptr)
	{
		auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		return (AActor *) Pawn;
	}
	else {
		if (GetWorld() == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GetWorld is empty"));
		}
		else if (GetWorld()->GetFirstPlayerController() == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GetFirstPlayerController is empty"));
		}
		return nullptr;
	}
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = AGetPlayer();
	
}

void UOpenDoor::SetDoorAngle(float Angle) 
{
	AActor* Owner = GetOwner();
	FRotator Rotation = Owner->GetActorRotation();
	FRotator NewRotation = FRotator(0.0f, Angle, 0.0f);
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::OpenDoor()
{
	SetDoorAngle(180.0f);

}

void UOpenDoor::CloseDoor()
{
	SetDoorAngle(90.0f);

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Player = AGetPlayer();

	float now = GetWorld()->GetTimeSeconds();
	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			OpenDoor();
			DoorOpenedTime = now;
		}
	}
	if (DoorOpenedTime && (now - DoorOpenedTime) > DoorCloseDelay)
	{
		CloseDoor();
	}
	
	// ...
}

