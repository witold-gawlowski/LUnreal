// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tree.generated.h"


UCLASS()
class LUNREAL_API ATree : public AActor
{
  GENERATED_BODY ()
  
//init values
  TMap<TCHAR, FString> rules;
  TArray<TCHAR> variables;
  TCHAR start_variable;
  float roll_angle;

  FString text_representation;
 
  void Init ();
  void ReadInput ();
  void LogInputData ();
  void Clear ();
  void StepForward ();
  void StepBackward ();
  void LogTextRepresentation ();

public:
	ATree();

	virtual void BeginPlay() override;
	
  virtual void OnConstruction (const FTransform& t) override;

	virtual void Tick( float DeltaSeconds ) override;
	

};
