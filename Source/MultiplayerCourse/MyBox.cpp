// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.f;
	//bReplicates = true;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicates(true);
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreseReplicatedVar, 2.f, false);
	}
	
}

void AMyBox::DecreseReplicatedVar()
{
	if (HasAuthority())
	{
		ReplicatedVar -= 1.f;
		OnRep_ReplicatedVar();
		if (ReplicatedVar > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreseReplicatedVar, 2.f, false);
		}
		
	}
	
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if 0
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Server"), true);
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Server"), true);
	}
#endif
}

void AMyBox::OnRep_ReplicatedVar()
{
	if (HasAuthority())
	{
		FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, 200.f);
		SetActorLocation(NewLocation);
		
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"), true);
	} else {
		int32 EditorID = UE::GetPlayInEditorID();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, 
			FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), EditorID), true
		);
	}
	
}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

