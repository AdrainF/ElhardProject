// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/EP_WeaponBase.h"

#include "GameFramework/Character.h"

// Sets default values
AEP_WeaponBase::AEP_WeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	Start_Collision= CreateDefaultSubobject<USceneComponent>(TEXT("StartCollision"));
	Start_Collision->SetupAttachment(WeaponMesh);
	End_Collision= CreateDefaultSubobject<USceneComponent>(TEXT("EndCollision"));
	End_Collision->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AEP_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEP_WeaponBase::WeaponTrace(ACharacter* OwnerCharacter)
{
	TArray<struct FHitResult> OutHitResults;
	const FVector Start=Start_Collision->GetComponentLocation();
	const FVector End=End_Collision->GetComponentLocation();;
	// Set up collision to detect pawns
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	const float HalfHeight = (End - Start).Size() / 2.0f;
	FCollisionShape CollisionShape;
	CollisionShape.SetCapsule(10.0f, HalfHeight);
	
	// Ignore the player to prevent self-collision
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	
	
	const bool bBlockHit=OwnerCharacter->GetWorld()->SweepMultiByObjectType(OutHitResults,Start,End
		,FQuat::Identity,ObjectQueryParams
		,FCollisionShape::MakeSphere(5.f),Params);

	// Debug visualization of the capsule trace
	const FVector Center = (End + Start) / 2;
	const FColor CapsuleColor = bBlockHit ? FColor::Green : FColor::Red;

	DrawDebugCapsule(
		OwnerCharacter->GetWorld(),
		Center,
		HalfHeight,
		10.0f,
		FRotationMatrix::MakeFromZ(End - Start).ToQuat(),
		CapsuleColor,
		false,   // Not persistent
		1.0f,    // Duration
		0,       // Depth priority
		1.0f     // Thickness
	);
}

// Called every frame
void AEP_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}