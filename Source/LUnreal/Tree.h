// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tree.generated.h"


UCLASS()
class LUNREAL_API ATree : public AActor
{
  GENERATED_BODY ()
  
  struct Rule {
    TCHAR left;
    FString right;
    Rule (TCHAR l, FString r) :left (l), right (r) {}
    FString ToString ();
  };
 
  FString text_representation;
  //todo: convert it to a map
  TArray<Rule> rules;
  TArray<TCHAR> variables;
  TCHAR start_variable;
  float roll_angle;
 
  void Init ();
  void ReadInput ();
  void LogInputData ();
  void Clear ();
  void StepGeneration ();

public:
	ATree();

	virtual void BeginPlay() override;
	
  virtual void OnConstruction (const FTransform& t) override;

	virtual void Tick( float DeltaSeconds ) override;
	

};
