#include "windowswindow.h"
#include <QWindow>
#include <windows.h>
#include <windowsx.h>

WindowsWindow::WindowsWindow(QWindow* window) : m_window(window) {}

bool WindowsWindow::nativeEventFilter(
    const QByteArray& eventType, // Typ eventu
    void* message, // Właściwości eventu
    qintptr* result) // Wskaźnik, przez który dajemy co system ma zrobić
{
    if (eventType != "windows_generic_MSG") // Sprawdza czy event jest a propos okna
        return false;

    if (!m_window || !message)
        return false;

    MSG* msg = static_cast<MSG*>(message); // Po upewnieniu się konwertuje z void na MSG (typ, z któreg kożysta windows)

    if (msg->message != WM_NCHITTEST) // Sprawdza czy event jest typu z którego chcemy skorzystać
        return false;

    HWND hwnd = reinterpret_cast<HWND>(m_window->winId()); // Pobiera info o które okno chodzi

    if (msg->hwnd != hwnd) // Sprawdza czy to nasze okno
        return false;

    if (m_window->visibility() != QWindow::Windowed) // if Window not windowed -> return
        return false;

    const QPoint globalPos( // Bierze globalne pozycje kursora (na monitorach)
        GET_X_LPARAM(msg->lParam),
        GET_Y_LPARAM(msg->lParam)
    );

    const QPoint pos = m_window->mapFromGlobal(globalPos); // Przekszałca to na pozycję w odniesieniu do okna

    constexpr int border = 8;

    const bool left   = pos.x() < border;
    const bool right  = pos.x() >= m_window->width() - border;
    const bool top    = pos.y() < border;
    const bool bottom = pos.y() >= m_window->height() - border;

    if (top && left)
        *result = HTTOPLEFT;
    else if (top && right)
        *result = HTTOPRIGHT;
    else if (bottom && left)
        *result = HTBOTTOMLEFT;
    else if (bottom && right)
        *result = HTBOTTOMRIGHT;
    else if (left)
        *result = HTLEFT;
    else if (right)
        *result = HTRIGHT;
    else if (top)
        *result = HTTOP;
    else if (bottom)
        *result = HTBOTTOM;
    else
        return false;

    return true;
}