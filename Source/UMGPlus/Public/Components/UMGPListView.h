#pragma once

#include "../UMGPStyle.h"

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "ObservableArray.h"
#include "SListView.h"
#include "SelectorInterface.h"

#include "UMGPListView.generated.h"

UCLASS()
class UMGPLUS_API UUMGPListView 
	: public UWidget
{
	GENERATED_BODY()
	
public:
	//UUMGPListView();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Style")
	UUMGPStyle* Style;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UUserWidget> ListItemClass;

	/*virtual int32 GetSelectedIndex_Imp() override;
	virtual UObject* GetSelectedItem() override;
	virtual bool GetSelectedItems(TArray<UObject *>& Items) override;
	virtual bool IsSelected(UObject* Item) override;*/

protected:
	//TSharedPtr<SListView<UObject*>> ListView;
	//TSharedPtr<TObservableArray<UObject*>> Context;
	//TArray<UUserWidget*> ItemWidgets;

	//virtual TSharedRef<SListView<UObject*>> RebuildListWidget();

private:
	//TSharedRef<ITableRow> OnGenerateRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable);
	//TWidgetFactory<UUserWidget*> ItemWidgets;

//	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
//	virtual void BeginDestroy() override;
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void Add(UObject* Item);
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void Empty();
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	bool Contains(UObject* Item);
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	int32 IndexOf(UObject* Item);
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void InsertItem(int32 Index, UObject* Item);
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void Move(int32 From, int32 To);
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void Remove(UObject* Item);
//
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	UObject* GetItemAt(int32 Index);
//
//
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	int32 GetNumItemsSelected() const;
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	UObject* GetSelectedItem() const;
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	bool GetSelectedItems(TArray<UObject*>& Items) const;
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	bool IsItemVisible(UObject* Item) const;
//
//	UFUNCTION(BlueprintCallable, Category = "ListView")
//	void ScrollIntoView(UObject* Item);
//	void ScrollIntoView(const UObject* Item);
//
//
//
//protected:
//	virtual TSharedRef<SWidget> RebuildWidget() override;
};