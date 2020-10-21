#include "global.hpp"
#include <Event.hpp>

int main(int, char**) {
    HYT::EventQueue queue;
    HYT::EventDispatcher dispatcher;
    dispatcher.subscribe(HYT::EventType::DemoEvent, [&](HYT::Event & e)->bool{
        std::cout << "Demo Event handled" << std::endl;
        return true;
    });
    dispatcher.post(HYT::Event(HYT::EventType::DemoEvent), queue);
    while (!queue.isEmpty())
    {
        dispatcher.handle(queue.front());
        if(queue.front().isHandled){
            queue.pop();
        }
    }
    
}
