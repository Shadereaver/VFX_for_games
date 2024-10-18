#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{
	_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_Arm->SetupAttachment(RootComponent);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camer"));
	_Camera->SetupAttachment(_Arm, FName("SpringEndpoint"));
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
	IInputable::Input_Ability3_Implementation();
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
	AddActorWorldRotation(FRotator(0.f, Value.X, 0.f));
	_Arm->AddLocalRotation(FRotator(Value.Y, 0.f, 0.f));
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

