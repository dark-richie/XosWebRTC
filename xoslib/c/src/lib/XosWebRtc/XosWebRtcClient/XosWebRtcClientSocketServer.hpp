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
///   File: XosWebRtcClientSocketServer.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTSOCKETSERVER_HPP
#define _XOSWEBRTCCLIENTSOCKETSERVER_HPP

#include "XosWebRtcClientPlatformSocketServer.hpp"
#include "XosWebRtcClientBaseWindow.hpp"
#include "talk/base/thread.h"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

#undef CDB_CLASS
#define CDB_CLASS "XosWebRtcClientSocketServerT"
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientSocketServerT
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
template <class TExtend>
class _EXPORT_CLASS XosWebRtcClientSocketServerT
: public TExtend
{
public:
    typedef TExtend Extends;

    XosWebRtcClientBaseWindow& m_peerWindow;
    talk_base::Thread* m_thread;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientSocketServerT
    ///
    ///       Author: $author$
    ///         Date: 4/22/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientSocketServerT
    (XosWebRtcClientBaseWindow& peerWindow)
    : m_peerWindow(peerWindow),
      m_thread(0)
    {
        if ((CTHIS m_thread = talk_base::Thread::Current()))
            CTHIS m_thread->set_socketserver(this);
    }
    virtual ~XosWebRtcClientSocketServerT()
    {
        if ((CTHIS m_thread))
            CTHIS m_thread->set_socketserver(0);
    }

    virtual bool Run()
    {
        bool isSuccess = false;
        if ((isSuccess = (0 != (CTHIS m_thread))))
            CTHIS m_thread->Run();
        return isSuccess;
    }
    virtual bool Wait(int cms, bool process_io) 
    {
        int msg_id, id;
        void* data;

        if ((CTHIS m_peerWindow.PeekUIMessage(msg_id, id, data)))
        switch(msg_id)
        {
        case XosWebRtcClientBaseWindow::UI_THREAD_QUIT:
            if ((CTHIS m_thread))
                CTHIS m_thread->Quit();
            break;
        default:
            CTHIS m_peerWindow.OnUIMessage(msg_id, id, data);
        }
        return Extends::Wait(0, process_io);
    }

    virtual void SetThread(talk_base::Thread* thread)
    {
        if ((CTHIS m_thread))
            CTHIS m_thread->set_socketserver(0);

        if ((CTHIS m_thread = thread))
            CTHIS m_thread->set_socketserver(this);
    }
};
#undef CDB_CLASS

typedef talk_base::PlatformSocketServer
XosWebRtcClientSocketServerExtend;

typedef XosWebRtcClientSocketServerT
<XosWebRtcClientSocketServerExtend>
XosWebRtcClientSocketServer;

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTSOCKETSERVER_HPP 
