// Fill out your copyright notice in the Description page of Project Settings.


#include "CueActor.h"

// Sets default values
ACueActor::ACueActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CueMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CueMesh"));
	RootComponent = CueMesh;
	CueMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	//initialize animation variables
	CueState = ECueState::Idle;
	CurrentPullDistance = 0.0f;
	MaxPullDistance = 100.0f;//maximum distance the cue can move backwards
	PullSpeed = 100.0f; //speed of the backward movement

	//initialize timer and force multiplier variables
	HoldStartTime = 0.0f;
	HoldEndTime = 0.0f;
	BaseForce = 200.0f; //base force value


}

// Called when the game starts or when spawned
void ACueActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACueActor::SetCueActive(bool bActive)
{
}

void ACueActor::RotateCue(float Value)
{
}

void ACueActor::PullCue(float Value)
{
}

void ACueActor::ReleaseCue()
{
}

void ACueActor::StartCuePull()
{
}

void ACueActor::Shoot()
{
}

float ACueActor::CalculateForceStrength()
{
	return 0.0f;
}

