// Fill out your copyright notice in the Description page of Project Settings.


#include "DonutTimerPhysics.h"

// Sets default values for this component's properties
UDonutTimerPhysics::UDonutTimerPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//get the mesh as a template to avoid crashing
	// if (getMesh == nullptr) {
	// 	getMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	// }

	// ...
}


// Called when the game starts
void UDonutTimerPhysics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDonutTimerPhysics::SetMesh(UStaticMeshComponent* InMesh)
{
	//get the mesh as a template to avoid crashing
	if (getMesh == nullptr) {
		getMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	}
}

// Called every frame, will be used for the timer
void UDonutTimerPhysics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDonutTimerPhysics::StartDestroy()
{
    // each second, decrease the timer by 1
    // when the timer reaches 0, return the mesh to its original state after 2 seconds

    if (timer > 0) {
        timer--;
    }
    else {
        // Disable physics and collisions
        getMesh->SetSimulatePhysics(false);
        getMesh->SetEnableGravity(false);
        getMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        getMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

        // Schedule the mesh to return to its original state after 2 seconds
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDonutTimerPhysics::ResetMeshState, 2.0f, false);
    }
}

void UDonutTimerPhysics::ResetMeshState()
{
    // Reset the mesh to its original state
    getMesh->SetSimulatePhysics(true);
    getMesh->SetEnableGravity(true);
    getMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    getMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}