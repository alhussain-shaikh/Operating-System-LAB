#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

std::mutex g_mutex;
bool g_ready = false;
int g_data = 0;

int produceData() {
    
    int randomNumber = rand() % 1000;
    std::cout << "produce data: " << randomNumber << "\n";
    return randomNumber;
    
 
}

void consumeData(int data) { 
    
    std::cout << "Consume data: " << data << "\n"; 
    
    
}

// consumer thread function
void consumer() {
    int cons=5;
  while (cons<=5) {
    while (!g_ready) {
      // sleep for 1 second
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    
    std::unique_lock<std::mutex> ul(g_mutex);
    consumeData(g_data);
    g_ready = false;
    cons--;
    if(cons==0){
            printf("\n The buffer is empty");
            break;
    }
  }
}

// producer thread function
void producer() {
    int prod=0;
  while (prod<5) {
    std::unique_lock<std::mutex> ul(g_mutex);

    g_data = produceData();
    g_ready = true;
    ul.unlock();
   
    while (g_ready) {
      // sleep for 1 second
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    if(prod==5){
            printf("\n The Buffer is full.\n");
        }
         prod++;
  }
}

void consumerThread() { consumer(); }

void producerThread() { producer(); }

int main() {
  std::thread t2(consumerThread);
  std::thread t1(producerThread);
  t1.join();
  t2.join();
  return 0;
}
