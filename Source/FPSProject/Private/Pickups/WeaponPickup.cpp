#include "Pickups/WeaponPickup.h"
#include "Player/FPSCharacter.h" // Replace with actual character header
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AWeaponPickup::AWeaponPickup()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->SetupAttachment(RootComponent);

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapBegin);
}

void AWeaponPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
    if (Player)
    {
        Player->PickupWeapon();
        //Destroy();
    }
}