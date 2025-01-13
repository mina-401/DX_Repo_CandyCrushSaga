#pragma once

template<typename T>
class Queue
{
public:
	// constrcuter destructer
	Queue()
	{
		Size = 0;
		Arr =new T[200];
		FrontIdx = 100;
		RearIdx = 100;
	}
	~Queue()
	{
		delete[] Arr;
	}

	// delete Function
	Queue(const Queue& _Other) = delete;
	Queue(Queue&& _Other) noexcept = delete;
	Queue& operator=(const Queue& _Other) = delete;
	Queue& operator=(Queue&& _Other) noexcept = delete;

	void Push(T _data)
	{
		Arr[RearIdx] = _data;
		RearIdx++;
		Size++;
	}

	void Pop()
	{
		if (Size != 0)
		{
			Arr[FrontIdx] = 0;
			FrontIdx++;
			Size--;
		}
	}

	T Front()
	{
		return Arr[FrontIdx];
	}

	T Back()
	{
		return Arr[RearIdx];
	}

	bool Emtpy()
	{
		return Size == 0;
	}

	int GetSize()
	{
		return Size;
	}
protected:

private:
	T* Arr;
	int Size;
	int FrontIdx;
	int RearIdx;

};
