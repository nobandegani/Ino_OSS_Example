// // Copyright Inoland, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Networking.h"

#include "SocketT.generated.h"

UCLASS()
class INO_OSS_API ASocketT : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocketT();

	FTimerHandle THandle1;
	FTimerHandle THandle2;
	FTimerHandle THandle3;

	//Timer functions, could be threads
	UFUNCTION(BlueprintCallable)
	void TCPConnectionListener();   //can thread this eventually
	UFUNCTION(BlueprintCallable)
	void TCPSocketListener();       //can thread this eventually

	FSocket* InoListenerSocket = nullptr;
	FSocket* InoConnectionSocket = nullptr;
	FIPv4Endpoint InoRemoteAddressForConnection;
	
	UFUNCTION(BlueprintCallable)
	void InoStartSocket(FString InputSocketName = "RamaSocketListener", FString InputIP = "127.0.0.1", int32 InputPort = 8890);

	void InoTickLogin ();

	void InoLogin(FString Input);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
