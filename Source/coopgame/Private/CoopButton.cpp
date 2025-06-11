// Fill out your copyright notice in the Description page of Project Settings.


#include "CoopButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "coopgameCharacter.h"

ACoopButton::ACoopButton()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
    TriggerZone->SetupAttachment(Mesh);
    TriggerZone->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
    TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ACoopButton::OnOverlapBegin);
    TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ACoopButton::OnOverlapEnd);

    bReplicates = true;
}

void ACoopButton::BeginPlay()
{
    Super::BeginPlay();
}

void ACoopButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AcoopgameCharacter* Player = Cast<AcoopgameCharacter>(OtherActor))
    {
        Player->CurrentButton = this;
    }
}

void ACoopButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (AcoopgameCharacter* Player = Cast<AcoopgameCharacter>(OtherActor))
    {
        if (Player->CurrentButton == this)
        {
            Player->CurrentButton = nullptr;
        }
    }
}

void ACoopButton::PressButton(AcoopgameCharacter* InteractingPlayer)
{
    UE_LOG(LogTemp, Warning, TEXT("Button pressed by %s"), *InteractingPlayer->GetName());
}
