#include "Benchmark_App.h"
#include <chrono>
#include <iostream>
#include <vector>
#include "LinkedList.h"
Benchmark_App::Benchmark_App()
{
}
void Benchmark_App::Update(const float dt)
{
	Engine::DoublyLinkedList<int> linkedListIntegers{};
	std::vector<int> vectorOfIntegers{};

	std::chrono::high_resolution_clock::time_point t1{ std::chrono::high_resolution_clock::now() };
	for (int i{5}; i < 11; ++i)
	{
		linkedListIntegers.push_back(i);
	}
	std::chrono::high_resolution_clock::time_point t2{ std::chrono::high_resolution_clock::now() };
	float elapsedSeconds = std::chrono::duration<float>(t2 - t1).count();

}