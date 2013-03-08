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
///   File: XosXWebRtcClientBaseWindow.hpp
///
/// Author: $author$
///   Date: 7/4/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXWEBRTCCLIENTBASEWINDOW_HPP
#define _XOSXWEBRTCCLIENTBASEWINDOW_HPP

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosXWebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosXWebRtcClientBaseWindowImplement
///
///  Author: $author$
///    Date: 7/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindowImplement
XosXWebRtcClientBaseWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosXWebRtcClientBaseWindowExtend
///
///  Author: $author$
///    Date: 7/4/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientBaseWindow
XosXWebRtcClientBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 7/4/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXWebRtcClientBaseWindow
: virtual public XosXWebRtcClientBaseWindowImplement,
  public XosXWebRtcClientBaseWindowExtend
{
public:
    typedef XosXWebRtcClientBaseWindowImplement Implements;
    typedef XosXWebRtcClientBaseWindowExtend Extends;

    unsigned m_debugLevels;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosXWebRtcClientBaseWindow
    ///
    ///       Author: $author$
    ///         Date: 7/4/2012
    ///////////////////////////////////////////////////////////////////////
    XosXWebRtcClientBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_debugLevels(XOS_GET_DEBUG_LEVELS())
    {
        m_useUIMessageQueue = true;
        m_postButtonEventUIMessages = true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosXWebRtcClientBaseWindow
    ///
    ///      Author: $author$
    ///        Date: 7/4/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosXWebRtcClientBaseWindow()
    {
    }

    //
    // State change
    //
    virtual void OnChangeStateToConnectToServer()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        Extends::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers()
    {
        XOS_SET_DEBUG_LEVELS(m_debugLevels);
        Extends::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming()
    {
        XOS_SET_DEBUG_LEVEL(XOS_DEBUG_LEVELS_NONE);
        Extends::OnChangeStateToStreaming();
    }

    //
    // Video renderer
    //
    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) 
    { 
        XosWebRtcClientVideoRenderer* renderer = 0;
        renderer = new XosXWebRtcClientVideoRenderer
        (*this, width, height, isRemote);
        return renderer; 
    }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) 
    { 
        if ((renderer))
        {
            delete renderer;
            return true;
        }
        return false; 
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSXWEBRTCCLIENTBASEWINDOW_HPP 
        

