// Fill out your copyright notice in the Description page of Project Settings.

#include "LUnreal.h"
#include "Branch.h"


// Sets default values
ABranch::ABranch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  //SplineComponent = CreateDefaultSubobject<USplineComponent> (TEXT ("BranchSpline"), );
}

// Called when the game starts or when spawned
void ABranch::BeginPlay()
{
	Super::BeginPlay();
  //SplineComponent->AddSplineLocalPoint (FVector (0, 0, 0));
}

// Called every frame
void ABranch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

