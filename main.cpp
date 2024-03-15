#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

class threadSafeQ {
	std::queue<int> rawQ;
	std::mutex m;
public:
	int retrieveAndDelete() {
		int front_value = 0;
		m.lock();
		if (!rawQ.empty()) {
			front_value = rawQ.front();
			rawQ.pop();
		}
		m.unlock();
		return front_value;
	}
	
	void push(int val1, int val2, int val3) {
		m.lock();
		rawQ.push(val1);
		rawQ.push(val2);
		rawQ.push(val3);
		m.unlock();
	}
	
	void Print() {
		m.lock();
		std::cout<< "Objects of queue: ";
		while (!rawQ.empty()) {
			std::cout << rawQ.front() << " ";
			rawQ.pop();
			std::cout<< std::endl;
		}
	
		m.unlock();
		
	}
};



int main()
{
	threadSafeQ q;
	
	std::thread PushThread(&threadSafeQ::push, &q, 1, 2, 3);

	
	std::thread PopThread(&threadSafeQ::retrieveAndDelete, &q);
	

	if (PushThread.joinable())
	{
		PushThread.join();
	}
	if (PopThread.joinable())
	{
		PopThread.join();
	}
	
	q.Print();
	
	return 0;
}
