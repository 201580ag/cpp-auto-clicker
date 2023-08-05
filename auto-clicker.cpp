#include <iostream>
#include <Windows.h>

int CalculateClickDelay(int cps) {
    return static_cast<int>(1000000.0 / cps);
}

int main() {
    std::cout << "Auto-click program is starting." << std::endl;

    int cps;
    std::cout << "Enter your desired click speed (CPS): ";
    std::cin >> cps;

    int clickDelay = CalculateClickDelay(cps);

    std::cout << "Press F6 to start clicking." << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            std::cout << "Clicking has started. (Press F7 to stop)" << std::endl;

            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);

            LARGE_INTEGER startTime, currentTime;
            QueryPerformanceCounter(&startTime);
            currentTime = startTime;

            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

            while (!(GetAsyncKeyState(VK_F7) & 0x8000)) {
                QueryPerformanceCounter(&currentTime);
                auto elapsedTime = (currentTime.QuadPart - startTime.QuadPart) * 1000000.0 / frequency.QuadPart;

                if (elapsedTime >= clickDelay) {
                    // Perform left click
                    SendInput(1, &input, sizeof(INPUT));
                    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                    SendInput(1, &input, sizeof(INPUT));
                    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                    startTime = currentTime;
                }
            }
            std::cout << "Clicking is stopped." << std::endl;
        }
    }

    return 0;
}