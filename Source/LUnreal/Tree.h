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
  UPROPERTY ()
    USceneComponent *SceneComponent;

  FString text_representation;
  FVector turtle_pos;
  FVector turtle_dir;
  TArray<ABranch*> branches;
  TArray<ABranch*> branchStack;

  void Forward ();
  void NewBranch ();
  void CloseBranch ();
  void RollCW ();
  void RollCCW ();

public:
 

	ATree();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	
  void Init (FString s);
  void Build ();
  void Draw ();
  void Clear ();
};
