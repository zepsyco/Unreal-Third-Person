#include "DonutTimerPhysics.h"

// Sets default values for this component's properties
UDonutTimerPhysics::UDonutTimerPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
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

	// Uncomment the following lines if needed for debugging
	//UE_LOG(LogTemp, Display, TEXT("I am indeed ticking with '%f'"), DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("'UDonutTimerPhysics::Tick' Ticking with '%f' DeltaTime"), DeltaTime));
}

void UDonutTimerPhysics::StartDestroy(AActor* PlayerActor)
{
    if (!PlayerActor || Timer > 0)
    {
        return;
    }

    // Set the initial timer value
    Timer = 2;

    // Schedule the countdown to happen every second
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UDonutTimerPhysics::CountdownTick, 1.0f, true);
}

void UDonutTimerPhysics::CountdownTick()
{
    if (Timer <= 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
        return;
    }

    // Decrease the timer by 1 second each tick
    Timer--;

    // Display the timer on screen
    UE_LOG(LogTemp, Warning, TEXT("Timer: %d"), Timer);
}

void UDonutTimerPhysics::ResetMeshState()
{
    if (MeshComponent)
    {
        // Reset the mesh to its original state
        // ...

        // Clear the timer handle
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    }
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