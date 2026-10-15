#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include <QAbstractNativeEventFilter>
#include <QPointer>

class QWindow;

class WindowsWindow : public QAbstractNativeEventFilter
{
public:
    explicit WindowsWindow(QWindow* window);

    bool nativeEventFilter(
        const QByteArray& eventType,
        void* message,
        qintptr* result
    ) override;

private:
    QPointer<QWindow> m_window;
};

#endif // WINDOWSWINDOW_H
