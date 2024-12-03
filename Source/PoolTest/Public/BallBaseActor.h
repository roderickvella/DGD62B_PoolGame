// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBaseActor.generated.h"

UCLASS()
class POOLTEST_API ABallBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BallMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//get the BallMesh Component
	UStaticMeshComponent* GetBallMesh() const;

	//check if the ball is moving
	bool IsBallMoving() const;

	//reset ball position
	void ResetBallPosition();

private:
	FVector BallPosition;

};
