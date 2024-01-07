// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StrawberryBonus.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSON_API UStrawberryBonus : public UActorComponent
{
	GENERATED_BODY()

	bool bHarvested = false;
	bool bFlyAway = false;
	bool bOnce = false;

public:	
	// Sets default values for this component's properties
	UStrawberryBonus();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Mechanics")
	void MarkScore(int32 &Score);

	UFUNCTION(BlueprintCallable, Category = "Mechanics")
	void Disappear(UStaticMeshComponent* FruitMesh);

	UFUNCTION(BlueprintCallable, Category = "Mechanics")
	void CheckCharacterDash(bool bHasWings, bool bIsDashing);
	
	UFUNCTION(BlueprintCallable, Category = "Mechanics")
	void FlyUp(UStaticMeshComponent* FruitMesh, float Seconds);
};
