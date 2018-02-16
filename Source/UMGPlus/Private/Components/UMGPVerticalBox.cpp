#include "UMGPVerticalBox.h"

TSharedRef<SWidget> UUMGPVerticalBox::RebuildWidget()
{
	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	return Widget;
}

void UUMGPVerticalBox::OnSlotAdded(UPanelSlot* Slot)
{
	auto o = 123;
}