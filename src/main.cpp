#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void GetScreenPixels(vector<vector<COLORREF>>& pixels) {
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);
    
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    
    pixels.resize(height, vector<COLORREF>(width));
    GetBitmapBits(hBitmap, width * height * 4, &pixels[0][0]);
    
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
}

bool IsGreenColor(COLORREF color) {
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
        return (r >= 100 && r <= 130 && g >= 200 && g <= 250 && b >= 0 && b <= 30);
}

void SimulateKeyPress(char key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.mi.dwFlags = 0;
    input.ki.wVk = key; 

    SendInput(1, &input, sizeof(INPUT));
    
    input.mi.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

bool IsF7Pressed() {
    return GetAsyncKeyState(VK_F7) & 0x8000;
}

int main() {
    bool running = false;

    while (true) {
        if (IsF7Pressed()) {
            running = !running; 
            Sleep(500); 
        }

        if (running) {
            vector<vector<COLORREF>> screenPixels;
            GetScreenPixels(screenPixels);

            const int redX = 959; 
            const int redY = 494; 

            bool greenLeft = false;
            bool greenRight = false;

            if (redX - 1 >= 0) {
                COLORREF leftColor = screenPixels[redY][redX - 1];
                greenLeft = IsGreenColor(leftColor);
            }

            if (redX + 1 < screenPixels[0].size()) {
                COLORREF rightColor = screenPixels[redY][redX + 1];
                greenRight = IsGreenColor(rightColor);
            }

            if (greenLeft && greenRight) {
                cout << "Зеленый цвет найден" << endl;
                SimulateKeyPress(0x45); 
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
