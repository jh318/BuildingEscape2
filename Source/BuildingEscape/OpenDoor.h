// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOpenDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	void OpenDoor();
	void CloseDoor();

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float openAngle = 90.0f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;


	float lastDoorOpenTime;

	AActor *owner;

	float GetTotalMassOfActorsOnPlate();
};
