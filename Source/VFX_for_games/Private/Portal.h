#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPortalDeathSignature);

UCLASS()
class VFX_FOR_GAMES_API APortal : public AActor 
{
	GENERATED_BODY()

public:
	APortal();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APortal> _Partner;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bCanTeleport;

	FPortalDeathSignature OnDeath;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> _Collider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> _Portal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)	
	int _Uses;

	UFUNCTION()
	void Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void Handle_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void DecrementUses();
	
	virtual void BeginPlay() override;
};
