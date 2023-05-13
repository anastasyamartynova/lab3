#include <Windows.h>
#include <cmath>
#include <cstring>
#include <string>
class Vector2D {
public:
    float x, y;

    // Конструкторы
    Vector2D() : x(0), y(0) {}
    Vector2D(float x_, float y_) : x(x_), y(y_) {}

    // Операторы сложения, вычитания и умножения на скаляр
    friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
        return Vector2D(v1.x + v2.x, v1.y + v2.y);
    }

    friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
        return Vector2D(v1.x - v2.x, v1.y - v2.y);
    }

    friend Vector2D operator*(const Vector2D& v, float scalar) {
        return Vector2D(v.x * scalar, v.y * scalar);
    }

    friend Vector2D operator*(float scalar, const Vector2D& v) {
        return v * scalar;
    }

    // Оператор присваивания
    Vector2D& operator=(const Vector2D& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    // Методы для вычисления длины и нормализации вектора
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D& normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
        return *this;
    }
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Задаем начальную точку для рисования окружностей
        Vector2D center(50, 50);

        // Рисуем 3x3 сетку окружностей с использованием сдвига вектора
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Vector2D offset(i * 100, j * 100);
                Vector2D circleCenter = center + offset;

                // Рисуем окружность с радиусом 40 пикселей и центром в circleCenter
                Ellipse(hdc, circleCenter.x - 40, circleCenter.y - 40, circleCenter.x + 40, circleCenter.y + 40);
            }
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Регистрируем класс окна
    const std::wstring CLASS_NAME = L"MyWindowClass";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME.c_str();

    RegisterClass(&wc);

    // Создаем окно
    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME.c_str(),
        L"My Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL) {
        return 0;
    }

    // Показываем окно
    ShowWindow(hWnd, nCmdShow);

    // Запускаем цикл сообщений
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}