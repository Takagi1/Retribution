#pragma once
class SpacialPartition
{
public:
	SpacialPartition(const SpacialPartition&) = delete;
	SpacialPartition(SpacialPartition&&) = delete;
	SpacialPartition& operator =(const SpacialPartition&) = delete;
	SpacialPartition& operator =(SpacialPartition&&) = delete;

	static SpacialPartition* GetInstance();

private:
	SpacialPartition();
	~SpacialPartition();

	static std::unique_ptr<SpacialPartition> partitionInstance;
	friend std::default_delete<SpacialPartition>;
};

