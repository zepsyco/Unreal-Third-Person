#include "CharacterDash.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// TODO: 
// - empêcher un autre dash tant que le joueur est en l'air
// - empêcher un autre dash tant que le joueur est en train de dasher
// - inverser les axes de déplacement
// - ajouter un effet de particules
// - ajouter un son
// - ajouter un effet de caméra

UCharacterDash::UCharacterDash()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize default values
    DashDistance = 1000.0f;
    DashSpeed = 500.0f;
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
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        // Obtenez le contrôleur du propriétaire
        AController* OwnerController = OwnerCharacter->GetController();
        if (OwnerController)
        {
            // Obtenez le mouvement du propriétaire (peut être le mouvement d'un personnage, d'un véhicule, etc.)
            UCharacterMovementComponent* OwnerMovement = OwnerCharacter->GetCharacterMovement();
            if (OwnerMovement)
            {
                // Obtenez la direction de Dash
                FVector ForwardVector = OwnerCharacter->GetActorForwardVector();

                FVector DashDirection = FVector(0.f, ForwardVector.Y, ForwardVector.Z);
                DashDirection.Normalize();

                // Calculez la vélocité en fonction de la direction et de la vitesse de dash
                FVector DashVelocity = DashDirection * DashSpeed;

                // Appliquez une impulsion au personnage
                OwnerCharacter->LaunchCharacter(DashVelocity, true, true);

                // Ajustez la vitesse de déplacement si nécessaire
                OwnerMovement->MaxWalkSpeed = DashSpeed;
            }
        }
    }
}