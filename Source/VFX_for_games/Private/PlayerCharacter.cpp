#include "PlayerCharacter.h"

#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{
	_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_Arm->SetupAttachment(RootComponent);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(_Arm, FName("SpringEndpoint"));

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(RootComponent);
}

UInputMappingContext* APlayerCharacter::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void APlayerCharacter::Input_AttackPressed_Implementation()
{
	IInputable::Input_AttackPressed_Implementation();
}

void APlayerCharacter::Input_AttackReleased_Implementation()
{
	IInputable::Input_AttackReleased_Implementation();
}

void APlayerCharacter::Input_Ability1_Implementation()
{
	IInputable::Input_Ability1_Implementation();
}

void APlayerCharacter::Input_Ability2_Implementation()
{
	IInputable::Input_Ability2_Implementation();
}

void APlayerCharacter::Input_Ability3_Implementation()
{
	UWorld* const World = GetWorld();
	if (World == nullptr || _Ability3Projectile == nullptr) {return;}

	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TObjectPtr<AProjectile> projectile = Cast<AProjectile>(World->SpawnActor(_Ability3Projectile, &_Muzzle->GetComponentTransform(), SpawnParameters));

	projectile->OnHit.AddUniqueDynamic(this, &APlayerCharacter::Handle_OnHit);
}

void APlayerCharacter::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void APlayerCharacter::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void APlayerCharacter::Input_Look_Implementation(FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(-Value.Y);
}

void APlayerCharacter::Input_Move_Implementation(FVector2D Value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), Value.Y);
	AddMovementInput(_Camera->GetRightVector(), Value.X);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

