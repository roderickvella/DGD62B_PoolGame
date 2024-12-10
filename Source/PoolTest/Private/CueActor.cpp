// Fill out your copyright notice in the Description page of Project Settings.


#include "CueActor.h"
#include <Kismet/GameplayStatics.h>
#include "WhiteBallActor.h"

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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		PlayerController->InputComponent->BindAxis("RotateCue", this, &ACueActor::RotateCue);
		PlayerController->InputComponent->BindAxis("PullCue", this, &ACueActor::PullCue);
		PlayerController->InputComponent->BindAction("Shoot", IE_Pressed, this, &ACueActor::StartCuePull);
		PlayerController->InputComponent->BindAction("Shoot", IE_Released, this, &ACueActor::ReleaseCue);
	}

	//if whiteballreference is null, we load by tag
	if (!WhiteBallReference) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("WhiteBall"), FoundActors);
		if (FoundActors.Num() > 0) {
			WhiteBallReference = Cast<AWhiteBallActor>(FoundActors[0]);
		}
	}

	
}

// Called every frame
void ACueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CueState == ECueState::Releasing) {
		//calculate the forward movement based on the current rotation
		FVector PushDirection = GetActorForwardVector();
		float PushSpeed = 300.0f; //speed of the forward movement (towards the white ball)
		float HoldDuration = HoldEndTime - HoldStartTime;
		if (HoldDuration < 0.2f) {
			PushSpeed = 60.0f;
		}
		else if (HoldDuration >= 0.2f && HoldDuration < 0.8f) {
			PushSpeed = 500.0f;
		}
		else if (HoldDuration >= 0.8f) {
			PushSpeed = 700.0f;
		}

		//move the cue forward along the push direction
		CurrentPullDistance -= PushSpeed * DeltaTime;
		float ThresholdDistance = -(CueOffset.Size() - 10.0f); //the -10 is make the cue go a little bit outside the white ball
		//not perfect at the center of the white ball)

		if (CurrentPullDistance <= ThresholdDistance) {
			CurrentPullDistance = 0.0f;
			CueState = ECueState::Shoot;
			Shoot(); //shoot the white ball when the cue reaches the white ball
		}
		else {
			//update the cue's location towards the white ball (move animation)
			SetActorLocation(WhiteBallReference->GetActorLocation() + CueOffset + PushDirection * CurrentPullDistance);
		}


	}

}

void ACueActor::SetCueActive(bool bActive)
{
}

void ACueActor::RotateCue(float Value)
{
	if (WhiteBallReference && CueState == ECueState::Idle) {
		FRotator RotationDelta(0.f, Value, 0.f);
		CueOffset = RotationDelta.RotateVector(CueOffset);

		//set the new location of the cue based on the ball's location and the offset
		SetActorLocation(WhiteBallReference->GetActorLocation() + CueOffset);

		FRotator TargetRotation = (WhiteBallReference->GetActorLocation() - GetActorLocation()).Rotation();
		TargetRotation.Pitch -= 180.f; //adjust the pitch to make the cue point towards the white ball
		SetActorRotation(TargetRotation);

	}
}

void ACueActor::PullCue(float Value)
{
	if (Value > 0.0f && (CueState == ECueState::Idle || CueState == ECueState::Pulling)) {
		//move cue backwards
		CueState = ECueState::Pulling; //set the cue state to pulling

		//calculate the backward movement based on the current rotation
		FVector PullDirection = GetActorForwardVector();

		CurrentPullDistance += PullSpeed * GetWorld()->GetDeltaSeconds();
		CurrentPullDistance = FMath::Clamp(CurrentPullDistance, 0.0f, MaxPullDistance);

		//set the new location based on the current pull distance and rotation
		SetActorLocation(WhiteBallReference->GetActorLocation() + CueOffset + PullDirection * CurrentPullDistance);

	}
}

void ACueActor::ReleaseCue()
{
	CueState = ECueState::Releasing;
	HoldEndTime = GetWorld()->GetTimeSeconds(); //end timing when the player releases the cue
}

void ACueActor::StartCuePull()
{
	if (CueState == ECueState::Idle) {
		HoldStartTime = GetWorld()->GetTimeSeconds(); //start timing when the player begins to pull the cue
		CueState = ECueState::Pulling;
	}
}

void ACueActor::Shoot()
{
}

float ACueActor::CalculateForceStrength()
{
	float HoldDuration = HoldEndTime - HoldStartTime; //calculate the duration the space bar was held
	return BaseForce * FMath::Clamp(HoldDuration, 0.1f, 5.0f); //clamp the hold duration between 0.1 and 5.0 seconds
}

