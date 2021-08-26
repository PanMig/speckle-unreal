#include "CustomComboBox.h"

void SCustomComboBox::Construct(const FArguments& InArgs)
{
	ComboOptions = InArgs._ComboOptions;
	
	CurrentItem = ComboOptions[0];
 
	ChildSlot
    [
		SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&ComboOptions)
		.OnSelectionChanged(this, &SCustomComboBox::OnSelectionChanged)
		.OnGenerateWidget(this, &SCustomComboBox::MakeWidgetForOption)
		.InitiallySelectedItem(CurrentItem)
		[
			SNew(STextBlock)
			.Text(this, &SCustomComboBox::GetCurrentItemLabel)
		]
    ];
}

FText SCustomComboBox::GetCurrentItemLabel() const
{
	if (CurrentItem.IsValid())
	{
		return FText::FromString(*CurrentItem);
	}
 
	return FText::FromString("Invalid Combo box Item");
}
