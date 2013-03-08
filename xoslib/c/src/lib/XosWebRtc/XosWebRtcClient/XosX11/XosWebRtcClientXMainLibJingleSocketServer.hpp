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
///   File: XosWebRtcClientXMainLibJingleSocketServer.hpp
///
/// Author: $author$
///   Date: 6/17/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTXMAINLIBJINGLESOCKETSERVER_HPP
#define _XOSWEBRTCCLIENTXMAINLIBJINGLESOCKETSERVER_HPP

#include "XosXMainLibJingleSocketServer.hpp"
#include "XosWebRtcClientBaseWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosXMainLibJingleSocketServer
XosWebRtcClientXMainLibJingleSocketServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientXMainLibJingleSocketServer
///
/// Author: $author$
///   Date: 6/17/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientXMainLibJingleSocketServer
: public XosWebRtcClientXMainLibJingleSocketServerExtend
{
public:
    typedef XosWebRtcClientXMainLibJingleSocketServerExtend Extends;

    XosWebRtcClientBaseWindow& m_peerWindow;

    XosWebRtcClientXMainLibJingleSocketServer
    (XosWebRtcClientBaseWindow& peerWindow, XosXMain& main)
    : Extends(main), m_peerWindow(peerWindow)
    {}
    virtual ~XosWebRtcClientXMainLibJingleSocketServer(){}

    virtual bool PeekQuitMessage(int& cms, bool& process_io) 
    {
        bool isTrue = false;
        int msg_id, id;
        void* data;

        if ((m_peerWindow.PeekUIMessage(msg_id, id, data)))
        switch(msg_id)
        {
        case XosWebRtcClientBaseWindow::UI_THREAD_QUIT:
            isTrue = true;
            break;
        default:
            m_peerWindow.OnUIMessage(msg_id, id, data);
        }

        if ((Extends::PeekQuitMessage(cms, process_io)))
            isTrue = true;

        return isTrue;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTXMAINLIBJINGLESOCKETSERVER_HPP 
