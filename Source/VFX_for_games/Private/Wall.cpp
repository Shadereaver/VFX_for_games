#include "Wall.h"

#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("_Collider"));
	_Collider->SetBoxExtent(FVector(200, 10, 125));
	RootComponent = _Collider;

	_Wall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Wall"));
	_Wall->SetupAttachment(RootComponent);
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}
