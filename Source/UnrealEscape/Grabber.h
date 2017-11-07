// Copyleft

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void BindInputComponent();

	void BindPhysicsHandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float Reach = 100.0f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputCompoment = nullptr;
	
	// Ray-cast and grab what's in reach
	void Grab();

	// Ray-cast and grab what's in reach
	void Release();
	
	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
