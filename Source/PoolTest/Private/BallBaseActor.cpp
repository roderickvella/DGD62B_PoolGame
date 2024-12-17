// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBaseActor.h"

// Sets default values
ABallBaseActor::ABallBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the mesh component and set as the root
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	//set physics
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetMassOverrideInKg(NAME_None, 0.22f);
	BallMesh->SetLinearDamping(0.01f);
	BallMesh->SetAngularDamping(2.0f); //a higher value will cause the ball to stop spinning faster
	//which should reduce the unexpected deviations in the ball's direction due to spinning

	//set scale
	BallMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

}

// Called when the game starts or when spawned
void ABallBaseActor::BeginPlay()
{
	Super::BeginPlay();
	//store the ball position
	BallPosition = GetActorLocation();
}

// Called every frame
void ABallBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* ABallBaseActor::GetBallMesh() const
{
	return BallMesh;
}

bool ABallBaseActor::IsBallMoving() const
{
	if (BallMesh) {
		return !BallMesh->GetPhysicsLinearVelocity().IsNearlyZero();
	}
	return false;
}

void ABallBaseActor::ResetBallPosition()
{
	SetActorLocation(BallPosition);
	BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

