#include "DonutTimerPhysics.h"

// Sets default values for this component's properties
UDonutTimerPhysics::UDonutTimerPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDonutTimerPhysics::InitMesh(UStaticMeshComponent* InitialMesh)
{
    getMesh = InitialMesh;
}
// Called when the game starts
void UDonutTimerPhysics::BeginPlay()
{
	Super::BeginPlay();

	// Get the mesh as a template to avoid crashing
	SetMesh();
}

void UDonutTimerPhysics::SetMesh()
{
	// Get the mesh as a template to avoid crashing
	if (GetOwner() && getMesh == nullptr) {
		getMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	}
}

// Called every frame, will be used for the timer
void UDonutTimerPhysics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDonutTimerPhysics::CountdownDestroy(int32 Time, int32 Action)
{
    Timer = Time, actionTimer = Action;

    // Schedule the countdown to happen every second
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UDonutTimerPhysics::CountdownTick, 1.0f, true);
}

void UDonutTimerPhysics::ResetMeshState()
{
    // Clear the timer handle
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    getMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    getMesh->SetVisibility(true);
}

void UDonutTimerPhysics::CountdownTick()
{
    Timer--;

    if (Timer <= 0 && getMesh) {
        ResetMeshState();
    }
    if (Timer == actionTimer && getMesh)
    {
        getMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        getMesh->SetVisibility(false);
    }

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("'UDonutTimerPhysics::CountdownTick' Timer is '%d'"), Timer));
}

bool UDonutTimerPhysics::IsOverlappingPlayer(AActor* PlayerActor)
{
    if (!PlayerActor)
    {
        return false;
    }

    // Check if the component is currently overlapping with the specified player actor
    TArray<AActor*> OverlappingActors;
    GetOwner()->GetOverlappingActors(OverlappingActors, PlayerActor->GetClass());

    return OverlappingActors.Contains(PlayerActor);
}