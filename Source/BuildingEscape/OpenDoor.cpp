#include "OpenDoor.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay(){
	Super::BeginPlay();

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorThatOpens))
	{
		OpenDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	AActor *owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, 60.0f, 0.0f);
	owner->SetActorRotation(newRotation);
}
