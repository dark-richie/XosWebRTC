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
///   File: XosX11WebRtcClientSocketServer.hpp
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSX11WEBRTCCLIENTSOCKETSERVER_HPP
#define _XOSX11WEBRTCCLIENTSOCKETSERVER_HPP

#include "XosWebRtcClientSocketServer.hpp"
#include "XosPlatform_gtk_gtk.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

#undef CDB_CLASS
#define CDB_CLASS "XosX11WebRtcClientSocketServerT"
///////////////////////////////////////////////////////////////////////
///  Class: XosX11WebRtcClientSocketServerT
///
/// Author: $author$
///   Date: 4/20/2012
///////////////////////////////////////////////////////////////////////
template <class TExtend>
class _EXPORT_CLASS XosX11WebRtcClientSocketServerT
: public TExtend
{
public:
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosX11WebRtcClientSocketServerT
    ///
    ///       Author: $author$
    ///         Date: 4/20/2012
    ///////////////////////////////////////////////////////////////////////
    XosX11WebRtcClientSocketServerT
    (XosWebRtcClientBaseWindow& peerWindow)
    : Extends(peerWindow)
    {
    }
    virtual ~XosX11WebRtcClientSocketServerT()
    {
    }

    /*virtual bool Wait(int cms, bool process_io) 
    {
        //gdk_threads_enter();

        //while(gtk_events_pending())
        //    gtk_main_iteration();

        //gdk_threads_leave();

        return Extends::Wait(0, process_io);
    }*/
};
#undef CDB_CLASS

typedef XosWebRtcClientSocketServer
XosX11WebRtcClientSocketServerExtend;

typedef XosX11WebRtcClientSocketServerT
<XosX11WebRtcClientSocketServerExtend>
XosX11WebRtcClientSocketServer;

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSX11WEBRTCCLIENTSOCKETSERVER_HPP 
