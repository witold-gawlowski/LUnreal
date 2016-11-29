#include "LUnreal.h"
#include "Tree.h"

#define print1(XXX) UE_LOG (LogTemp, Warning, XXX);
#define print(XXX, YYY)  UE_LOG (LogTemp, Warning, XXX, YYY);
ATree::ATree(){
	PrimaryActorTick.bCanEverTick = true;
  SceneComponent = CreateDefaultSubobject<USceneComponent> (TEXT ("Tree Root"));
  RootComponent = SceneComponent;
}
void ATree::BeginPlay(){
	Super::BeginPlay();
 
}
void ATree::Tick( float DeltaTime ){ 
	Super::Tick( DeltaTime );
}
void ATree::Init (FString s) {
  text_representation = s;
  turtle_pos = GetActorLocation ();
  turtle_dir = FVector (0, 0, 1);
}
void ATree::Build () {
  NewBranch ();
  for ( TCHAR c : text_representation ) {
    //print (TEXT ("BUILD LOOP %c"), c);
    switch ( c ) {
    case 'F':
      Forward ();
      break;
    case '[':
      NewBranch ();
      break;
    case ']':
      CloseBranch ();
      break;
    case '+':
      RollCW ();
      break;
    case '-':
      RollCCW ();
      break;
    }
  }
}
void ATree::Forward () {
  turtle_pos += turtle_dir * 100;
  branchStack.Top ()->AddPoint (turtle_pos);
}
void ATree::NewBranch () {
  ABranch *newBranch = GetWorld ()->SpawnActor<ABranch> (turtle_pos, turtle_dir.Rotation ());
  newBranch->AddPoint (turtle_pos);
  branchStack.Add(newBranch);
}
void ATree::CloseBranch () {
  branches.Add (branchStack.Pop ());
}
void ATree::RollCW () {
  turtle_dir.RotateAngleAxis (25, FVector (1, 0, 0));
}
void ATree::RollCCW () {
  turtle_dir.RotateAngleAxis (-25, FVector (1, 0, 0));
}
void ATree::Draw () {
  for ( ABranch* bp : branches ) {
    bp->Draw ();
  }
}