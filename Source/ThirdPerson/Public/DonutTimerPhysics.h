#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DonutTimerPhysics.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSON_API UDonutTimerPhysics : public UActorComponent
{
	GENERATED_BODY()

	int timer = 2;
	UStaticMeshComponent* getMesh = nullptr;

public:
	// Sets default values for this component's properties
	UDonutTimerPhysics();

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void StartDestroy();

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void ResetMeshState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Expose la propriété à Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut Timer Physics")
	UStaticMeshComponent* MeshComponent = nullptr;

	// Fonction Blueprint qui prend un mesh en paramètre
	UFUNCTION(BlueprintCallable, Category = "Donut Timer Physics")
	void SetMesh(UStaticMeshComponent* InMesh);
};