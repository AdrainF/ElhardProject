// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructible/DestructibleObjectBase.h"

// Sets default values
ADestructibleObjectBase::ADestructibleObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestructibleObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

