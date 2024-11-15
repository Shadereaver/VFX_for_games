#include "Wall.h"

#include "Components/BoxComponent.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("_Collider"));
	_Collider->SetBoxExtent(FVector(200, 10, 125));
	RootComponent = _Collider;
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}
