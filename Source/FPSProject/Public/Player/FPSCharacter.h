// .h


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
#include "Pickups/WeaponPickup.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// --------------------Player Controls--------------------
	// Move Forward
	UFUNCTION() //Allows you to use it in Blueprints
	void MoveForward(float value);
	// Move Right
	UFUNCTION()
	void MoveRight(float value);
	// Jump
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void EndJump();
	
	// Weapon
	bool bHasWeapon;

	UFUNCTION()
	void PickupWeapon();

    AWeaponPickup* AttachedWeapon;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void StartCrouch();

	UFUNCTION()
	void StopCrouch();



	/*
	UFUNCTION()
	void Damage(float damageAmt);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	*/


};
