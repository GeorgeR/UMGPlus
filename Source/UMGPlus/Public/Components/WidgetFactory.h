#include "Blueprint/UserWidget.h"
#include "STableRow.h"
#include "SObjectTableRow.h"
#include "STableViewBase.h"

template <class WidgetType, class = typename TEnableIf<TIsDerivedFrom<WidgetType, UUserWidget>::IsDerived, WidgetType>::Type>
class TWidgetFactory : public FGCObject
{
private:
	FORCEINLINE UGameInstance* AsGameInstance() const { return Cast<UGameInstance>(OuterGetter()); }
	FORCEINLINE UWorld* AsWorld() const { return Cast<UWorld>(OuterGetter()); }
public:
	typedef TFunctionRef<TSharedPtr<SObjectWidget>(UUserWidget*, TSharedRef<SWidget>)> ConstructMethodType;

	TWidgetFactory() = default;
	TWidgetFactory(TSubclassOf<WidgetType> InWidgetClass, TFunction<UObject*(void)>&& InOuterGetter)
	    : WidgetClass(InWidgetClass)
	    , OuterGetter(MoveTemp(InOuterGetter)) { }

	TWidgetFactory(TWidgetFactory&& Other)
	    : Active(MoveTemp(Other.Active))
	    , Inactive(MoveTemp(Other.Inactive))
	    , CachedSlateWidgets(MoveTemp(Other.CachedSlateWidgets))
	    , WidgetClass(Other.WidgetClass)
	    , OuterGetter(MoveTemp(Other.OuterGetter))
	{
		Other.Active.Empty();
		Other.Inactive.Empty();
		Other.WidgetClass = nullptr;
		Other.OuterGetter = nullptr;
	}

	TWidgetFactory& operator=(TWidgetFactory&& Other)
	{

		Active             = MoveTemp(Other.Active);
		Inactive           = MoveTemp(Other.Inactive);
		CachedSlateWidgets = MoveTemp(Other.CachedSlateWidgets);
		WidgetClass        = Other.WidgetClass;
		OuterGetter        = MoveTemp(Other.OuterGetter);

		Other.Active.Empty();
		Other.Inactive.Empty();
		Other.CachedSlateWidgets.Empty();
		Other.WidgetClass = nullptr;
		Other.OuterGetter = nullptr;

		return *this;
	}

	bool IsInitialized() const { return WidgetClass && OuterGetter != nullptr; }

	void GetAllActiveWidgets(TArray<WidgetType*>& ActiveWidgets) { Active.GenerateValueArray(ActiveWidgets); }

	void PreConstruct(int32 Num)
	{
		if (!OuterGetter)
			return;

		for (int32 i = 0; i < Num; ++i)
		{
			if (WidgetClass)
			{
				WidgetType* NewWidget = nullptr;
				if (UWorld* World = AsWorld())
					NewWidget = CreateWidget<WidgetType>(World, WidgetClass);
				else if (UGameInstance* GameIn = AsGameInstance())
					NewWidget = CreateWidget<WidgetType>(GameIn, WidgetClass);

				if (NewWidget)
					Inactive.Add(NewWidget);
			}
		}
	}

	/** Method to get a widget from this factory, can sometimes call CreateWidget */
	WidgetType* Acquire()
	{
		WidgetType* Result = Inactive.Num() > 0 ? Inactive.Pop() : nullptr;

		if (!Result && OuterGetter && WidgetClass)
		{
			if (UWorld* World = AsWorld())
				Result = CreateWidget<WidgetType>(World, WidgetClass);
			else if (UGameInstance* GameIn = AsGameInstance())
				Result = CreateWidget<WidgetType>(GameIn, WidgetClass);
			
			check(Result);
		}

		Active.Add(Result->GetFName(), Result);

		return Result;
	}

	/** Return a widget to the pool, allowing it to be reused in the future */
	void Release(WidgetType* Widget)
	{
		const int32 NumRemoved = Active.Remove(Widget->GetFName());
		if (NumRemoved > 0)
			Inactive.Push(Widget);
	}

	void Reset(const bool bReleaseSlate = false, const bool bMoveToInactive = false)
	{
		if (!bMoveToInactive)
		{
			Active.Empty();
			Inactive.Empty();
		}
		else
		{
			TArray<WidgetType*> Widgets;
			Active.GenerateValueArray(Widgets);
			Active.Empty();
			Inactive.Append(Widgets);
		}

		if (bReleaseSlate)
			CachedSlateWidgets.Reset();
	}

	void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects<FName, WidgetType*>(Active);
		Collector.AddReferencedObjects(Inactive);
	}

	template <class DerivedWidgetType = SObjectWidget,
	          class                   = typename TEnableIf<TIsDerivedFrom<DerivedWidgetType, SObjectWidget>::IsDerived, DerivedWidgetType>::Type>
	TSharedRef<DerivedWidgetType> TakeAndCacheWidget(WidgetType* Key, ConstructMethodType ConstructMethod)
	{
		TSharedPtr<SWidget>& Cache = CachedSlateWidgets.FindOrAdd(Key);
		if (!Cache.IsValid())
			Cache = Key->template TakeDerivedWidget<DerivedWidgetType>(ConstructMethod);

		return StaticCastSharedRef<DerivedWidgetType>(Cache.ToSharedRef());
	}

	/** Convenience function for SObjectTableRows takes and caches the widget, then creates the object row around it */
	template <class DerivedWidgetType = SObjectWidget,
	          class                   = typename TEnableIf<TIsDerivedFrom<DerivedWidgetType, ITableRow>::IsDerived, DerivedWidgetType>::Type>
	TSharedRef<ITableRow> TakeAndCacheRow(WidgetType* Key, const TSharedRef<STableViewBase>& DestinationTable)
	{
		TSharedPtr<SWidget>& Cache = CachedSlateWidgets.FindOrAdd(Key);
		if (!Cache.IsValid())
		{
			Cache = Key->template TakeDerivedWidget<DerivedWidgetType>(
			    [DestinationTable](UUserWidget* Widget, TSharedRef<SWidget> SafeContent) 
				{
				    return SNew(DerivedWidgetType, DestinationTable, Widget)
				        [ 
							SafeContent 
						];
				});
		}

		return StaticCastSharedRef<DerivedWidgetType>(Cache.ToSharedRef());
	}

private:
	TMap<FName, WidgetType*>               Active;
	TArray<WidgetType*>                    Inactive;
	TMap<WidgetType*, TSharedPtr<SWidget>> CachedSlateWidgets;
	TSubclassOf<WidgetType>                WidgetClass;
	TFunction<UObject*(void)>              OuterGetter;

	FORCEINLINE friend typename TMap<FName, WidgetType*>::TConstIterator begin(const TWidgetFactory& Factory) { return begin(Factory.Active); }
	FORCEINLINE friend typename TMap<FName, WidgetType*>::TIterator begin(TWidgetFactory& Factory) { return begin(Factory.Active); }
	FORCEINLINE friend typename TMap<FName, WidgetType*>::TConstIterator end(const TWidgetFactory& Factory) { return end(Factory.Active); }
	FORCEINLINE friend typename TMap<FName, WidgetType*>::TIterator end(TWidgetFactory& Factory) { return end(Factory.Active); }
};