#include "UMGPListView.h"

//UUMGPListView::UUMGPListView()
///*: ItemHeight(128.0f),
//	ListItemClass(nullptr),
//	SelectionMode(ESelectionMode::Single),
//	ConsumeMouseWHeel(EConsumeMouseWheel::WhenScrollingPossible),
//	bClearSelectionOnClick(false),
//	NumPreAllocatedEntries(1)*/
//{
//	//Visibility = ESlateVisibility::Visible;
//}

//TSharedRef<SWidget> UUMGPListView::RebuildWidget()
//{
//	if (!IsDesignTime())
//	{
//		UE_LOG(LogTemp, Error, TEXT("[%s] has no row widget class specified!"), *GetName());
//
//		UClass* ItemClass = ListItemClass != nullptr ? *ListItemClass : UUserWidget::StaticClass();
//		ItemWidgets = TWidgetFactory<UUserWidget>(
//			ItemClass,
//			[this]()->UGameInstance*
//		{
//			return GetWorld()->GetGameInstance();
//		});
//
//		ItemWidgets.PreConstruct(NumPreAllocatedEntries);
//	}
//
//	TSharedPtr<SScissorRectBox> ScissorRectBox = SNew(SScissorRectBox)
//		[
//			RebuildListWidget()
//		];
//
//	return BuildDesignTimeWidget(SScissorRectBox.ToSharedRef());
//}
//
//int32 UUMGPListView::GetSelectedIndex()
//{
//}
//
//UObject* UUMGPListView::GetSelectedItem()
//{
//}
//
//bool UUMGPListView::GetSelectedItems(TArray<UObject *>& Items)
//{
//}
//
//bool UUMGPListView::IsSelected(UObject* Item)
//{
//}
//
//
//TSharedRef<SListView<UObject*>> UUMGPListView::RebuildListWidget()
//{
//	ListView = SNew(SListView<UObject*>)
//		.HandleGamepadEvents(false)
//		.SelectionMode(SelectionMode)
//		.ListItemsSource(&Context->AsArray())
//		.ClearSelectionOnClick(bClearSelectionOnClick)
//		.ItemHeight(GetTotalItemHeight())
//		.ConsumeMouseWheel(EConsumeMouseWheel::WhenScrollingPossible)
//		.OnGenerateRow_UObject(this, &ThisClass::OnGenerateRow)
//		.OnMouseButtonClick_UObject(this, &ThisClass::OnItemClicked)
//		.OnSelectionChanged_UObject(this, &ThisClass::OnSelectionChanged)
//		.OnRowReleased_UObject(this, &ThisClass::OnRowReleased);
//
//	return ListView.ToSharedRef();
//}
//
//TSharedRef<ITableRow> UUMGPListView::OnGenerateRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable)
//{
//	//UUserWidget* Widget = ItemWidgets;
//
//	TSharedRef<ITableRow> GeneratedRow = GenerateRow(Widget, OwnerTable);
//
//	//if(!Widget->Implements<>)
//}

//

//
//void UUMGPListView::ReleaseSlateResources(bool bReleaseChildren)
//{
//	Super::ReleaseSlateResources(bReleaseChildren);
//
//	Clear();
//	ListView.Reset();
//	ItemWidgets.Reset(bReleaseChildren);
//}
//
//void UUMGPListView::BeginDestroy()
//{
//	Super::BeginDestroy();
//
//	if (ListView.IsValid())
//		ListView.Reset();
//
//	DataProvider.Reset();
//}