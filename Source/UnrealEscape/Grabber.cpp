// Copyleft

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber is here!"));
	InputCompoment = GetOwner()->FindComponentByClass<UInputComponent>();

	BindPhysicsHandle();
	BindInputComponent();
}

void UGrabber::BindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Physics component"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	GetFirstPhysicsBodyInReach();
}


void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerPosition;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPosition, PlayerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Grabber: player view point postion %s, rotation %s"), *PlayerPostion.ToCompactString(), *PlayerRotation.ToCompactString());

	FVector LineTraceEnd = PlayerPosition + (PlayerRotation.Vector() * Reach);

	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerPosition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}

	return FHitResult();
}

void UGrabber::BindInputComponent()
{
	if (InputCompoment)
	{
		InputCompoment->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputCompoment->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Component"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

