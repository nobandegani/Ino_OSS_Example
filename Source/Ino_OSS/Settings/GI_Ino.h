// // Copyright Inoland, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Online.h"
#include "Http.h"

#include "GI_Ino.generated.h"

/**
 * 
 */
UCLASS()
class INO_OSS_API UGI_Ino : public UGameInstance
{
	GENERATED_BODY()

public:
	
	FHttpModule* Http = nullptr;

	/* The actual HTTP call */
	UFUNCTION(BlueprintCallable)
	void MyHttpCall();

	//UFUNCTION()
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



	IOnlineSubsystem* IOSS = nullptr;
	IOnlineIdentityPtr IIdentityInterface = nullptr;
	FOnlineAccountCredentials IAccount;

	UFUNCTION(BlueprintCallable)
	void ILogin();
	void AutoLogin();
protected:
	virtual void Init() override;
};
