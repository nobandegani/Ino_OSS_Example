// // Copyright Inoland, All Rights Reserved.


#include "GI_Ino.h"

//IOnlineSubsystem* ion = IOnlineSubsystem::Get(FName("Ino_OSS")); for forcing to get the ino_oss

void UGI_Ino::Init()
{
	ReceiveInit();
	UE_LOG(LogTemp, Error, TEXT("gi is initialized"));
}