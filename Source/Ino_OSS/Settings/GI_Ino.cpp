// // Copyright Inoland, All Rights Reserved.


#include "GI_Ino.h"
#include "OnlineSubsystemIno/Private/OnlineAccountIno.h"
//IOnlineSubsystem* ion = IOnlineSubsystem::Get(FName("Ino_OSS")); for forcing to get the ino_oss

void UGI_Ino::MyHttpCall()
{
	UE_LOG(LogTemp, Display, TEXT("MyHyypCall is called"));
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGI_Ino::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("https://api.inoland.site/test/test.php");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UGI_Ino::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Display, TEXT("OnResponseReceived is called"));
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;
	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<FString>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		int32 recievedInt = JsonObject->GetIntegerField("customInt");
		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	}
}

void UGI_Ino::ILogin()
{

	IAccount.Type = "WordPress";
	IAccount.Id = "myfuckingusername";
	IAccount.Token = "myfuckingpassword";

	if (IIdentityInterface.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(0, 50.0f, FColor::Green, TEXT("nicely done!"));
		IIdentityInterface->Login(0, IAccount);
	} 
	
}

void UGI_Ino::AutoLogin()
{
	IIdentityInterface->AutoLogin();
}

void UGI_Ino::Init()
{
	//ReceiveInit();
	UE_LOG(LogTemp, Warning, TEXT("gi is initialized"));

	//Http = &FHttpModule::Get();
	//MyHttpCall();

	IOSS = IOnlineSubsystem::Get(FName("Ino"));
	
	//IOnlineSubsystem* ion = IOnlineSubsystem::Get(FName("Ino"));
	IIdentityInterface = IOSS->GetIdentityInterface();

}

