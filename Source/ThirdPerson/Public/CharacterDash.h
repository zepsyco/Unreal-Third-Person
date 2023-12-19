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
    // Distance du Dash
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashDistance;

    // Vitesse du Dash
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashUpwardSpeed;

    // Temps de recharge du Dash
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
    float DashCooldown;

    // Fonction pour déclencher le Dash
    UFUNCTION(BlueprintCallable, Category = "Dash")
    void StartDash();

private:
 	
	FTimerHandle DashCooldownTimerHandle;
    
	// Gérer l'état du Dash
    bool bCanDash;

    // Fonction pour effectuer le Dash
    void Dash();

    // Fonction pour réinitialiser le Dash après le temps de recharge
    void ResetDash();
};