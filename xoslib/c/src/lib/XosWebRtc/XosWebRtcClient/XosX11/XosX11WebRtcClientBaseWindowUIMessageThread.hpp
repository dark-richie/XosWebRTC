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
///   File: XosX11WebRtcClientBaseWindowUIMessageThread.hpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSX11WEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP
#define _XOSX11WEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosX11WebRtcClientBaseWindowSocketServer.hpp"
#include "XosPThread.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosPThreadImplement
XosWebRtcClientBaseWindowUIMessageThreadImplement;

typedef XosPThread
XosWebRtcClientBaseWindowUIMessageThreadExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindowUIMessageThread
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindowUIMessageThread
: virtual public XosWebRtcClientBaseWindowUIMessageThreadImplement,
  public XosWebRtcClientBaseWindowUIMessageThreadExtend
{
public:
    typedef XosWebRtcClientBaseWindowUIMessageThreadImplement Implements;
    typedef XosWebRtcClientBaseWindowUIMessageThreadExtend Extends;

    XosWebRtcClientBaseWindow* m_uiWindow;
    XosX11WebRtcClientBaseWindowSocketServer* m_socketServer;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientBaseWindowUIMessageThread
    ///
    ///       Author: $author$
    ///         Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientBaseWindowUIMessageThread()
    : m_uiWindow(0),
      m_socketServer(0)
    {
    }
    virtual ~XosWebRtcClientBaseWindowUIMessageThread()
    {
    }

    virtual bool CreateMessageThread
    (XosWebRtcClientBaseWindow* uiWindow,
     XosX11WebRtcClientBaseWindowSocketServer* socketServer = 0)
    {
        bool isSuccess = Create(uiWindow, socketServer);
        return isSuccess;
    }
    virtual bool DestroyMessageThread()
    {
        bool isSuccess = Destroy();
        return isSuccess;
    }

    virtual bool Create
    (XosWebRtcClientBaseWindow* uiWindow,
     XosX11WebRtcClientBaseWindowSocketServer* socketServer = 0)
    {
        bool isSuccess = false;
        m_uiWindow = uiWindow;
        m_socketServer = socketServer;
        if (!(isSuccess = Extends::Create()))
        {
            m_socketServer = 0;
            m_uiWindow = 0;
        }
        return isSuccess;
    }
    virtual bool Destroy()
    {
        bool isSuccess = false;
        if ((m_uiWindow))
        {
            m_uiWindow->PostUIMessage
            (XosWebRtcClientBaseWindow::UI_THREAD_QUIT, 0,0);
            isSuccess = Extends::Destroy();
            m_socketServer = 0;
            m_uiWindow = 0;
        }
        return isSuccess;
    }

    virtual void Run()
    {
        if ((m_uiWindow))
        {
            if ((m_socketServer))
            {
                talk_base::AutoThread autoThread;
                m_socketServer->SetThread(talk_base::ThreadManager::CurrentThread());
                m_socketServer->Run();
                m_socketServer->SetThread(0);
            }
            else
            {
                talk_base::AutoThread autoThread;
                XosX11WebRtcClientBaseWindowSocketServer socketServer(*m_uiWindow);
                socketServer.Run();
            }
            /*talk_base::Thread* thread;

            if ((thread = talk_base::ThreadManager::WrapCurrentThread()))
            {
                talk_base::Thread* oldThread;

                if (thread != (oldThread = talk_base::ThreadManager::CurrentThread()))
                    talk_base::ThreadManager::SetCurrent(thread);

                if ((talk_base::ThreadManager::CurrentThread()))
                {
                    XosX11WebRtcClientBaseWindowSocketServer socketServer(*m_uiWindow);
                    socketServer.Run();
                }

                if (thread != oldThread)
                {
                    talk_base::ThreadManager::SetCurrent(oldThread);
                    talk_base::ThreadManager::UnwrapCurrentThread();
                }
            }*/
            /*int msg_id;
            int msg;
            void* data;

            while ((m_uiWindow->GetUIMessage(msg_id, msg, data)))
            {
                if ((msg_id != XosWebRtcClientBaseWindow::UI_THREAD_QUIT))
                {
                    m_uiWindow->OnUIMessage(msg_id, msg, data);
                    continue;
                }
                break;
            }*/
        }
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSX11WEBRTCCLIENTBASEWINDOWUIMESSAGETHREAD_HPP 
