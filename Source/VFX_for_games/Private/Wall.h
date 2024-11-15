#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class UBoxComponent;

UCLASS()
class VFX_FOR_GAMES_API AWall : public AActor
{
	GENERATED_BODY()

public:
	AWall();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
};
