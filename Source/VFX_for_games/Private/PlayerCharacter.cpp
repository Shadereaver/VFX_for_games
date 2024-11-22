#include "PlayerCharacter.h"

#include "Health.h"
#include "NiagaraComponent.h"
#include "Portal.h"
#include "Projectile.h"
#include "Wall.h"
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

	_Health = CreateDefaultSubobject<UHealth>(TEXT("_Health"));

	_WallPos = CreateDefaultSubobject<USceneComponent>(TEXT("_WallPos"));
	_WallPos->SetupAttachment(RootComponent);

	_bAbility3OnCooldown = false;
	_bAbility2OnCooldown = false;
	_bAbility1OnCooldown = false;
}

UInputMappingContext* APlayerCharacter::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void APlayerCharacter::Input_AttackPressed_Implementation()
{
	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor(_AttackProjectile, &_Muzzle->GetComponentTransform(), SpawnParameters);
}

void APlayerCharacter::Input_AttackReleased_Implementation()
{
	IInputable::Input_AttackReleased_Implementation();
}

void APlayerCharacter::Input_Ability1_Implementation()
{
	if (_bAbility1OnCooldown) {return;}
	_bAbility1OnCooldown = true;
	GetWorldTimerManager().SetTimer(_Ability1Cooldown, this, &APlayerCharacter::Ability1OffCooldown, 20);
	
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	GetWorld()->SpawnActor(_Wall, &_WallPos->GetComponentTransform(), SpawnParams);
}

void APlayerCharacter::Input_Ability2_Implementation()
{
	if (_bAbility2OnCooldown) {return;}
	_bAbility2OnCooldown = true;
	GetWorldTimerManager().SetTimer(_Ability2Cooldown, this, &APlayerCharacter::Ability2OffCooldown, 30);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TObjectPtr<APortal> Portal = Cast<APortal>(GetWorld()->SpawnActor(_Portal, &GetActorTransform(), SpawnParams));

	FTimerDelegate Timerdel;
	Timerdel.BindUFunction(this, FName("EndIncorporealTime"), Portal);
	GetWorldTimerManager().SetTimer(_IncorporealTime, Timerdel, 5, false);
}

void APlayerCharacter::Input_Ability3_Implementation()
{
	if (_bAbility3OnCooldown || _Ability3Projectile == nullptr) {return;}

	_bAbility3OnCooldown = true;
	GetWorldTimerManager().SetTimer(_Ability3Cooldown, this, &APlayerCharacter::Ability3OffCooldown, 10);
	
	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TObjectPtr<AProjectile> projectile = Cast<AProjectile>(GetWorld()->SpawnActor(_Ability3Projectile, &_Muzzle->GetComponentTransform(), SpawnParameters));

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

void APlayerCharacter::Ability1OffCooldown()
{
	_bAbility1OnCooldown = false;
}

void APlayerCharacter::EndIncorporealTime(APortal* OtherPortal)
{
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	TObjectPtr<APortal> Portal = Cast<APortal>(GetWorld()->SpawnActor(_Portal, &GetActorTransform(), SpawnParams));

	Portal->_bCanTeleport = false;
	Portal->_Partner = OtherPortal;
	OtherPortal->_Partner = Portal;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void APlayerCharacter::Ability2OffCooldown()
{
	_bAbility2OnCooldown = false;
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
