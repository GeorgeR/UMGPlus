#include "Widgets/IntegerSpinBoxWidget.h"
#include "Engine/Font.h"

#define LOCTEXT_NAMESPACE "UMG"

UUPIntegerSpinBox::UUPIntegerSpinBox()
{
    if (!IsRunningDedicatedServer())
    {
        static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
        Font = FSlateFontInfo(RobotoFontObj.Object, 12, FName("Bold"));
    }

    // Grab other defaults from slate arguments.
    SSpinBox<int32>::FArguments Defaults;

    Value = Defaults._Value.Get();
    MinValue = Defaults._MinValue.Get().Get(0);
    MaxValue = Defaults._MaxValue.Get().Get(0);
    MinSliderValue = Defaults._MinSliderValue.Get().Get(0);
    MaxSliderValue = Defaults._MaxSliderValue.Get().Get(0);
    Delta = Defaults._Delta.Get();
    SliderExponent = Defaults._SliderExponent.Get();
    MinDesiredWidth = Defaults._MinDesiredWidth.Get();
    ClearKeyboardFocusOnCommit = Defaults._ClearKeyboardFocusOnCommit.Get();
    SelectAllTextOnCommit = Defaults._SelectAllTextOnCommit.Get();

    WidgetStyle = *Defaults._Style;
    ForegroundColor = FSlateColor(FLinearColor::Black);
}

void UUPIntegerSpinBox::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    SlateWidget.Reset();
}

TSharedRef<SWidget> UUPIntegerSpinBox::RebuildWidget()
{
    SlateWidget = SNew(SSpinBox<int32>)
        .Style(&WidgetStyle)
        .Font(Font)
        .ClearKeyboardFocusOnCommit(ClearKeyboardFocusOnCommit)
        .SelectAllTextOnCommit(SelectAllTextOnCommit)
        .Justification(Justification)
        .OnValueChanged(BIND_UOBJECT_DELEGATE(FOnInt32ValueChanged, HandleOnValueChanged))
        .OnValueCommitted(BIND_UOBJECT_DELEGATE(FOnInt32ValueCommitted, HandleOnValueCommitted))
        .OnBeginSliderMovement(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnBeginSliderMovement))
        .OnEndSliderMovement(BIND_UOBJECT_DELEGATE(FOnInt32ValueChanged, HandleOnEndSliderMovement))        ;

    return SlateWidget.ToSharedRef();
}

void UUPIntegerSpinBox::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    SlateWidget->SetDelta(Delta);
    SlateWidget->SetSliderExponent(SliderExponent);
    SlateWidget->SetMinDesiredWidth(MinDesiredWidth);

    SlateWidget->SetForegroundColor(ForegroundColor);

    // Set optional values
    bOverride_MinValue ? SetMinValue(MinValue) : ClearMinValue();
    bOverride_MaxValue ? SetMaxValue(MaxValue) : ClearMaxValue();
    bOverride_MinSliderValue ? SetMinSliderValue(MinSliderValue) : ClearMinSliderValue();
    bOverride_MaxSliderValue ? SetMaxSliderValue(MaxSliderValue) : ClearMaxSliderValue();

    // Always set the value last so that the max/min values are taken into account.
    TAttribute<int32> ValueBinding = PROPERTY_BINDING(int32, Value);
    SlateWidget->SetValue(ValueBinding);
}

int32 UUPIntegerSpinBox::GetValue() const
{
    if (SlateWidget.IsValid())
        return SlateWidget->GetValue();

    return Value;
}

void UUPIntegerSpinBox::SetValue(int32 NewValue)
{
    Value = NewValue;

    if (SlateWidget.IsValid())
        SlateWidget->SetValue(NewValue);
}

int32 UUPIntegerSpinBox::GetMinValue() const
{
    auto Result = TNumericLimits<int32>::Lowest();

    if (SlateWidget.IsValid())
        Result = SlateWidget->GetMinValue();
    else if (bOverride_MinValue)
        Result = MinValue;

    return Result;
}

void UUPIntegerSpinBox::SetMinValue(int32 NewValue)
{
    bOverride_MinValue = true;
    MinValue = NewValue;

    if (SlateWidget.IsValid())
        SlateWidget->SetMinValue(NewValue);
}

void UUPIntegerSpinBox::ClearMinValue()
{
    bOverride_MinValue = false;

    if (SlateWidget.IsValid())
        SlateWidget->SetMinValue(TOptional<int32>());
}

int32 UUPIntegerSpinBox::GetMaxValue() const
{
    auto Result = TNumericLimits<int32>::Max();

    if (SlateWidget.IsValid())
        Result = SlateWidget->GetMaxValue();
    else if (bOverride_MaxValue)
        Result = MaxValue;

    return Result;
}

void UUPIntegerSpinBox::SetMaxValue(int32 NewValue)
{
    bOverride_MaxValue = true;
    MaxValue = NewValue;

    if (SlateWidget.IsValid())
        SlateWidget->SetMaxValue(NewValue);
}

void UUPIntegerSpinBox::ClearMaxValue()
{
    bOverride_MaxValue = false;

    if (SlateWidget.IsValid())
        SlateWidget->SetMaxValue(TOptional<int32>());
}

int32 UUPIntegerSpinBox::GetMinSliderValue() const
{
    auto Result = TNumericLimits<int32>::Min();

    if (SlateWidget.IsValid())
        Result = SlateWidget->GetMinSliderValue();
    else if (bOverride_MinSliderValue)
        Result = MinSliderValue;

    return Result;
}

void UUPIntegerSpinBox::SetMinSliderValue(int32 NewValue)
{
    bOverride_MinSliderValue = true;
    MinSliderValue = NewValue;

    if (SlateWidget.IsValid())
        SlateWidget->SetMinSliderValue(NewValue);
}

void UUPIntegerSpinBox::ClearMinSliderValue()
{
    bOverride_MinSliderValue = false;

    if (SlateWidget.IsValid())
        SlateWidget->SetMinSliderValue(TOptional<int32>());
}

int32 UUPIntegerSpinBox::GetMaxSliderValue() const
{
    auto Result = TNumericLimits<int32>::Max();

    if (SlateWidget.IsValid())
        Result = SlateWidget->GetMaxSliderValue();
    else if (bOverride_MaxSliderValue)
        Result = MaxSliderValue;

    return Result;
}

void UUPIntegerSpinBox::SetMaxSliderValue(int32 NewValue)
{
    bOverride_MaxSliderValue = true;
    MaxSliderValue = NewValue;

    if (SlateWidget.IsValid())
        SlateWidget->SetMaxSliderValue(NewValue);
}

void UUPIntegerSpinBox::ClearMaxSliderValue()
{
    bOverride_MaxSliderValue = false;

    if (SlateWidget.IsValid())
        SlateWidget->SetMaxSliderValue(TOptional<int32>());
}

void UUPIntegerSpinBox::SetForegroundColor(FSlateColor InForegroundColor)
{
    ForegroundColor = InForegroundColor;

    if (SlateWidget.IsValid())
        SlateWidget->SetForegroundColor(ForegroundColor);
}

void UUPIntegerSpinBox::HandleOnValueChanged(int32 InValue)
{
    if (!IsDesignTime())
        OnValueChanged.Broadcast(InValue);
}

void UUPIntegerSpinBox::HandleOnValueCommitted(int32 InValue, ETextCommit::Type CommitMethod)
{
    if (!IsDesignTime())
        OnValueCommitted.Broadcast(InValue, CommitMethod);
}

void UUPIntegerSpinBox::HandleOnBeginSliderMovement()
{
    if (!IsDesignTime())
        OnBeginSliderMovement.Broadcast();
}

void UUPIntegerSpinBox::HandleOnEndSliderMovement(int32 InValue)
{
    if (!IsDesignTime())
        OnEndSliderMovement.Broadcast(InValue);
}

#if WITH_EDITOR
const FText UUPIntegerSpinBox::GetPaletteCategory()
{
    return LOCTEXT("UMGPlus", "UMG Plus");
}
#endif

#undef LOCTEXT_NAMESPACE