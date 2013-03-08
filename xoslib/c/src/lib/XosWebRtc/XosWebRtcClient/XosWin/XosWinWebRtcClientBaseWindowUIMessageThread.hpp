///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: XosWinWebRtcClientBaseWindowUIMessageThread.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP
#define _XOSWINWEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosWebRtcClientSocketServer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowUIMessageThread
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowUIMessageThread
{
public:
    enum ThreadWindowMessages 
    {
        UI_MESSAGE_THREAD_UI_MESSAGE = (WM_APP+1),
        UI_MESSAGE_THREAD_UI_CALLBACK,
        UI_MESSAGE_THREAD_QUIT
    };

    ///////////////////////////////////////////////////////////////////////
    ///  Class: SocketServer
    ///
    /// Author: $author$
    ///   Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    class SocketServer
    : public XosWebRtcClientSocketServer
    {
    public:
        typedef XosWebRtcClientSocketServer Extends;

        SocketServer
        (XosWebRtcClientBaseWindow& peerWindow)
        : Extends(peerWindow)
        {
        }
        virtual bool Wait(int cms, bool process_io)
        {
            MSG msg;

            if ((PeekMessage(&msg, NULL, 0,0, TRUE)))
                OnWindowMessage(m_peerWindow, msg);

            return Extends::Wait(0, process_io);
        }
    };

    DWORD m_tid;
    HANDLE m_trd;
    XosWebRtcClientBaseWindow* m_uiWindow;

    XosWebRtcClientBaseWindowUIMessageThread()
    : m_tid(0), m_trd(0), m_uiWindow(0)
    {
    }
    virtual ~XosWebRtcClientBaseWindowUIMessageThread()
    {
        if ((m_trd))
        if ((m_uiWindow))
            Destroy();
        else
        DestroyMessageThread();
    }

    ///////////////////////////////////////////////////////////////////////
    // socket server message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (XosWebRtcClientBaseWindow* uiWindow)
    {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd))
        {
            m_uiWindow = uiWindow;
            if ((trd = CreateThread
                (NULL, 0, Thread, (LPVOID)(this), 0, &tid)))
            {
                m_trd = trd;
                m_tid = tid;
                isSuccess = true;
            }
            else
            m_uiWindow = 0;
        }
        return isSuccess;
    }
    virtual bool Destroy()
    {
        bool isSuccess = false;
        if ((m_trd) && (m_uiWindow))
        {
            m_uiWindow->PostUIMessage
            (XosWebRtcClientBaseWindow::UI_THREAD_QUIT, 0,0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    virtual void Run()
    {
        talk_base::Thread* thread;

        if ((m_uiWindow))
        if ((thread = talk_base::ThreadManager::WrapCurrentThread()))
        {
            talk_base::Thread* oldThread;

            if (thread != (oldThread = talk_base::ThreadManager::CurrentThread()))
                talk_base::ThreadManager::SetCurrent(thread);

            if ((talk_base::ThreadManager::CurrentThread()))
            {
                SocketServer socketServer(*m_uiWindow);
                socketServer.Run();
            }

            if (thread != oldThread)
            {
                talk_base::ThreadManager::SetCurrent(oldThread);
                talk_base::ThreadManager::UnwrapCurrentThread();
            }
        }
    }
    static DWORD WINAPI Thread(LPVOID lpParameter)
    {
        DWORD result = 1;
        XosWebRtcClientBaseWindowUIMessageThread* thread;

        if ((thread = (XosWebRtcClientBaseWindowUIMessageThread*)(lpParameter)))
            thread->Run();
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    // uiWindow message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMessageThread
    (XosWebRtcClientBaseWindow* uiWindow)
    {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd))
        if ((trd = CreateThread
            (NULL, 0, MessageThreadUIWindow, (LPVOID)(uiWindow), 0, &tid)))
        {
            m_trd = trd;
            m_tid = tid;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    static DWORD WINAPI MessageThreadUIWindow(LPVOID lpParameter)
    {
        DWORD result = 1;
        XosWebRtcClientBaseWindow* uiWindow;
        bool isQuitMessage;
        MSG msg;

        if ((uiWindow = (XosWebRtcClientBaseWindow*)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(*uiWindow, msg)))
                return result;
        }
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    // hWnd message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMessageThread(HWND hWnd)
    {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd))
        if ((trd = CreateThread
            (NULL, 0, MessageThreadHwnd, (LPVOID)(hWnd), 0, &tid)))
        {
            m_trd = trd;
            m_tid = tid;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    static DWORD WINAPI MessageThreadHwnd(LPVOID lpParameter)
    {
        DWORD result = 1;
        bool isQuitMessage;
        HWND hWnd;
        MSG msg;

        if ((hWnd = (HWND)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(hWnd, msg)))
                return result;
        }
        return result;
    }
    virtual bool DestroyMessageThread()
    {
        bool isSuccess = false;
        if ((m_trd) && (!m_uiWindow))
        {
            ::PostThreadMessage(m_tid, UI_MESSAGE_THREAD_QUIT, 0, 0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // post messages
    ///////////////////////////////////////////////////////////////////////
    virtual bool PostUIThreadMessage
    (int msg_id, int id, void* data) 
    {
        return (FALSE != (PostThreadMessage
        (UI_MESSAGE_THREAD_UI_MESSAGE, 
         MAKEWPARAM(msg_id, id), (LPARAM)(data))));
    }
    virtual BOOL PostThreadMessage
    (UINT msg, WPARAM wParam, LPARAM lParam)
    {
        DWORD tid = GetCurrentThreadId();
        return ::PostThreadMessage(tid, msg, wParam, lParam);
    }

    ///////////////////////////////////////////////////////////////////////
    // message thread id
    ///////////////////////////////////////////////////////////////////////
    virtual DWORD SetCurrentThreadId(DWORD tid)
    {
        m_tid = tid;
        return m_tid;
    }
    virtual DWORD GetCurrentThreadId() const
    {
        if (!(m_tid))
            return ::GetCurrentThreadId();
        return m_tid;
    }

    ///////////////////////////////////////////////////////////////////////
    // on window msg for uiWindow
    ///////////////////////////////////////////////////////////////////////
    static bool OnWindowMessage
    (XosWebRtcClientBaseWindow& uiWindow, MSG& msg)
    {
        bool isQuitMessage = false;
        if ((msg.hwnd))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        switch(msg.message)
        {
        case UI_MESSAGE_THREAD_UI_MESSAGE:
            if ((isQuitMessage = ((int)(LOWORD(msg.wParam))
                == XosWebRtcClientBaseWindow::UI_THREAD_QUIT)))
                break;
            uiWindow.PostUIMessage
            ((int)(LOWORD(msg.wParam)), 
             (int)(HIWORD(msg.wParam)), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_UI_CALLBACK:
            uiWindow.PostUIMessage
            (XosWebRtcClientBaseWindow::UI_THREAD_CALLBACK, 
             (int)(msg.wParam), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_QUIT:
        case WM_NULL:
            isQuitMessage = true;
        }
        return isQuitMessage;
    }
    ///////////////////////////////////////////////////////////////////////
    // on window msg for hWnd
    ///////////////////////////////////////////////////////////////////////
    static bool OnWindowMessage
    (HWND hWnd, MSG& msg)
    {
        bool isQuitMessage = false;
        if ((msg.hwnd))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        switch(msg.message)
        {
        case UI_MESSAGE_THREAD_UI_MESSAGE:
            if ((isQuitMessage = ((int)(LOWORD(msg.wParam))
                == XosWebRtcClientBaseWindow::UI_THREAD_QUIT)))
                break;
            PostMessage(hWnd, msg.message, msg.wParam, msg.lParam);
            break;

        case UI_MESSAGE_THREAD_UI_CALLBACK:
            PostMessage(hWnd, msg.message, msg.wParam, msg.lParam);
            break;

        case UI_MESSAGE_THREAD_QUIT:
        case WM_NULL:
            isQuitMessage = true;
        }
        return isQuitMessage;
    }
};

typedef XosWebRtcClientBaseWindowUIMessageThread::SocketServer 
XosWebRtcClientBaseWindowSocketServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowSocketServer
///
/// Author: $author$
///   Date: 1/27/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowSocketServer
: public XosWebRtcClientBaseWindowSocketServerExtend
{
public:
    typedef XosWebRtcClientBaseWindowSocketServerExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientBaseWindowSocketServer
    ///
    ///       Author: $author$
    ///         Date: 1/27/2013
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientBaseWindowSocketServer
    (XosWebRtcClientBaseWindow& peerWindow)
    : Extends(peerWindow)
    {
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP 
