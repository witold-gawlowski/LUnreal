// Fill out your copyright notice in the Description page of Project Settings.

#include "LUnreal.h"
#include "Branch.h"


// Sets default values
ABranch::ABranch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  SplineComponent = CreateDefaultSubobject<USplineComponent> (TEXT ("BranchSpline"));

  static ConstructorHelpers::FObjectFinder<UStaticMesh> BarFillObj (TEXT ("/Game/Cylinder_StaticMesh2"));
  StaticMesh = BarFillObj.Object;

  
  TArray<FVector> points = {FVector(0), FVector(100), FVector(200), FVector(500, 300, 700)};
  SplineComponent->SetSplinePoints (points, ESplineCoordinateSpace::Local);
  int32 branch_length = SplineComponent->GetNumberOfSplinePoints ();
  for ( int32 i = 0; i < branch_length; i++ ) {
    SplineMesh = CreateDefaultSubobject<USplineMeshComponent> (FName(*FString::FromInt(i)));
    SplineMesh->SetForwardAxis (ESplineMeshAxis::Z);
    SplineMesh->SetStaticMesh (StaticMesh);
    SplineMesh->SetStartScale (FVector2D (1, 1));
    SplineMesh->SetEndScale (FVector2D (1, 1));
    FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i, pointLocationStart, pointTangentStart);
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i+1, pointLocationEnd, pointTangentEnd);

    SplineMesh->SetStartAndEnd (pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, true);
  }
}

// Called when the game starts or when spawned
void ABranch::BeginPlay()
{
	Super::BeginPlay();

  
 
  
  
}

// Called every frame
void ABranch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

