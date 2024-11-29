// Fill out your copyright notice in the Description page of Project Settings.


#include "TableActor.h"

// Sets default values
ATableActor::ATableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	//set the default scale for the root component
	DefaultSceneRoot->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));

}

// Called when the game starts or when spawned
void ATableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

