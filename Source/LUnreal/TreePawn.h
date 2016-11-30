// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tree.h"
#include "GameFramework/Pawn.h"
#include "TreePawn.generated.h"

UCLASS()
class LUNREAL_API ATreePawn : public APawn
{
	GENERATED_BODY()

   /*GENERATION*/
  TMap<TCHAR, FString> rules;
  TArray<TCHAR> variables;
  TCHAR start_variable;
  TArray<FString> text_representations;
  

  /*PARAMETERS*/
  float roll_angle;
  float pitch_angle;
  float width_multiplier;
  float length_multiplier;
  enum ParameterType{roll, pitch, width, length};
  ParameterType currentParameter;
  int32 current_LOD;

  UPROPERTY()
  ATree *tree;
  
  UPROPERTY (EditAnywhere)
  USpringArmComponent* OurCameraSpringArm;
  UCameraComponent* OurCamera;

  FVector MovementInput;
  FVector2D CameraInput;

  void MoveForward (float AxisValue);
  void MoveRight (float AxisValue);
  void MoveUp (float AxisValue);
  void PitchCamera (float AxisValue);
  void YawCamera (float AxisValue);

  void Init ();
  void Build ();
  void ReadInput (FString path);
  void LogInputData ();
  void Clear ();
  void LogTextRepresentation ();
  void GenerateNewLevel ();

  void DrawTree ();

  /*INPUT HANDLERS*/
  void StepForward ();
  void StepBackward ();
  void IncreaseParam (float AxisValue);
  void EnableRollParam ();
  void EnablePitchParam ();
  void EnableWidthMultiplier ();
  void EnableLengthMultiplier ();
  void ReadInputGeneric (FString f);
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
