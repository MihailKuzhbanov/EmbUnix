//////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
//////////////////////////////////////////////////////////////////////////////

# include <string>
# include <thread>

# include "../include/tport.hpp"

# define CHNUM 1000
using namespace tport;

void tport_writer(TPort<int>& tport) {
    std::vector<int> data(CHNUM);
    int i = 0;
    Exit_t res;
    while (1) {
        res=tport.write(data, 0);
        i++;
        for (auto j=0; j < CHNUM; j++) {
            data[j] = i;
        }
        if (res == EXIT_FAILURE) {
            std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
        }
        usleep(11);
    }
}

void tport_reader(TPort<int>& tport) {
    std::vector<int> data(CHNUM);
    while (1) {
        if (tport.read(data) == EXIT_SUCCESS) {
            std::cout << data[0] << std::endl;
        }
        usleep(9);
    }
}

int main(int argc, char** argv) {
    TPort<int> tport(CHNUM);
    std::thread t1(tport_writer, std::ref(tport));
    std::thread t2(tport_reader, std::ref(tport));
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}
