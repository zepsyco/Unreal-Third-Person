// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDash.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSON_API UCharacterDash : public UActorComponent
{
    GENERATED_BODY()

public:    
    // Sets default values for this component's properties
    UCharacterDash();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:

    // Vitesse du Dash
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashUpwardSpeed;

    // Fonction pour déclencher le Dash
    UFUNCTION(BlueprintCallable, Category = "Dash")
    void StartDash(int32 playerDashSpeed);

private:
 	
	FTimerHandle DashCooldownTimerHandle;
    
	// Gérer l'état du Dash
    bool bCanDash = true;

    // Fonction pour effectuer le Dash
    void Dash();

    // Fonction pour réinitialiser le Dash après le temps de recharge
    UFUNCTION(BlueprintCallable, Category = "Dash")
    void ResetDash();
};