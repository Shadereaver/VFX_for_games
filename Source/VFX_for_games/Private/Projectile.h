#pragma once

#include "CoreMinimal.h"
#include "DamageMultiply.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UNiagaraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FProjectileHitSignature, UPrimitiveComponent*, HitComponent, AActor*,
                                              OtherActor, UPrimitiveComponent*, OtherComp,
                                              FVector, NormalImpulse, const FHitResult&, Hit);

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class VFX_FOR_GAMES_API AProjectile : public AActor, public IDamageMultiply
{
	GENERATED_BODY()

public:
	AProjectile();
	
	FProjectileHitSignature OnHit;

	virtual void MultiplyDamage_Implementation(float Multiplier) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> _ProjMov;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> _Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;

	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
};
