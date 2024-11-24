#include "Projectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile::Handle_Hit);

	_Sprite = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Sprite"));
	_Sprite->SetupAttachment(RootComponent);
	
	_ProjMov = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	_ProjMov->UpdatedComponent = RootComponent;
	_ProjMov->InitialSpeed = 500;
	_ProjMov->MaxSpeed = 500;
	_ProjMov->bRotationFollowsVelocity = true;
	_ProjMov->bShouldBounce = false;
	_ProjMov->ProjectileGravityScale = 0;

	InitialLifeSpan = 3.f;
	_Damage = 0;
}

void AProjectile::MultiplyDamage_Implementation(float Multiplier)
{
	_Damage *= Multiplier;
}

void AProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, _Impact, GetActorLocation());
	UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());
	OnHit.Broadcast(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	Destroy();
}
