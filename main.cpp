#include "system.h"
#include "visualizer.h"


int main(int argc, char **argv) {
    const real Distance = 6.f;
    System oSystem(50, Distance, 2, 0.01);
    Visualizer visualizer(argc, argv, oSystem);

    while (true) {
        usleep(1000 * 10);
        oSystem.simulate();
        visualizer.update();
    }
}
