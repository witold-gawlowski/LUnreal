#include "LUnreal.h"
#include "TreePawn.h"

#define print(XXX, YYY)  UE_LOG (LogTemp, Warning, XXX, YYY);
#define print1(XXX) UE_LOG (LogTemp, Warning, XXX);

/*GENERATING TEXT REPRESENTATION*/
void ATreePawn::ReadInput () {
  TArray<FString> input_lines;
  FString filedir (FPaths::GameDir () + "/Input/tree.txt");
  FFileHelper::LoadANSITextFileToStrings (*filedir, NULL, input_lines);


  TArray<FString> temp;
  input_lines[1].ParseIntoArrayWS (temp);
  for ( FString s : temp ) {
    variables.Add (s[0]); // not sure if it runs poperly
  }

  start_variable = input_lines[3][0];

  roll_angle = FCString::Atof (*input_lines[5]);
  
  for ( int i = 7; i < input_lines.Num (); i++ ) {
    input_lines[i].ParseIntoArrayWS (temp);
    //print (TEXT ("Rule Line Dump: "), *input_lines[i]);
    if ( temp.Num () == 0 ) {
      break;
    }
    rules.Add (temp[0][0], temp[2]);
  }
}
void ATreePawn::Clear () {
  rules.Empty ();
  text_representations.Empty ();
  variables.Empty ();
  start_variable = 0;
  roll_angle = 0;
  current_LOD = 0;
}
void ATreePawn::GenerateNewLevel () {
  FString result;
  for ( TCHAR c : text_representations[current_LOD] ) {
    FString *successor = rules.Find (c);
    if ( successor ) {
      result.Append (*successor);
    } else {
      result.Append (FString::Chr (c));
    }
  }
  text_representations.Add(result);
}
void ATreePawn::StepForward () {
  if(current_LOD >= text_representations.Num() - 1){
    GenerateNewLevel ();
  }
  current_LOD++;
  tree->Init (text_representations[current_LOD]);
}
void ATreePawn::StepBackward () {
  if ( current_LOD >= 1 ) {
    current_LOD--;
  }
  tree->Init (text_representations[current_LOD]);
}
void ATreePawn::LogInputData () {
  for ( TCHAR c : variables ) {
    print (TEXT ("Variables: %c"), c)
  }
  print1 (TEXT ("Rules:"))
    for ( auto &elem : rules ) {
      FString temp = FString::Printf (TEXT ("%c -> %s"), elem.Key, *elem.Value);
      print (TEXT ("%s"), *temp);
    }
  print (TEXT ("Roll angle: %f"), roll_angle);
}
void ATreePawn::LogTextRepresentation () {
  print (TEXT ("Text represenation: %s"), *text_representations[current_LOD]);
}
void ATreePawn::Init () {
  text_representations.Add (FString::Chr (start_variable));
  current_LOD = 0;
}

/*TREE DRAWING*/
void ATreePawn::DrawTree () {
  //tree.Construct (text_representations[current_LOD]);
}

/*INPUT HANDLERS*/
void ATreePawn::IncreaseParam () {}
void ATreePawn::DecreaseParam () {
  LogTextRepresentation ();
  tree->Clear ();
  tree->Build ();
}
void ATreePawn::EnableRollParam () {}
void ATreePawn::EnablePitchParam () {}
void ATreePawn::EnableSizeMultiplier () {}
void ATreePawn::ReadInput1 () {}
void ATreePawn::ReadInput2 () {}
void ATreePawn::ReadInput3 () {}
void ATreePawn::ReadInput4 () {}
void ATreePawn::ReadInput5 () {}
void ATreePawn::ReadInput6 () {}
void ATreePawn::ReadInput7 () {}
void ATreePawn::ReadInput8 () {}
void ATreePawn::MoveForward (float AxisValue) {
  MovementInput.X = FMath::Clamp<float> (AxisValue, -1.0f, 1.0f);
}
void ATreePawn::MoveRight (float AxisValue) {
  MovementInput.Y = FMath::Clamp<float> (AxisValue, -1.0f, 1.0f);
}
void ATreePawn::MoveUp (float AxisValue) {
  MovementInput.Z = FMath::Clamp<float> (AxisValue, -1.0f, 1.0f);
}
void ATreePawn::PitchCamera (float AxisValue) {
  CameraInput.Y = AxisValue;
}
void ATreePawn::YawCamera (float AxisValue) {
  CameraInput.X = AxisValue;
}

/*ACTOR API*/
ATreePawn::ATreePawn () {
  PrimaryActorTick.bCanEverTick = true;
  //Create our components
  RootComponent = CreateDefaultSubobject<USceneComponent> (TEXT ("RootComponent"));
  OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent> (TEXT ("CameraSpringArm"));
  OurCameraSpringArm->SetupAttachment (RootComponent);
  OurCameraSpringArm->SetRelativeLocationAndRotation (FVector (0.0f, 0.0f, 50.0f), FRotator (-60.0f, 0.0f, 0.0f));
  OurCameraSpringArm->TargetArmLength = 400.f;
  OurCameraSpringArm->bEnableCameraLag = true;
  OurCameraSpringArm->CameraLagSpeed = 3.0f;

  OurCamera = CreateDefaultSubobject<UCameraComponent> (TEXT ("GameCamera"));
  OurCamera->SetupAttachment (OurCameraSpringArm, USpringArmComponent::SocketName);
  
  AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void ATreePawn::BeginPlay () {
  Super::BeginPlay ();
  Clear ();
  ReadInput ();
  //LogInputData ();
  Init ();
  LogTextRepresentation ();
  tree = GetWorld ()->SpawnActor<ATree>();
  tree->Init (text_representations[current_LOD]);
}
void ATreePawn::Tick (float DeltaTime) {
  Super::Tick (DeltaTime);
  {
    FRotator NewRotation = GetActorRotation ();
    NewRotation.Yaw += CameraInput.X;
    SetActorRotation (NewRotation);
  }

  {
    FRotator NewRotation = OurCameraSpringArm->GetComponentRotation ();
    NewRotation.Pitch = FMath::Clamp (NewRotation.Pitch + CameraInput.Y, -80.0f, 35.0f);
    OurCameraSpringArm->SetWorldRotation (NewRotation);
  }

  {
    if ( !MovementInput.IsZero () ) {
      MovementInput = MovementInput.SafeNormal () * 400.0f;
      FVector NewLocation = GetActorLocation ();
      NewLocation += GetActorForwardVector () * MovementInput.X * DeltaTime;
      NewLocation += GetActorRightVector () * MovementInput.Y * DeltaTime;
      NewLocation += GetActorUpVector () * MovementInput.Z * DeltaTime;
      SetActorLocation (NewLocation);
    }
  }
}
void ATreePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
  InputComponent->BindAction ("StepForward", IE_Pressed, this, &ATreePawn::StepForward);
  InputComponent->BindAction ("StepBackward", IE_Pressed, this, &ATreePawn::StepBackward);
  InputComponent->BindAction ("Increase", IE_Pressed, this, &ATreePawn::IncreaseParam);
  InputComponent->BindAction ("Decrease", IE_Pressed, this, &ATreePawn::DecreaseParam);
  InputComponent->BindAction ("RollAngParam", IE_Pressed, this, &ATreePawn::EnableRollParam);
  InputComponent->BindAction ("PitchAngParam", IE_Pressed, this, &ATreePawn::EnablePitchParam);
  InputComponent->BindAction ("SizeMultiplier", IE_Pressed, this, &ATreePawn::EnableSizeMultiplier);
  InputComponent->BindAction ("Input1", IE_Pressed, this, &ATreePawn::ReadInput1);
  InputComponent->BindAction ("Input2", IE_Pressed, this, &ATreePawn::ReadInput2);
  InputComponent->BindAction ("Input3", IE_Pressed, this, &ATreePawn::ReadInput3);
  InputComponent->BindAction ("Input4", IE_Pressed, this, &ATreePawn::ReadInput4);
  InputComponent->BindAction ("Input5", IE_Pressed, this, &ATreePawn::ReadInput5);
  InputComponent->BindAction ("Input6", IE_Pressed, this, &ATreePawn::ReadInput6);
  InputComponent->BindAction ("Input7", IE_Pressed, this, &ATreePawn::ReadInput7);
  InputComponent->BindAction ("Input8", IE_Pressed, this, &ATreePawn::ReadInput8);

  InputComponent->BindAxis ("MoveForward", this, &ATreePawn::MoveForward);
  InputComponent->BindAxis ("MoveRight", this, &ATreePawn::MoveRight);
  InputComponent->BindAxis ("MoveUp", this, &ATreePawn::MoveUp);
  InputComponent->BindAxis ("CameraPitch", this, &ATreePawn::PitchCamera);
  InputComponent->BindAxis ("CameraYaw", this, &ATreePawn::YawCamera);
  
}

