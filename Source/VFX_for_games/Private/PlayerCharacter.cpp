#include "PlayerCharacter.h"

#include "NiagaraComponent.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{
	_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_Arm->SetupAttachment(RootComponent);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(_Arm, FName("SpringEndpoint"));

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(RootComponent);

	_Ring = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Ring"));
	_Ring->SetupAttachment(RootComponent);
	
	_Lightning = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Lightning"));
	_Lightning->SetupAttachment(RootComponent);
	
	_Tether = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Tether"));
	_Tether->SetupAttachment(RootComponent);

	_bAbility3OnCooldown = false;
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
	if (_bAbility3OnCooldown || _Ability3Projectile == nullptr) {return;}

	_bAbility3OnCooldown = true;
	GetWorldTimerManager().SetTimer(_Ability3Cooldown, this, &APlayerCharacter::Ability3OffCooldown, 10);
	
	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TObjectPtr<AProjectile> projectile = Cast<AProjectile>(World->SpawnActor(_Ability3Projectile, &_Muzzle->GetComponentTransform(), SpawnParameters));

	projectile->OnHit.AddUniqueDynamic(this, &APlayerCharacter::Handle_Ability3ProjectileOnHit);
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

	_Ring->OnSystemFinished.AddUniqueDynamic(this, &APlayerCharacter::Handle_RingEffectDone);
}

void APlayerCharacter::SwapDone()
{
	_Lightning->ToggleActive();
	_Tether->ToggleActive();
	GetWorldTimerManager().ClearTimer(_PassTetherDataTimer);
}

void APlayerCharacter::Handle_Ability3ProjectileOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FTimerDelegate TetherTimerDel;
	TetherTimerDel.BindUFunction(this, FName("PassTetherData"), OtherActor);
	
	GetWorldTimerManager().SetTimer(_PassTetherDataTimer, TetherTimerDel, 0.01f, true);
	GetWorldTimerManager().SetTimer(_PassRingDataTimer, this, &APlayerCharacter::PassRingData, 0.01f, true);

	_Tether->ToggleActive();
	_Lightning->ToggleActive();
	_Ring->ToggleActive();

	StartSwap(OtherActor);
}

void APlayerCharacter::PassTetherData(AActor* OtherActor)
{
	_Tether->SetVariablePosition(FName("TetherEndPos"), OtherActor->GetActorLocation());
}

void APlayerCharacter::PassRingData()
{
	_Ring->SetVariablePosition(FName("PlayerPos"), GetActorLocation());
	_Ring->SetVariableVec3(FName("RingFacing"), GetCapsuleComponent()->GetForwardVector());
}

void APlayerCharacter::Handle_RingEffectDone(UNiagaraComponent* PSystem)
{
	GetWorldTimerManager().ClearTimer(_PassRingDataTimer);	
}

void APlayerCharacter::Ability3OffCooldown()
{
	_bAbility3OnCooldown = false;
}
