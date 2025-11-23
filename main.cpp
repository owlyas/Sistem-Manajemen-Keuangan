#include <iostream>
#include <iomanip>
#include "AppCLI.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    AppCLI app;
    app.run();

    return 0;
}
