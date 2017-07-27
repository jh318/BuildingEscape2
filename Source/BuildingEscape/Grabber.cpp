#include "Grabber.h"

#define OUT

UGrabber::UGrabber(){
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UGrabber::BeginPlay(){
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s Reporting for duty"), *GetOwner()->GetName());
	
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Found Physics Handle"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing physics component: %s"), *GetOwner()->GetName());
	}

	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input) {
		UE_LOG(LogTemp, Error, TEXT("Found input component on %s"), *input->GetOwner()->GetName());
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing input component"));
	}
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

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		playerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	AActor* actorHit = Hit.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *actorHit->GetName());
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab works"));
}

void UGrabber::Released() {
	UE_LOG(LogTemp, Warning, TEXT("Released works"));
}

