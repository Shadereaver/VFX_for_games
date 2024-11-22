#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UNiagaraComponent;
class UCapsuleComponent;

UCLASS()
class VFX_FOR_GAMES_API APortal : public AActor 
{
	GENERATED_BODY()

public:
	APortal();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APortal> _Partner;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> _Collider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> _Portal;

	UFUNCTION()
	void Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
