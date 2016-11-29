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

void ATree::Clear () {

  turtle_pos = GetActorLocation ();
  turtle_dir = FVector (0, 0, 1);
  for ( ABranch *b : branches ) {
    if(!b->IsPendingKillOrUnreachable())
      b->Destroy ();
  }
  branches.Empty ();
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
  CloseBranch ();
  check (branchStack.Num()==0);
  Draw ();
}
void ATree::Forward () {
  turtle_pos += turtle_dir * 100;
  branchStack.Top ()->AddPoint (turtle_pos);
  /*print (TEXT("New turtle_pos x: %f"), turtle_pos.X);
  print (TEXT("New turtle_pos y: %f"), turtle_pos.Y);
  print (TEXT("New turtle_pos z: %f"), turtle_pos.Z);*/

}
void ATree::NewBranch () {
  ABranch *newBranch = GetWorld ()->SpawnActor<ABranch> ();
  newBranch->AddPoint (turtle_pos);
  newBranch->Init (turtle_dir);
  branchStack.Add(newBranch);
  pos_stack.Add (turtle_pos);
  dir_stack.Add (turtle_dir);
}
void ATree::CloseBranch () {
  branches.Add (branchStack.Pop ());
  turtle_pos = pos_stack.Pop ();
  turtle_dir = dir_stack.Pop ();
}
void ATree::RollCW () {
  turtle_dir = turtle_dir.RotateAngleAxis (25, FVector (0, 1, 0));
}
void ATree::RollCCW () {
  turtle_dir = turtle_dir.RotateAngleAxis (-25, FVector (0, 1, 0));
}
void ATree::Draw () {
  for ( ABranch* bp : branches ) {
    bp->Draw ();
  }
}