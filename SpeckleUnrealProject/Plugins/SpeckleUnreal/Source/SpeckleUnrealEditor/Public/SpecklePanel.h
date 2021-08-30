#pragma once
#include "CustomComboBox.h"

class ASpeckleUnrealManager;

class SpecklePanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SpecklePanel) {}

	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

private:
	FReply ReceiveButtonClicked();
	
	TSharedRef<SWidget> HorizontalActionsPanel();

	void Init();
	
	template<typename T>
	UFUNCTION(BlueprintCallable)
	void FindAllActors(UWorld* World, TArray<T*>& Out)
	{
		for (TActorIterator<T> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	}

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpeckleUnrealManager> SpeckleManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASpeckleUnrealManager* CurrentSpeckleManager;

	UPROPERTY()
	TArray<ASpeckleUnrealManager*> SpeckleManagers;
	
	// TSharedRef<SWidget> BranchesCBox;
	// TSharedRef<SWidget> CommitsCBox;
	// TSharedRef<SWidget> ManagersCBox;
};
