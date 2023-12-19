#include "CharacterDash.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

UCharacterDash::UCharacterDash()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize default values
    DashDistance = 1000.0f;
    DashSpeed = 1000.0f;
    DashCooldown = 2.0f;
    bCanDash = true;
}

void UCharacterDash::BeginPlay()
{
    Super::BeginPlay();

    // ...
}

void UCharacterDash::StartDash()
{
    if (bCanDash)
    {
        bCanDash = false;
        // Appeler votre fonction de dash ici
        Dash();
        // Démarrez un minuteur pour le temps de recharge
        GetWorld()->GetTimerManager().SetTimer(DashCooldownTimerHandle, this, &UCharacterDash::ResetDash, DashCooldown, false);
    }
}

void UCharacterDash::ResetDash()
{
    bCanDash = true;
}

void UCharacterDash::Dash()
{
    // Obtenir l'acteur propriétaire du composant (peut être un personnage, un véhicule, etc.)
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        // Obtenez le contrôleur du propriétaire
        AController* OwnerController = OwnerActor->GetInstigatorController();
        if (OwnerController)
        {
            // Obtenez le mouvement du propriétaire (peut être le mouvement d'un personnage, d'un véhicule, etc.)
            UCharacterMovementComponent* OwnerMovement = OwnerActor->FindComponentByClass<UCharacterMovementComponent>();
            if (OwnerMovement)
            {
                // Obtenez la direction de Dash
                FVector DashDirection = OwnerActor->GetActorForwardVector() * DashDistance;

                // Obtenez la position après Dash
                FVector DashLocation = OwnerActor->GetActorLocation() + DashDirection;

                // Déplacez l'acteur vers la nouvelle position
                OwnerController->SetControlRotation(DashDirection.Rotation());
                OwnerActor->SetActorLocation(DashLocation);

                // Ajustez la vitesse de déplacement si nécessaire
                OwnerMovement->MaxWalkSpeed = DashSpeed;
            }
        }
    }
}