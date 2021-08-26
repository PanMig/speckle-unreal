#include "SpecklePanel.h"

#include "CustomComboBox.h"
#include "EngineUtils.h"
#include "PanelButton.h"
#include "Engine/World.h"
#include "SpeckleStyle.h"
#include "SpeckleUnrealManager.h"
#include "Chaos/ChaosPerfTest.h"

#define LOCTEXT_NAMESPACE "SpecklePanel"

//const auto TextStyle = FSpeckleStyle::Get()->GetFontStyle("Speckle.DefaultText");
FSlateFontInfo TextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");

void SpecklePanel::Construct(const FArguments& InArgs)
{
	Init();

	TextStyle.Size = 12.0f;
	TArray<TSharedPtr<FString>> SpeckleManagerNames;
	for (auto SM : SpeckleManagers)
	{
		SpeckleManagerNames.Add(MakeShared<FString>(SM->GetName()));
	}

	auto StreamID = FString(TEXT("Stream: Unspecified"));
	if(CurrentSpeckleManager != nullptr)
	{
		StreamID = FString(CurrentSpeckleManager->StreamID);		
	}
	
	ChildSlot
    [
        SNew(SScrollBox)
        + SScrollBox::Slot()
        .VAlign(VAlign_Top)
        .Padding(10)
        [
        	SNew(SOverlay)
            +SOverlay::Slot()
            .HAlign(EHorizontalAlignment::HAlign_Left)
            .VAlign(EVerticalAlignment::VAlign_Top)
            .Padding(10)
            [
				SNew(STextBlock)
				.Text(FText::FromString(StreamID))
				.Font(TextStyle)
            ]
            
            +SOverlay::Slot()
            .HAlign(EHorizontalAlignment::HAlign_Right)
            .VAlign(EVerticalAlignment::VAlign_Top)
            [
            	SNew(SBox)
            	.WidthOverride(32)
            	.HeightOverride(32)
            	[
            		SNew(SButton)
            		.HAlign(EHorizontalAlignment::HAlign_Fill)
            		.VAlign(EVerticalAlignment::VAlign_Fill)
					.OnClicked(this, &SpecklePanel::ReceiveButtonClicked)
					[
						SNew(SImage)
						.Image(FSpeckleStyle::Get()->GetBrush("Speckle.ChangeModeIcon"))
					]
            	]
            ]
		]

		+ SScrollBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
        .Padding(10)
        [
			SNew(SCustomComboBox)
			.ComboOptions(SpeckleManagerNames)
        ]
		
		+ SScrollBox::Slot()
		.VAlign(EVerticalAlignment::VAlign_Top)
		[
			HorizontalActionsPanel()
		]
    ];
}

FReply SpecklePanel::ReceiveButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Import clicked"));
	return FReply::Handled();
}

TSharedRef<SWidget> SpecklePanel::HorizontalActionsPanel()
{	
	TArray<TSharedPtr<FString>> Options;
	Options.Add(MakeShareable(new FString("Option1")));
	Options.Add(MakeShareable(new FString("Option2")));
	Options.Add(MakeShareable(new FString("Option3")));
	
	auto HorizontalPanel = SNew(SOverlay)
    +SOverlay::Slot()
    .HAlign(EHorizontalAlignment::HAlign_Left)
    .VAlign(EVerticalAlignment::VAlign_Fill)
	.Padding(FMargin(10,10,50,10))
    [
		 SNew(SCustomComboBox)
		.ComboOptions(Options)
    ]

	+SOverlay::Slot()
    .HAlign(EHorizontalAlignment::HAlign_Left)
    .VAlign(EVerticalAlignment::VAlign_Fill)
	.Padding(FMargin(100,10,50,10))
    [
		SNew(SCustomComboBox)
		.ComboOptions(Options)
    ]
	
    +SOverlay::Slot()
    .HAlign(EHorizontalAlignment::HAlign_Right)
    .VAlign(EVerticalAlignment::VAlign_Fill)
	.Padding(FMargin(0,10,0,10))

    [
		SNew(SPanelButton)
		.Label(TEXT("Receive"))
		.ButtonClicked(this, &SpecklePanel::ReceiveButtonClicked)
		.ImageBrush(FSpeckleStyle::Get()->GetBrush("Speckle.ReceiveIcon"))
    ];

	return HorizontalPanel;
}

void SpecklePanel::Init()
{
	const auto EditorWorld = GEditor->GetEditorWorldContext().World();

	for(TActorIterator<ASpeckleUnrealManager> It(EditorWorld); It; ++It)
	{
		SpeckleManagers.Add(*It);
	}

	if(SpeckleManagers.Num() > 0)
	{
		CurrentSpeckleManager = SpeckleManagers[0];
	}
}

#undef LOCTEXT_NAMESPACE
