#pragma once

#include "CoreMinimal.h"

enum class EObservableArrayAction
{
	OAA_Add,
	OAA_Remove,
	OAA_Empty
};

DECLARE_MULTICAST_DELEGATE_FiveParams(FOnArrayChanged, EObservableArrayAction, TArray<UObject*>, int32, TArray<UObject*>, int32);

template<typename InElementType, typename InAllocator>
class TObservableArray
{
public:
	typedef InElementType ElementType;
	typedef InAllocator   Allocator;

	FOnArrayChanged OnArrayChanged;

	FORCEINLINE int32 Num() { return Items.Num(); }

	void Add(ElementType&& Item);
	void Add(const ElementType& Item);
	void Empty();

	template <typename ComparisonType>
	FORCEINLINE bool Contains(const ComparisonType& Item) const { return Items.Contains(Item); }

	FORCEINLINE int32 IndexOf(const ElementType& Item) { return Items.IndexOfByKey(Item); }

	void Insert(const ElementType& Item, int32 Index);

	void Remove(const ElementType& Item);

	void RemoveAt(int32 Index);

	template <typename OtherAllocator>
	TObservableArray& operator=(const TArray<ElementType, OtherAllocator>& Other)
	{
		Items = Other;
		return *this;
	}

	FORCEINLINE ElementType& operator[](int32 Index) { return Items[Index]; }

private:
	TArray<InElementType, InAllocator> Items;
};

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::Add(ElementType&& Item)
{
	int32 InsertedAt = Items.Add(Item);

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> NewItems = { Item };
		TArray<UObject*> OldItems;
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Add, NewItems, InsertedAt, OldItems, 0);
	}
}

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::Add(const ElementType& Item)
{
	int32 InsertedAt = Items.Add(Item);

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> NewItems = { Item };
		TArray<UObject*> OldItems;
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Add, NewItems, InsertedAt, OldItems, 0);
	}
}

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::Empty()
{
	Items.Empty();

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> Dummy;
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Empty, Dummy, 0, Dummy, 0);
	}
}

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::Insert(const ElementType& Item, int32 Index)
{
	int32 InsertedAt = Items.Insert(Item, Index);

	int32 InsertedAt = Items.Add(Item);

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> NewItems = { Item };
		TArray<UObject*> OldItems;
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Add, NewItems, InsertedAt, OldItems, 0);
	}
}

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::Remove(const ElementType& Item)
{
	int32 RemovedAt = Items.Remove(Item);

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> NewItems;
		TArray<UObject*> OldItems = { Item };
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Remove, NewItems, 0, OldItems, RemovedAt);
	}
}

template<typename InElementType, typename InAllocator>
void TObservableArray<InElementType, InAllocator>::RemoveAt(int32 Index)
{
	Items.RemoveAt(Index);

	if (OnArrayChanged.IsBound())
	{
		TArray<UObject*> NewItems;
		TArray<UObject*> OldItems = { Item };
		OnArrayChanged.Broadcast(EObservableArrayAction::OAA_Remove, NewItems, 0, OldItems, Index);
	}
}