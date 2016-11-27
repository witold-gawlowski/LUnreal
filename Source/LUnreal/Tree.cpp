#include "LUnreal.h"
#include "Tree.h"

#define print(XXX, YYY)  UE_LOG (LogTemp, Warning, XXX, YYY);

FString ATree::Rule::ToString () {
  return FString::Printf (TEXT ("Left: %c, Right: %s"), left, *right);
}
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
    rules.Add (Rule (temp[0][0], temp[2]));
  }
}
// not tested
void ATree::Clear () {
  rules.Empty ();
  variables.Empty ();
  start_variable = NULL;
  roll_angle = 0;
}
void ATree::LogInputData () {
  for ( TCHAR c : variables ) {
    print (TEXT ("Variables: %c"), c)
  }
  for ( Rule r : rules ) {
    print (TEXT ("Rules: %s"), *r.ToString ());
  }
  print (TEXT ("Roll angle: %f"), roll_angle);
}
void ATree::Init () {

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
}
void ATree::Tick( float DeltaTime ){ 
	Super::Tick( DeltaTime );
}


