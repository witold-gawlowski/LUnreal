#include "LUnreal.h"
#include "Branch.h"

ABranch::ABranch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  SplineComponent = CreateDefaultSubobject<USplineComponent> (TEXT ("BranchSpline"));
  RootComponent = SplineComponent;

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
  UStaticMeshComponent *m = NewObject<UStaticMeshComponent> (this, TEXT ("asd"));
  m->SetStaticMesh (StaticMesh);

  SplineComponent->SetSplinePoints (points, ESplineCoordinateSpace::Local);
  int32 branch_length = SplineComponent->GetNumberOfSplinePoints ();
  for ( int32 i = 0; i < branch_length; i++ ) {
    SplineMesh = NewObject<USplineMeshComponent> (this, FName (*FString::FromInt (i)));
    SplineMesh->RegisterComponentWithWorld (GetWorld ());
    SplineMesh->AttachTo (SplineComponent);
    AddOwnedComponent (SplineMesh);
    SplineMesh->SetForwardAxis (ESplineMeshAxis::Z);
    SplineMesh->SetStaticMesh (StaticMesh);
    SplineMesh->SetStartScale (FVector2D (1, 1));
    SplineMesh->SetEndScale (FVector2D (1, 1));
    FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i, pointLocationStart, pointTangentStart);
    SplineComponent->GetLocalLocationAndTangentAtSplinePoint (i + 1, pointLocationEnd, pointTangentEnd);
    SplineMesh->SetStartAndEnd (pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, true);
  }
}