#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectile::AProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile::Handle_Hit);
	
	_ProjMov = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	_ProjMov->UpdatedComponent = RootComponent;
	_ProjMov->InitialSpeed = 500;
	_ProjMov->MaxSpeed = 500;
	_ProjMov->bRotationFollowsVelocity = true;
	_ProjMov->bShouldBounce = false;
	_ProjMov->ProjectileGravityScale = 0;

	InitialLifeSpan = 3.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	OnHit.Broadcast(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	Destroy();
}
