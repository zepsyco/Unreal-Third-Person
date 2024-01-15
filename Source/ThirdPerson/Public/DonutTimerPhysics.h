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

	float Timer;
	float actionTimer;
	float Precision = 0.01f;
	
	FTimerHandle CountdownTimerHandle;
    FTimerHandle ResetMeshTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Donut Timer Physics")
    UStaticMeshComponent* getMesh = nullptr;

protected:

	// Pointer to the mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut Timer Physics")
	UStaticMeshComponent* MeshComponent;

public:
	// Sets default values for this component's properties
	UDonutTimerPhysics();

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void InitMesh(UStaticMeshComponent* InitialMesh);

	// Function to start the destruction process
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void CountdownDestroy(float Time, float Action);
	void CountdownTick();
	void ResetMeshState();

	UFUNCTION(BlueprintCallable, Category = "MyActor Functions")
	bool IsOverlappingPlayer(AActor* PlayerActor);

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