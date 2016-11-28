#include "LUnreal.h"
#include "Tree.h"

#define print(XXX, YYY)  UE_LOG (LogTemp, Warning, XXX, YYY);
#define print1(XXX) UE_LOG (LogTemp, Warning, XXX);

void ATree::ReadInput () {
  TArray<FString> input_lines;
  FString filedir (FPaths::GameDir () + "/Input/test.txt");
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
    rules.Add (temp[0][0], temp[2]);
  }
}
// not tested
void ATree::Clear () {
  rules.Empty ();
  variables.Empty ();
  start_variable = 0;
  roll_angle = 0;
}
void ATree::StepForward () {
  FString result;
  for ( TCHAR c : text_representation ) {
    FString *successor = rules.Find(c);
    if ( successor ) {
      result.Append (*successor);
    } else {
      result.Append (FString::Chr (c));
    }
  }
  text_representation = result;
}
void ATree::StepBackward () {}
void ATree::LogInputData () {
  for ( TCHAR c : variables ) {
    print (TEXT ("Variables: %c"), c)
  }
  print1 (TEXT ("Rules:"))
  for (auto &elem : rules ) {
    FString temp = FString::Printf(TEXT("%c -> %s"), elem.Key, *elem.Value);
    print (TEXT("%s"), *temp);
  }
  print (TEXT ("Roll angle: %f"), roll_angle);
}
void ATree::LogTextRepresentation(){
  print (TEXT ("Text represenation: %s"), *text_representation);
}
void ATree::Init () {
  text_representation = FString::Chr(start_variable);
}

ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATree::BeginPlay()
{
	Super::BeginPlay();
  
}
void ATree::OnConstruction(const FTransform &t){
  Clear ();
  ReadInput ();
  LogInputData ();
  Init ();
  LogTextRepresentation ();
}

void ATree::Tick( float DeltaTime ){ 
	Super::Tick( DeltaTime );
}


