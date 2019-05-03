#include "Widgets/WindowContainerWidget.h"

UWindowContainerWidget::UWindowContainerWidget()
{
	bUseBlur = false;
	BlurAmount = 4.0f;

	bUseWash = false;
	WashColor = FLinearColor::White;
}