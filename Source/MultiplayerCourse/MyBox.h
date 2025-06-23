// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBox.generated.h"

class UParticleSystem;

UCLASS()
class MULTIPLAYERCOURSE_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedVar, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ReplicatedVar;

	FTimerHandle TestTimer;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionEffect;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void OnRep_ReplicatedVar();

	void DecreseReplicatedVar();
	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void MulticastRPCExplode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
