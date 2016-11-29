

#pragma once
#include "Classes/Components/SplineMeshComponent.h"
#include "Classes/Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Branch.generated.h"


UCLASS()
class LUNREAL_API ABranch : public AActor
{
  GENERATED_BODY ()
    UPROPERTY (VisibleAnywhere)
    TArray<FVector> points;
  FVector initialTangent;

public:
  UPROPERTY ()
  USplineComponent *SplineComponent;
  UPROPERTY ()
  UStaticMesh *StaticMesh;
  UPROPERTY()
  USplineMeshComponent *SplineMesh;

	ABranch();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

  void AddPoint (FVector v);
  void Draw ();
  void Init (FVector tangent);
};
