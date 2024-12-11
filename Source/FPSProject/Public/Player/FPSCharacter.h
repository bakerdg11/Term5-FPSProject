// .h


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
#include "Pickups/WeaponPickup.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "FPSCharacter.generated.h"

class AEnemyAIController;

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

private: 
	// Stealth kill range
	UPROPERTY(EditAnywhere, Category = "Stealth Kill")
	float StealthKillRange = 200.0f;

	// Stealth kill dot product threshold (-1.0 = directly behind, 0 = perpendicular)
	UPROPERTY(EditAnywhere, Category = "Stealth Kill")
	float StealthKillDotThreshold = 0.0f;


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
	void StealthKill();

	UFUNCTION()
	void StartCrouch();

	UFUNCTION()
	void StopCrouch();

	UFUNCTION()
	void Damage(float damageAmt);
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


private:
	float Health = 100;
	const float MaxHealth = 100;



protected:
	void AttemptStealthKill();

	AEnemyAIController* GetValidEnemyForStealthKill() const;

	void DebugStealthKill(FVector EnemyLocation, FVector PlayerLocation, bool IsBehind, bool IsClose);



};
