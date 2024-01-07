// Fill out your copyright notice in the Description page of Project Settings.


#include "StrawberryBonus.h"

// Sets default values for this component's properties
UStrawberryBonus::UStrawberryBonus()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStrawberryBonus::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStrawberryBonus::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStrawberryBonus::MarkScore(int32 &Score)
{
    if (!bHarvested) {
        Score += 1000;
    	bHarvested = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Strawberry Bonus!\n +1000"));
	}
}

void UStrawberryBonus::Disappear(UStaticMeshComponent* FruitMesh)
{
    FruitMesh->SetVisibility(false);
}

void UStrawberryBonus::CheckCharacterDash(bool bHasWings, bool bIsDashing)
{
	if (bHasWings && bIsDashing) {
		bFlyAway = true;
	}
}

void UStrawberryBonus::FlyUp(UStaticMeshComponent* FruitMesh, float Seconds)
{
    static float Timer = 0.f;
	
	//if mesh is over a certain height, it cant go higher
	if (FruitMesh->GetComponentLocation().Z > 1000.f)
		return;

    if (!bOnce)
    {
        Timer = Seconds;
        bOnce = true;
    }

    if (bFlyAway && Timer > 0.f)
    {
        Timer -= GetWorld()->GetDeltaSeconds();
        FruitMesh->AddLocalOffset(FVector(0.f, 0.f, 10.f));
    }

    if (bFlyAway && Timer <= 0.f)
    {
        bFlyAway = false;
        bOnce = false;
    }
}