

#pragma once
#include "Classes/Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Branch.generated.h"


UCLASS()
class LUNREAL_API ABranch : public AActor
{
  GENERATED_BODY ()
    
public:
  UPROPERTY ()
  USplineComponent* SplineComponent;

	ABranch();


	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	
	
};
