#include "global.hpp"
#include <Event.hpp>
#include "Log.hpp"

int main(int, char**) {
    HYT::Logger::init();
    LOG_INFO("Hello world");
    
}
