// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	//OpenDoor();
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	//Find owning Actor
	//AActor *Owner = GetOwner();

	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f); //pitch, yaw, roll
    // Set rotation
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	// Set rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Poll the trigger volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		//If the ActorThatOpens within the volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	// ...
	// Check if its time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
	
}

