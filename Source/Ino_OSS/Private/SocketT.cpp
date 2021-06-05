// // Copyright Inoland, All Rights Reserved.


#include "SocketT.h"

#include "HAL/PlatformApplicationMisc.h"



void ASocketT::TCPConnectionListener()
{
	//~~~~~~~~~~~~~
	if(!InoListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Listener Socket = 0 ! ")));
		return;
	}
	//~~~~~~~~~~~~~

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	
	
	//TSharedPtr<FInternetAddr> RemoteAddress = MakeShareable(FInternetAddr( ));
	//FInternetAddr RemoteAddress (127,0,0,1);
	bool Pending;
 
	// handle incoming connections
	if (InoListenerSocket->HasPendingConnection(Pending) && Pending)
	{ 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Already have a Connection? destroy previous
		if(InoConnectionSocket)
		{
			InoConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(InoConnectionSocket);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Connection Socket Destroyed!")));
			UE_LOG(LogTemp, Warning,TEXT("Connection Socket Destroyed!") );
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//New Connection receive!
		InoConnectionSocket = InoListenerSocket->Accept(*RemoteAddress, TEXT("Received Socket Connection"));
		//InoConnectionSocket = InoListenerSocket->Accept()
		UE_LOG(LogTemp, Warning,TEXT("Received Socket Connection") ); 
		if (InoConnectionSocket != NULL)
		{
			//Global cache of current Remote Address
			
			InoRemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);
			//InoRemoteAddressForConnection.
			uint32 ip4ff;
			RemoteAddress->GetIp(ip4ff);
			int32 port4ff = RemoteAddress->GetPort();
			
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Connection Accepted! ")));
			UE_LOG(LogTemp, Warning,TEXT("Connection Accepted! IP: %i - Port: %i"), ip4ff,  port4ff);
			//can thread this too
			//GetWorldTimerManager().SetTimer(THandle2, this, &ASocketT::TCPSocketListener, 0.01, true);    
		}
	}
}

void ASocketT::TCPSocketListener()
{
	//~~~~~~~~~~~~~
	if(!InoConnectionSocket) return;
	//~~~~~~~~~~~~~

	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (InoConnectionSocket->HasPendingData(Size))
	{	
		ReceivedData.Init( 0, FMath::Min(Size, 65507u));
		int32 Read = 0;
		InoConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
		UE_LOG(LogTemp, Warning,TEXT("Data Read! %d"), ReceivedData.Num() );
		const FString ReceivedUE4String = FString ( (TCHAR*)FUTF8ToTCHAR((const ANSICHAR*) ReceivedData.GetData() ).Get() );
		UE_LOG( LogTemp, Warning, TEXT("Data Read: %s"), *ReceivedUE4String );
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

void ASocketT::InoStartSocket(FString InputSocketName, FString InputIP, int32 InputPort)
{
	FIPv4Address InoIPv4( 127, 0, 0, 1);
	FIPv4Endpoint Endpoint(InoIPv4, InputPort);
	InoListenerSocket = FTcpSocketBuilder(*InputSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	const int32 ReceiveBufferSize = 2*1024*1024;
	int32 NewSize = 0;
	InoListenerSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	if(!InoListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket could not be created! ~> %s %d"), *InputIP, InputPort));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket created! ~> %s %d"), *InputIP, InputPort));

		//Start the Listener! //thread this eventually
		GetWorldTimerManager().SetTimer(THandle1, this, &ASocketT::TCPConnectionListener, 0.01, true);    
	}

	//FString ( (TCHAR*)FUTF8ToTCHAR((const ANSICHAR*) BinaryArray.GetData() ).Get() );
	
}

void ASocketT::InoTickLogin()
{
	FString Title;
    if ( FPlatformApplicationMisc::GetWindowTitleMatchingText(TEXT("access_token"), Title) )
    {
    	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("found")));
    	InoLogin(Title);
    	GetWorldTimerManager().ClearTimer(THandle3);
    }
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("try to find")));
	}
}

void ASocketT::InoLogin(FString Input)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("access_key: %s"), *Input));
	int32 sp =  Input.Find("=",ESearchCase::IgnoreCase, ESearchDir::FromStart, 5);
	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("access_key: %s"), *Input));
	
	FString mysr =  Input.Mid(sp + 1,29);
	
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("access_key: %s"), *mysr));
}


// Sets default values
ASocketT::ASocketT()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocketT::BeginPlay()
{
	Super::BeginPlay();

	FString Endpoint_URL = "https://nation.inoland.site/wp-admin/authorize-application.php";
	FString APP_Name = "ino-oss";
	FString APP_ID = "c19d9237-20d3-49e9-b789-77f47e3ad79b";
	
	//FString Success_URL = "http%3A%2F%2F127.0.0.1%3A9992";
	FString Success_URL = "https://api.inoland.site/test/test.php";
	
	//FString Reject_URL = "http%3A%2F%2F127.0.0.1%3A9992";
	FString Reject_URL = "";
	const FString& Command = FString::Printf(TEXT("%s?app_name=%s&app_id=%s&success_url=%s&reject_url=%s"), *Endpoint_URL, *APP_Name, *APP_ID, *Success_URL, *Reject_URL);
	FPlatformMisc::OsExecute(TEXT("open"), *Command);
	 
	//InoStartSocket("RamaSocketListener", "127.0.0.1", 9992);

    GetWorldTimerManager().SetTimer(THandle3, this, &ASocketT::InoTickLogin, 0.1, true);  
}

void ASocketT::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if ( InoConnectionSocket ){
		InoConnectionSocket->Shutdown(ESocketShutdownMode::ReadWrite);
		InoConnectionSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(InoConnectionSocket);
	}
	if ( InoListenerSocket )
	{
		InoListenerSocket->Shutdown(ESocketShutdownMode::ReadWrite);
		InoListenerSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(InoListenerSocket);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASocketT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

