#include "Grabber.h"

#define OUT

UGrabber::UGrabber(){
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UGrabber::BeginPlay(){
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s Reporting for duty"), *GetOwner()->GetName());
	
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("ViewPoint Location: %s ViewPointRotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());

	FVector LineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
		);
}

