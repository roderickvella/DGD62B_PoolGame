// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CueActor.generated.h"

class AWhiteBallActor;


UCLASS()
class POOLTEST_API ACueActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACueActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	UStaticMeshComponent* CueMesh;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AWhiteBallActor* WhiteBallReference;


	UPROPERTY(EditAnywhere, Category = "Gameplay")
	FVector CueOffset = FVector(30.0f, 0.f, 0.f);

	//cue active
	void SetCueActive(bool bActive);

private:
	//rotates the cuse based on player input
	void RotateCue(float Value);

	//pulls the cue back
	void PullCue(float Value);

	//release the cue
	void ReleaseCue();

	//starts the pulling of the cue (when space bar is pressed)
	void StartCuePull();

	//shoots the white ball
	void Shoot();

	//calculate force strength
	float CalculateForceStrength();

	//animation control variables
	float CurrentPullDistance;
	float MaxPullDistance;
	float PullSpeed;

	//enum for cue state
	enum class ECueState {
		Idle,
		Pulling,
		Releasing,
		Shoot,
		Disabled
	};

	ECueState CueState;

	//timing and force variables
	float HoldStartTime; //time when the space bar is pressed
	float HoldEndTime; //time when the space bar is released
	float BaseForce; //Base Force applied to the ball

};
