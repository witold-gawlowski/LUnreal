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

  /*GLOBAL PARAMS*/
  float roll_angle;
  float pitch_angle;
  float width_multiplier;
  float length_multiplier;
  int lod;


  /*CONSTRUCTION*/
  FString text_representation;
  FVector turtle_pos;
  FVector turtle_dir;
  float turtle_length_scale;
  float turtle_width_scale;
  TArray<ABranch*> branches;
  TArray<ABranch*> branchStack;
  TArray<FVector> pos_stack;
  TArray<FVector> dir_stack;
  TArray<float> length_stack;
  TArray<float> width_stack;
  float tree_height;

  void Forward ();
  void NewBranch ();
  void CloseBranch ();
  void RollCW ();
  void RollCCW ();
  void PitchCW ();
  void PitchCCW ();

public:
 

	ATree();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	
  void Init (FString s, float roll_angle, float pitch_angle, float length_multipler, float width_multiplier, int lod);
  void Build ();
  void Draw ();
  void Clear ();
};
