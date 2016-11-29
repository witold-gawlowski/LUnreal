#include "LUnreal.h"
#include "Branch.h"

#define print(XXX, YYY)  UE_LOG (LogTemp, Warning, XXX, YYY);
#define print1(XXX) UE_LOG (LogTemp, Warning, XXX);

ABranch::ABranch()
{
	PrimaryActorTick.bCanEverTick = true;
  SplineComponent = CreateDefaultSubobject<USplineComponent> (TEXT ("BranchSpline"));
  RootComponent = SplineComponent;
  SplineComponent->SetMobility (EComponentMobility::Static);

  static ConstructorHelpers::FObjectFinder<UStaticMesh> BarFillObj (TEXT ("/Game/Cylinder_StaticMesh2"));
  StaticMesh = BarFillObj.Object;
}
void ABranch::BeginPlay()
{
	Super::BeginPlay();
  
}
void ABranch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABranch::Draw () {
  SplineComponent->SetSplinePoints (points, ESplineCoordinateSpace::Local);
  for ( FVector v : points ) {
    print (TEXT ("Branch point x: %f"), v.X);
    print (TEXT ("Branch point y: %f"), v.Y);
    print (TEXT ("Branch point z: %f"), v.Z);
  }
  int32 branch_length = SplineComponent->GetNumberOfSplinePoints ();
  for ( int32 i = 0; i < branch_length-1; i++ ) {
    SplineMesh = NewObject<USplineMeshComponent> (this, FName (*FString::FromInt (i)));
    SplineMesh->RegisterComponentWithWorld (GetWorld ());
    SplineMesh->AttachTo (SplineComponent);
    AddOwnedComponent (SplineMesh);
    SplineMesh->SetForwardAxis (ESplineMeshAxis::Z);
    SplineMesh->SetSplineUpDir (FVector (1, 0, 0));
    SplineMesh->SetMobility (EComponentMobility::Movable);
    SplineMesh->SetStaticMesh (StaticMesh);
    SplineMesh->SetStartScale (FVector2D (1, 1));
    SplineMesh->SetEndScale (FVector2D (1, 1));
    FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i, pointLocationStart, pointTangentStart);
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i + 1, pointLocationEnd, pointTangentEnd);
    SplineMesh->SetStartAndEnd (pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, true);
  }
}

void ABranch::AddPoint (FVector v) {
  points.Add (v);
}