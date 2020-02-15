#include "pch.h"
#include "SpacialPartition.h"

std::unique_ptr<SpacialPartition> SpacialPartition::partitionInstance = nullptr;

SpacialPartition * SpacialPartition::GetInstance()
{
	if (partitionInstance.get() == nullptr) {
		partitionInstance.reset(new SpacialPartition);
	}
	return partitionInstance.get();
}

SpacialPartition::SpacialPartition()
{
}


SpacialPartition::~SpacialPartition()
{
}
