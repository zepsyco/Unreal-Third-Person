#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DonutTimerPhysics.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSON_API UDonutTimerPhysics : public UActorComponent
{
	GENERATED_BODY()

private:
	int32 Timer;
	FTimerHandle CountdownTimerHandle;
    FTimerHandle ResetMeshTimerHandle;
	
	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* getMesh = nullptr;

protected:
	// Pointer to the mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut Timer Physics")
	UStaticMeshComponent* MeshComponent;

public:
	// Sets default values for this component's properties
	UDonutTimerPhysics();

	// Function to start the destruction process
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void StartDestroy(AActor* PlayerActor);

	// Function to check if the component is overlapping with a player
	UFUNCTION(BlueprintCallable, Category = "MyActor Functions")
	bool IsOverlappingPlayer(AActor* PlayerActor);

	// Function to be called on each tick of the countdown timer
	void CountdownTick();

	// Function to reset the mesh state
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void ResetMeshState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Function to set the mesh component
	UFUNCTION(BlueprintCallable, Category = "Donut Timer Physics")
	void SetMesh();
};