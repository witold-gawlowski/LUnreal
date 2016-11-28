// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Branch.h"
#include "Classes/Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"


UCLASS()
class LUNREAL_API ATree : public AActor
{
  GENERATED_BODY ()
  
    UPROPERTY()
  ABranch *branch;
public:
	ATree();

	virtual void BeginPlay() override;
	
  virtual void OnConstruction (const FTransform& t) override;

	virtual void Tick( float DeltaSeconds ) override;
	

};
