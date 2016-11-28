#include "LUnreal.h"
#include "Tree.h"


ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATree::BeginPlay()
{
	Super::BeginPlay();
  branch = GetWorld ()->SpawnActor<ABranch> ();
}
void ATree::OnConstruction(const FTransform &t){

}

void ATree::Tick( float DeltaTime ){ 
	Super::Tick( DeltaTime );
}


