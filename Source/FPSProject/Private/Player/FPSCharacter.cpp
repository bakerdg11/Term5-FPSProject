// .cpp


#include "Player/FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/FPSHUD.h"


// Sets default values
AFPSCharacter::AFPSCharacter() //Constructor: Gets called when game starts for the first time and editor opens for the first time
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent)
	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	if (!FPSMesh)
	{
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMesh->SetupAttachment(FPSCameraComponent);
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
	}

	GetMesh()->SetOwnerNoSee(true);


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay() // Only called when the game begins, not when editor opens
{
	Super::BeginPlay();
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f;
	}

	bHasWeapon = false;

}


// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Look around
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	// Fire Weapon
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	// Crouch
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPSCharacter::StopCrouch);
}

void AFPSCharacter::MoveForward(float value)
{
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::PickupWeapon()
{
	if (bHasWeapon) return;

	bHasWeapon = true;
	UE_LOG(LogTemp, Warning, TEXT("Weapon Picked Up"));

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		TSubclassOf<AWeaponPickup> WeaponClass = LoadClass<AWeaponPickup>(nullptr, TEXT("/Game/Blueprint/Pickup/BP_WeaponPickup.BP_WeaponPickup_C"));
		if (WeaponClass)
		{
			FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150.0f;  // Spawn slightly in front of the player
			FRotator SpawnRotation = GetActorRotation();

			AttachedWeapon = World->SpawnActor<AWeaponPickup>(WeaponClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (AttachedWeapon)
			{
				AttachedWeapon->AttachToComponent(FPSCameraComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

				AttachedWeapon->SetActorRelativeLocation(FVector(50.0f, 10.0f, -20.0f));
				AttachedWeapon->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
				UE_LOG(LogTemp, Warning, TEXT("Weapon Spawned at Location: %s"), *SpawnLocation.ToString());
			}
		}
	}
}


void AFPSCharacter::Fire()
{
	if (!bHasWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("You need to pick up a weapon first!"));
		return; // Exit the method if the player doesn't have a weapon
	}


	if (!ProjectileClass) return;
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	//MuzzleRotation.Pitch += 10.0f;

	// Unity Instantiate
	// 1. Get World we to spawn in
	// 2. Spawn Actor with parameters to setup
	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;

	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}

void AFPSCharacter::StartCrouch()
{
	Crouch();

	// Change speed
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f; // Example speed
	}

	// Adjust camera position for crouch
	if (FPSCameraComponent)
	{
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f)); // Adjust as needed
	}
}

void AFPSCharacter::StopCrouch()
{
	UnCrouch();

	// Change speed back
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f; // Example speed
	}

	// Camera position back to regular
	if (FPSCameraComponent)
	{
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	}
}



/*
void AFPSCharacter::Damage(float damageAmt)
{
}

float AFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}

*/