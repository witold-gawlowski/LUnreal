// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TreePawn.generated.h"

UCLASS()
class LUNREAL_API ATreePawn : public APawn
{
	GENERATED_BODY()
  TMap<TCHAR, FString> rules;
  TArray<TCHAR> variables;
  TCHAR start_variable;
  float roll_angle;
  TArray<FString> text_representations;
  int32 current_LOD;

  void Init ();
  void ReadInput ();
  void LogInputData ();
  void Clear ();
  void LogTextRepresentation ();
  void GenerateNewLevel ();

  /*INPUT HANDLERS*/
  void StepForward ();
  void StepBackward ();
  void IncreaseParam ();
  void DecreaseParam ();
  void EnableRollParam ();
  void EnablePitchParam ();
  void EnableSizeMultiplier ();
  void ReadInput1 ();
  void ReadInput2 ();
  void ReadInput3 ();
  void ReadInput4 ();
  void ReadInput5 ();
  void ReadInput6 ();
  void ReadInput7 ();
  void ReadInput8 ();
public:
	// Sets default values for this pawn's properties
	ATreePawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;	
};
