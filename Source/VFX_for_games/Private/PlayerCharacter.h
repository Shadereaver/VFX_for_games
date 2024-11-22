#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class APortal;
class AWall;
class UHealth;
class UNiagaraComponent;
class AProjectile;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Abstract)
class VFX_FOR_GAMES_API APlayerCharacter : public ACharacter, public IInputable
{

	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual void Input_AttackPressed_Implementation() override;
	virtual void Input_AttackReleased_Implementation() override;
	virtual void Input_Ability1_Implementation() override;
	virtual void Input_Ability2_Implementation() override;
	virtual void Input_Ability3_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _Arm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Muzzle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealth> _Health;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Attack")
	TSubclassOf<AProjectile> _AttackProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability 1")
	TSubclassOf<AWall> _Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability 1")
	TObjectPtr<USceneComponent> _WallPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 1")
	bool _bAbility1OnCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 1")
	FTimerHandle _Ability1Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability 2")
	TSubclassOf<APortal> _Portal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 2")
	FTimerHandle _IncorporealTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 2")
	bool _bAbility2OnCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 2")
	FTimerHandle _Ability2Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability 3")
	TSubclassOf<AProjectile> _Ability3Projectile;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	TObjectPtr<UNiagaraComponent> _Ring;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	TObjectPtr<UNiagaraComponent> _Lightning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	TObjectPtr<UNiagaraComponent> _Tether;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	FTimerHandle _PassTetherDataTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	FTimerHandle _PassRingDataTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	FTimerHandle _RingEffectDone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	FTimerHandle _Ability3Cooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability 3")
	bool _bAbility3OnCooldown;

	UFUNCTION(Category="Ability 1")
	void Ability1OffCooldown();
	
	UFUNCTION(Category="Ability 2")
	void EndIncorporealTime(APortal* Portal1);
	UFUNCTION(Category="Ability 2")
	void Ability2OffCooldown();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Ability 3")
	void StartSwap(AActor* OtherActor);
	UFUNCTION(BlueprintCallable, Category="Ability 3")
	void SwapDone();

	UFUNCTION(Category="Ability 3")
	void Handle_Ability3ProjectileOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(Category="Ability 3")
	void PassTetherData(AActor* OtherActor);
	UFUNCTION(Category="Ability 3")
	void PassRingData();
	UFUNCTION(Category="Ability 3")
	void Handle_RingEffectDone(UNiagaraComponent* PSystem);
	UFUNCTION(Category="Ability 3")
	void Ability3OffCooldown();
};
