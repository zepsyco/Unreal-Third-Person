#include "CharacterDash.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// TODO: 
// - ajouter un effet de particules
// - ajouter un son
// - ajouter un effet de caméra

UCharacterDash::UCharacterDash()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame
    PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterDash::BeginPlay()
{
    Super::BeginPlay();

    // ...
}

void UCharacterDash::StartDash(int32 playerDashSpeed)
{
    DashSpeed = playerDashSpeed;

    if (bCanDash)
    {
        bCanDash = false;
        Dash();
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
                //OwnerMovement->MaxWalkSpeed = DashSpeed;
            }
        }
    }
}