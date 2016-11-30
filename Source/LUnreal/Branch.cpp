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

  static ConstructorHelpers::FObjectFinder<UStaticMesh> BarFillObj (TEXT ("/Game/Cylinder_StaticMesh3"));
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
    SplineMesh->SetSplineUpDir (FVector (0, 1, 0));;
    SplineMesh->SetMobility (EComponentMobility::Movable);
    SplineMesh->SetStaticMesh (StaticMesh);
    SplineMesh->SetStartScale (FVector2D (1, 1));
    SplineMesh->SetEndScale (FVector2D (1, 1));
    FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i, pointLocationStart, pointTangentStart);
    if ( i == 0 ) {
      pointTangentStart = initialTangent;
    }
    FVector tangent = pointLocationEnd - pointLocationStart;
    FVector perpendicular = FVector::CrossProduct (tangent, FVector (1, 0, 0));
    //SplineMesh->SetSplineUpDir (perpendicular);
    SplineMesh->SetEndScale (FVector2D (initialScale*pow (width_multiplier, i + 1), initialScale*pow (width_multiplier, i + 1)));
    SplineMesh->SetStartScale (FVector2D (initialScale*pow (width_multiplier, i), initialScale*pow (width_multiplier, i)));
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i + 1, pointLocationEnd, pointTangentEnd);
    SplineMesh->SetStartAndEnd (pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, true);
  }
}
void ABranch::AddPoint (FVector v) {
  points.Add (v);
}
void ABranch::Init (FVector tangent, float scale, float w) {
  initialTangent = tangent;
  initialScale = scale;
  width_multiplier = w;
}