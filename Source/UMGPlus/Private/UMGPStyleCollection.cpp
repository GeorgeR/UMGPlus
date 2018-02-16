#include "UMGPStyleCollection.h"
#include "UMGPStyle.h"
#include "EngineMinimal.h"
#include "Components/Border.h"

UUMGPStyleCollection* UUMGPStyleCollection::Default = nullptr;

UUMGPStyleCollection* UUMGPStyleCollection::GetDefault()
{
	if (Default == nullptr)
	{
		Default = NewObject<UUMGPStyleCollection>(GetTransientPackage());

		auto BorderStyle = NewObject<UUMGPStyle>(Default);
		BorderStyle->Selector = TEXT("Border UMGPBorder");
		BorderStyle->Update();
		Default->Styles.Add(BorderStyle);

		auto ButtonStyle = NewObject<UUMGPStyle>(Default);
		ButtonStyle->Selector = TEXT("Button UMGPButton");
		ButtonStyle->Update();
		Default->Styles.Add(ButtonStyle);

		auto CanvasPanelStyle = NewObject<UUMGPStyle>(Default);
		CanvasPanelStyle->Selector = TEXT("CanvasPanel UMGPCanvasPanel");
		CanvasPanelStyle->Update();
		Default->Styles.Add(CanvasPanelStyle);

		auto CanvasPanelSlotStyle = NewObject<UUMGPStyle>(Default);
		CanvasPanelSlotStyle->Selector = TEXT("CanvasPanelSlot UMGPCanvasPanelSlot");
		CanvasPanelSlotStyle->Update();
		Default->Styles.Add(CanvasPanelSlotStyle);

		auto CheckboxStyle = NewObject<UUMGPStyle>(Default);
		CheckboxStyle->Selector = TEXT("Checkbox UMGPCheckbox");
		CheckboxStyle->Update();
		Default->Styles.Add(CheckboxStyle);

		auto ComboBoxStyle = NewObject<UUMGPStyle>(Default);
		ComboBoxStyle->Selector = TEXT("ComboBox, UMGPComboBox");
		ComboBoxStyle->Update();
		Default->Styles.Add(ComboBoxStyle);

		auto ComboBoxStringStyle = NewObject<UUMGPStyle>(Default);
		ComboBoxStringStyle->Selector = TEXT("ComboBoxString UMGPComboBoxString");
		ComboBoxStringStyle->Update();
		Default->Styles.Add(ComboBoxStringStyle);

		auto EditableTextStyle = NewObject<UUMGPStyle>(Default);
		EditableTextStyle->Selector = TEXT("EditableText UMGPEditableText");
		EditableTextStyle->Update();
		Default->Styles.Add(EditableTextStyle);

		auto EditableTextBoxStyle = NewObject<UUMGPStyle>(Default);
		EditableTextBoxStyle->Selector = TEXT("EditableTextBox UMGPEditableTextBox");
		EditableTextBoxStyle->Update();
		Default->Styles.Add(EditableTextBoxStyle);

		auto ExpandableAreaStyle = NewObject<UUMGPStyle>(Default);
		ExpandableAreaStyle->Selector = TEXT("ExpandableArea UMGPExpandableArea");
		ExpandableAreaStyle->Update();
		Default->Styles.Add(ExpandableAreaStyle);

		auto GridPanelStyle = NewObject<UUMGPStyle>(Default);
		GridPanelStyle->Selector = TEXT("GridPanel UMGPGridPanel");
		GridPanelStyle->Update();
		Default->Styles.Add(GridPanelStyle);

		auto GridSlotStyle = NewObject<UUMGPStyle>(Default);
		GridPanelStyle->Selector = TEXT("GridSlot UMGPGridSlot");
		GridPanelStyle->Update();
		Default->Styles.Add(GridPanelStyle);

		auto HorizontalBoxStyle = NewObject<UUMGPStyle>(Default);
		HorizontalBoxStyle->Selector = TEXT("HorizontalBox UMGPHorizontalBox");
		HorizontalBoxStyle->Update();
		Default->Styles.Add(HorizontalBoxStyle);

		auto HorizontalBoxSlotStyle = NewObject<UUMGPStyle>(Default);
		HorizontalBoxSlotStyle->Selector = TEXT("HorizontalBoxSlot UMGPHorizontalBoxSlot");
		HorizontalBoxSlotStyle->Update();
		Default->Styles.Add(HorizontalBoxSlotStyle);
		
		auto ImageStyle = NewObject<UUMGPStyle>(Default);
		ImageStyle->Selector = TEXT("Image UMGPImage");
		ImageStyle->Update();
		Default->Styles.Add(ImageStyle);

		auto MultiLineEditableTextStyle = NewObject<UUMGPStyle>(Default);
		MultiLineEditableTextStyle->Selector = TEXT("MultiLineEditableText UMGPMultiLineEditableText");
		MultiLineEditableTextStyle->Update();
		Default->Styles.Add(MultiLineEditableTextStyle);

		auto MultiLineEditableTextBoxStyle = NewObject<UUMGPStyle>(Default);
		MultiLineEditableTextBoxStyle->Selector = TEXT("MultiLineEditableTextBox UMGPMultiLineEditableTextBox");
		MultiLineEditableTextBoxStyle->Update();
		Default->Styles.Add(MultiLineEditableTextBoxStyle);

		auto OverlayStyle = NewObject<UUMGPStyle>(Default);
		OverlayStyle->Selector = TEXT("Overlay UMGPOverlay");
		OverlayStyle->Update();
		Default->Styles.Add(OverlayStyle);

		auto ProgressBarStyle = NewObject<UUMGPStyle>(Default);
		ProgressBarStyle->Selector = TEXT("ProgressBar UMGPProgressBar");
		ProgressBarStyle->Update();
		Default->Styles.Add(ProgressBarStyle);

		auto RichTextBlockStyle = NewObject<UUMGPStyle>(Default);
		RichTextBlockStyle->Selector = TEXT("RichTextBlock UMGPRichTextBlock");
		RichTextBlockStyle->Update();
		Default->Styles.Add(RichTextBlockStyle);

		auto ScaleBoxStyle = NewObject<UUMGPStyle>(Default);
		ScaleBoxStyle->Selector = TEXT("ScaleBox UMGPScaleBox");
		ScaleBoxStyle->Update();
		Default->Styles.Add(ScaleBoxStyle);

		auto ScrollBoxStyle = NewObject<UUMGPStyle>(Default);
		ScrollBoxStyle->Selector = TEXT("ScrollBox UMGPScrollBox");
		ScrollBoxStyle->Update();
		Default->Styles.Add(ScrollBoxStyle);

		auto ScrollBoxSlotStyle = NewObject<UUMGPStyle>(Default);
		ScrollBoxSlotStyle->Selector = TEXT("ScrollBoxSlot UMGPScrollBoxSlot");
		ScrollBoxSlotStyle->Update();
		Default->Styles.Add(ScrollBoxSlotStyle);

		auto SizeBoxStyle = NewObject<UUMGPStyle>(Default);
		SizeBoxStyle->Selector = TEXT("SizeBox UMGPSizeBox");
		SizeBoxStyle->Update();
		Default->Styles.Add(SizeBoxStyle);

		auto SizeBoxSlotStyle = NewObject<UUMGPStyle>(Default);
		SizeBoxSlotStyle->Selector = TEXT("SizeBoxSlot UMGPSizeBoxSlot");
		SizeBoxSlotStyle->Update();
		Default->Styles.Add(SizeBoxSlotStyle);

		auto SliderStyle = NewObject<UUMGPStyle>(Default);
		SliderStyle->Selector = TEXT("Slider UMGPSlider");
		SliderStyle->Update();
		Default->Styles.Add(SliderStyle);

		auto SpacerStyle = NewObject<UUMGPStyle>(Default);
		SpacerStyle->Selector = TEXT("Spacer UMGPSpacer");
		SpacerStyle->Update();
		Default->Styles.Add(SpacerStyle);

		auto SpinBoxStyle = NewObject<UUMGPStyle>(Default);
		SpinBoxStyle->Selector = TEXT("SpinBox, UMGPSpinBox");
		SpinBoxStyle->Update();
		Default->Styles.Add(SpinBoxStyle);

		auto TextBlockStyle = NewObject<UUMGPStyle>(Default);
		TextBlockStyle->Selector = TEXT("TextBlock UMGPTextBlock");
		TextBlockStyle->Update();
		Default->Styles.Add(TextBlockStyle);

		auto ThrobberStyle = NewObject<UUMGPStyle>(Default);
		ThrobberStyle->Selector = TEXT("Throbber UMGPThrobber");
		ThrobberStyle->Update();
		Default->Styles.Add(ThrobberStyle);

		auto UniformGridPanelStyle = NewObject<UUMGPStyle>(Default);
		UniformGridPanelStyle->Selector = TEXT("UniformGridPanel UMGPUniformGridPanel");
		UniformGridPanelStyle->Update();
		Default->Styles.Add(UniformGridPanelStyle);

		auto UniformGridSlotStyle = NewObject<UUMGPStyle>(Default);
		UniformGridSlotStyle->Selector = TEXT("UniformGridSlot UMGPUniformGridSlot");
		UniformGridSlotStyle->Update();
		Default->Styles.Add(UniformGridSlotStyle);

		auto VerticalBoxStyle = NewObject<UUMGPStyle>(Default);
		VerticalBoxStyle->Selector = TEXT("VerticalBox UMGPVerticalBox");
		VerticalBoxStyle->Update();
		Default->Styles.Add(VerticalBoxStyle);

		auto VerticalBoxSlotStyle = NewObject<UUMGPStyle>(Default);
		VerticalBoxSlotStyle->Selector = TEXT("VerticalBoxSlot UMGPVerticalBoxSlot");
		VerticalBoxSlotStyle->Update();
		Default->Styles.Add(VerticalBoxSlotStyle);

		auto WidgetStyle = NewObject<UUMGPStyle>(Default);
		WidgetStyle->Selector = TEXT("Widget UMGPWidget");
		WidgetStyle->Update();
		Default->Styles.Add(WidgetStyle);

		auto WidgetSwitcherStyle = NewObject<UUMGPStyle>(Default);
		WidgetSwitcherStyle->Selector = TEXT("WidgetSwitcher UMGPWidgetSwitcher");
		WidgetSwitcherStyle->Update();
		Default->Styles.Add(WidgetSwitcherStyle);

		auto WidgetSwitcherSlotStyle = NewObject<UUMGPStyle>(Default);
		WidgetSwitcherSlotStyle->Selector = TEXT("WidgetSwitcherSlot UMGPWidgetSwitcherSlot");
		WidgetSwitcherSlotStyle->Update();
		Default->Styles.Add(WidgetSwitcherSlotStyle);

		auto WrapBoxStyle = NewObject<UUMGPStyle>(Default);
		WrapBoxStyle->Selector = TEXT("WrapBox UMGPWrapBox");
		WrapBoxStyle->Update();
		Default->Styles.Add(WrapBoxStyle);

		auto WrapBoxSlotStyle = NewObject<UUMGPStyle>(Default);
		WrapBoxSlotStyle->Selector = TEXT("WrapBoxSlot UMGPWrapBoxSlot");
		WrapBoxSlotStyle->Update();
		Default->Styles.Add(WrapBoxSlotStyle);
	}

	return Default;
}

void UUMGPStyleCollection::ApplyTo(UWidget* InWidget)
{
	TArray<UUMGPStyle*> Styles = GetStylesForWidget(InWidget);
	for (auto i = 0; i < Styles.Num(); i++)
		Styles[i]->ApplyTo(InWidget);
}

TArray<UUMGPStyle*> UUMGPStyleCollection::GetStylesForWidget(UWidget* InWidget)
{
	return TArray<UUMGPStyle*>();
}