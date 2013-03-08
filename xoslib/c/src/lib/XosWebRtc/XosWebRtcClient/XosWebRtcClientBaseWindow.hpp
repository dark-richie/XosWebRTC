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
///   File: XosWebRtcClientBaseWindow.hpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTBASEWINDOW_HPP
#define _XOSWEBRTCCLIENTBASEWINDOW_HPP

#include "XosWebRtcClientUserInterfaceImplement.hpp"
#include "XosWebRtcClientUserInterface.hpp"
#include "XosWebRtcClientConductorInterface.hpp"
#include "XosWebRtcClientConductor.hpp"
#include "XosWebRtcClientConnection.hpp"
#include "XosWebRtcClientOptions.hpp"
#include "XosWebRtcClientConversationInterface.hpp"
#include "XosWebRtcClientConversationToken.hpp"
#include "XosWebRtcClientPeerList.hpp"
#include "XosWebRtcClientVideoRenderer.hpp"
#include "XosWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosWebRtcClientUIMessageQueue.hpp"
#include "XosWindow.hpp"
#include "XosString.hpp"
#include "XosExportBase.hpp"

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME "localhost"
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT 8888
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON false
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON false

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_USE_OPENGL_RENDERER true
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE false
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE true
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS true

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_MESSAGE_HEADER \
    "SEND_MESSAGE_TO_PEER:"

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BEFORE "Connect to Server \""
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_AFTER "\"..."
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BEFORE "Connect to Peer \""
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_AFTER "\"..."
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_BEFORE "Connected as Peer \""
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_AFTER "\""
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECTING "Connecting... "
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_NO_VIDEO_STREAMS "(no video streams either way)"
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_NO_INCOMMING_VIDEO_STREAM "(no incoming video stream)"

#define XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_CONNECT_TO_SERVER_NAME "ConnectToServer"
#define XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_LIST_PEERS_NAME "ListPeers"
#define XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_STREAMING_NAME "Streaming"

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED   0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN 128
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE  0

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE 128

#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECTING_RED 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECTING_GREEN 0
#define XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECTING_BLUE 0

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosWebRtcClientBaseWindowUIMessageThread;
class _EXPORT_CLASS XosWebRtcClientBaseWindowSocketServer;
class _EXPORT_CLASS XosWebRtcClientBaseWindowPeerImplement;
class _EXPORT_CLASS XosWebRtcClientBasePeerWindowImplement;
class _EXPORT_CLASS XosWebRtcClientWindowPeerImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientBaseWindowImplement
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientUserInterfaceImplement
XosWebRtcClientBaseWindowImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientBaseWindowExtend
///
///  Author: $author$
///    Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientOptions
XosWebRtcClientBaseWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientBaseWindow
: virtual public XosWebRtcClientBaseWindowImplement,
  public XosWebRtcClientBaseWindowExtend
{
friend class XosWebRtcClientBaseWindowPeerImplement;
public:
    typedef XosWebRtcClientBaseWindowImplement Implements;
    typedef XosWebRtcClientBaseWindowExtend Extends;

    typedef XosWebRtcClientBaseWindowUIMessageThread UIMessageThread;
    typedef XosWebRtcClientBaseWindowUIMessageThread* UIMessageThreadId;
    ///////////////////////////////////////////////////////////////////////
    ///    Enum: UIMessages
    ///
    ///  Author: $author$
    ///    Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    enum UIMessages 
    {
        UI_THREAD_CALLBACK = 1,
        UI_CONNECT_TO_SERVER,
        UI_DISCONNECT_SERVER,
        UI_CONNECT_TO_PEER,
        UI_DISCONNECT_PEER,
        UI_LBUTTON_UP,
        UI_RBUTTON_UP,
        UI_INVALIDATE_WINDOW,
        UI_VALIDATE_WINDOW,
        UI_THREAD_QUIT
    };

protected:
    ///////////////////////////////////////////////////////////////////////
    ///  Class: AutoLock
    ///
    /// Author: $author$
    ///   Date: 4/2/2012
    //
    /// A little helper class to make sure we always to proper locking and
    /// unlocking when working with VideoRenderer buffers.
    ///////////////////////////////////////////////////////////////////////
    template <typename T>
    class AutoLock 
    {
     public:
        explicit AutoLock(T* obj) : obj_(obj) { obj_->Lock(); }
        ~AutoLock() { obj_->Unlock(); }
     protected:
          T* obj_;
    };

    bool m_showConnectionState;
    bool m_handleButtonEvents;
    bool m_postButtonEventUIMessages;
    bool m_postInvalidateWindowUIMessages;
    std::string m_peerMessageHeader;
    std::string m_serverName;
    int m_serverPort;
    std::string m_peerName;
    int m_peerId;
    std::string m_connectToPeerName;
    int m_connectToPeerId;
    bool m_autoConnectToPeer;
    bool m_autoConnectToPeerOn;
    bool m_autoConnectToPeerAfter;
    bool m_autoConnectToPeerAfterOn;
    bool m_useOpenGLRendererOff;
    bool m_useOpenGLRenderer;
    XosWebRtcClientPeerList m_peerList;
    bool m_useCallbackInAPI;
    bool m_useUIMessageQueue;

    talk_base::scoped_ptr<XosWebRtcClientVideoRenderer> remote_video_;
    talk_base::scoped_ptr<XosWebRtcClientVideoRenderer> local_video_;
    UI ui_;
    UIMessageThreadId ui_thread_id_;
    XosWebRtcClientUIMessageQueue ui_message_queue_;
    XosWebRtcClientConductorInterface* callback_;
    XosWebRtcClientOpenGLVideoRenderer* renderer_;
    XosWebRtcClientConversationToken token_;

    std::string m_connectToServerStateName;
    std::string m_listPeersStateName;
    std::string m_streamingStateName;

    std::string m_ConnectToServerBefore;
    std::string m_ConnectToServerAfter;
    std::string m_ConnectToPeerBefore;
    std::string m_ConnectToPeerAfter;
    std::string m_PeerBefore;
    std::string m_PeerAfter;
    std::string m_Connecting;
    std::string m_NoVideoStreams;
    std::string m_NoIncomingVideoStream;

    XosWebRtcClientBaseWindowPeerImplement* m_attachedWindowPeer;

public:
    XosWebRtcClientBaseWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_HANDLE_BUTTON_EVENTS);
    virtual ~XosWebRtcClientBaseWindow();

    virtual void RegisterObserver
    (XosWebRtcClientConductorInterface* callback) 
    { Delegate((XosWebRtcClientAudioVideoOptionsInterface*)(callback_ = callback)); 
      DelegatePortServerOptions((XosWebRtcClientPortServerOptionsInterface*)(callback_)); }
    virtual void UnRegisterObserver() 
    { DelegatePortServerOptions((XosWebRtcClientPortServerOptionsInterface*)(0));
      Delegate((XosWebRtcClientAudioVideoOptionsInterface*)(callback_ = 0)); }

    virtual XosWebRtcClientOpenGLVideoRenderer*
    AcquireOpenGLRenderer() { return 0; }
    virtual bool ReleaseOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) { return false; }

    virtual bool ReshapeOpenGLRenderer
    (XosWebRtcClientOpenGLVideoRenderer* renderer) { return false; }

    virtual XosWebRtcClientVideoRenderer* AcquireVideoRenderer
    (size_t width, size_t height, bool isRemote=false) { return 0; }
    virtual bool ReleaseVideoRenderer
    (XosWebRtcClientVideoRenderer* renderer) { return false; }

    virtual bool UpdateWindow();
    virtual bool ValidateWindow() { return false; }
    virtual bool InvalidateWindow(bool eraseBackground = true) { return false; }
    virtual bool IsWindow() { return true; }
    virtual UI current_ui() { return ui_; }

    virtual cricket::VideoRenderer* local_renderer();
    virtual cricket::VideoRenderer* remote_renderer();

    virtual void SwitchToConnectUI();
    virtual void SwitchToPeerList(const Peers& peers);
    virtual void SwitchToStreamingUI();

    virtual void MessageBox
    (const char* caption, const char* text, bool is_error);

    virtual void QueueUIThreadCallback(int msg_id, void* data);
    virtual const std::string GetThisPeerName();
    virtual void SetThisPeerName(const std::string& name);

    virtual bool SendMessageToPeer(const std::string& message);
    virtual bool OnReceiveMessageFromPeer(int peer_id, const std::string& message);
    virtual bool OnMessageFromPeer(int peer_id, const std::string& messageEnvelope);
    virtual void OnFailedToConnectToServer(const std::string& server);

    virtual void OnChangeStateToConnectToServer();
    virtual void OnChangeStateToListPeers();
    virtual void OnChangeStateToStreaming();
    virtual void OnChangeState(const std::string& toState);
    virtual void OnChangeUI(UI uiFrom, UI uiTo){}

protected:
    virtual void OnOpen();
    virtual void OnClose();
    virtual void OnSize();
    virtual void OnPaint();
 
    virtual bool OnPaintImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height);
    virtual bool OnPaintImage
    (const uint8* image, int width, int height, bool is_local);
    virtual bool OnPaintBlank();

    virtual bool OnRenderImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height, 
     bool is_local = false) { return false; }

    virtual void OnDefaultAction
    (int msg_id, int id, void* data);

    virtual bool InitUIMessageQueue();
    virtual bool FinishUIMessageQueue();

    virtual bool InitUIMessageThread();
    virtual bool FinishUIMessageThread();

    virtual bool CreateUIMessageThread();
    virtual bool DestroyUIMessageThread();

    virtual void PostUIThreadMessage
    (UIMessageThreadId tid, int msg_id, int id, void* data);
    virtual UIMessageThreadId GetUIMessageThreadId();

    virtual bool PostUIQueueMessage
    (XosWebRtcClientUIMessageQueue& msg_q, int msg_id, int id, void* data);

    virtual bool GetUIQueueMessage
    (XosWebRtcClientUIMessageQueue& msg_q, int& msg_id, int& id, void*& data);

    virtual bool PeekUIQueueMessage
    (XosWebRtcClientUIMessageQueue& msg_q, 
     int& msg_id, int& id, void*& data, bool dontRemove=false);

    virtual void OnLButtonUp()
    {
        XOS_DBI(("() ...\n"));
        if ((m_postButtonEventUIMessages)) {
            XOS_DBI(("() PostUIMessage()...\n"));
            PostUIMessage(UI_LBUTTON_UP, 0,0);
        }
        else
        OnUIMessage(UI_LBUTTON_UP, 0,0);
    }
    virtual void OnRButtonUp()
    {
        XOS_DBI(("() ...\n"));
        if ((m_postButtonEventUIMessages)) {
            XOS_DBI(("() PostUIMessage()...\n"));
            PostUIMessage(UI_RBUTTON_UP, 0,0);
        }
        else
        OnUIMessage(UI_RBUTTON_UP, 0,0);
    }

public:
    virtual void OnInvalidateWindow(bool eraseBackground = true)
    {
        if ((m_postInvalidateWindowUIMessages))
            PostUIMessage(UI_INVALIDATE_WINDOW, eraseBackground,0);
        else
        InvalidateWindow(eraseBackground);
    }
    virtual void OnValidateWindow()
    {
        if ((m_postInvalidateWindowUIMessages))
            PostUIMessage(UI_VALIDATE_WINDOW, 0,0);
        else
        ValidateWindow();
    }

    virtual bool PostUIMessage
    (int msg_id, int id, void* data)
    { 
        if ((m_useUIMessageQueue)) 
            return PostUIQueueMessage(ui_message_queue_, msg_id, id, data);

        PostUIThreadMessage(ui_thread_id_, msg_id, id, data); 
        return true;
    }
    virtual bool GetUIMessage
    (int& msg_id, int& id, void*& data)
    { 
        if ((m_useUIMessageQueue)) 
            return GetUIQueueMessage(ui_message_queue_, msg_id, id, data);
        return false; 
    }
    virtual bool PeekUIMessage
    (int& msg_id, int& id, void*& data, bool dontRemove=false)
    { 
        if ((m_useUIMessageQueue)) 
            return PeekUIQueueMessage
            (ui_message_queue_, msg_id, id, data, dontRemove);
        return false; 
    }
    virtual bool OnUIMessage
    (int msg_id, int id, void* data)
    { 
        OnDefaultAction(msg_id, id, data);
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer
    (const std::string& serverName, int serverPort)
    {
        std::string portSeparator = ":";
        std::string hostName = serverName;
        int hostPort = serverPort;
        size_t portPos;

        if ((portPos = serverName.find_last_of(portSeparator))
            != (serverName.npos))
        {
            std::string hostPortString(serverName.c_str()+portPos+portSeparator.length());
            std::stringstream hostPortStream(hostPortString);
            hostName.assign(serverName.c_str(), portPos);
            hostPortStream >> hostPort;
        }

        if ((0 < (hostName.length())))
            m_serverName = hostName;

        if ((0 < (hostPort)))
            m_serverPort = hostPort;

        return ConnectToServer();
    }
    virtual bool ConnectToServer()
    {
        m_autoConnectToPeer = m_autoConnectToPeerOn;
        m_autoConnectToPeerAfter = m_autoConnectToPeerAfterOn;

        SwitchToConnectUI();
        if (!(m_useCallbackInAPI) || !(callback_))
            PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_SERVER, 0,0);
        else
        callback_->StartLogin(m_serverName, m_serverPort);
        return true;
    }
    virtual bool DisconnectFromServer()
    { 
        SwitchToConnectUI(); 
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName)
    {
        if (0 >= (peerName.length()))
            return ConnectToPeer();

        if ((LIST_PEERS == (ui_)) && (0 > m_peerId))
        {
            XosWebRtcClientPeerList::const_iterator i;
            for (i = m_peerList.begin(); i != m_peerList.end(); i++)
            {
                XosWebRtcClientPeerItem peerItem(*i);
                if ((peerItem.m_name != peerName))
                    continue;

                m_connectToPeerName = peerItem.m_name;
                return ConnectToPeer(peerItem.m_id);
            }
        }
        return false;
    }
    virtual bool ConnectToPeer(int peerId)
    {
        if (0 > (peerId))
            return ConnectToPeer();

        if ((LIST_PEERS == (ui_)) && (0 > m_peerId))
        {
            m_connectToPeerId = peerId;
            return ConnectToPeer();
        }
        return false;
    }
    virtual bool ConnectToPeer()
    { 
        if ((LIST_PEERS == (ui_)) && (0 <= (m_connectToPeerId)) && (0 > m_peerId))
        {
            if (!(m_useCallbackInAPI) || !(callback_))
                PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_PEER, 0,0);
            else
            {
                m_peerName = m_connectToPeerName;
                m_peerId = m_connectToPeerId;
                callback_->ConnectToPeer(m_peerId);
            }
            return true;
        }
        return false; 
    }
    virtual bool DisconnectFromPeer()
    { 
        if (STREAMING == (ui_))
        {
            m_autoConnectToPeer = false;
            if (!(m_useCallbackInAPI) || !(callback_))
                PostUIThreadMessage(ui_thread_id_, UI_DISCONNECT_PEER, 0,0);
            else
            callback_->DisconnectFromCurrentPeer();
            return true;
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    // server
    ///////////////////////////////////////////////////////////////////////
    virtual void SetServerName(const std::string& toName)
    { m_serverName = toName; }
    virtual void SetServerName(const char* toChars)
    { m_serverName = toChars; }
    virtual const char* GetServerName() const
    { const char* val=m_serverName.c_str(); return val; }
    virtual void SetServerPort(int serverPort)
    { m_serverPort = serverPort; }
    virtual int GetServerPort() const
    { int val = m_serverPort; return val; }

    ///////////////////////////////////////////////////////////////////////
    // options
    ///////////////////////////////////////////////////////////////////////
    virtual void SetAutoConnectToPeerOn(bool isTrue=true)
    { m_autoConnectToPeerOn = isTrue; }
    virtual bool GetAutoConnectToPeerOn() const
    { bool val=m_autoConnectToPeerOn; return val; }

    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true)
    { m_autoConnectToPeerAfterOn = isTrue; }
    virtual bool GetAutoConnectToPeerAfterOn() const
    { bool val=m_autoConnectToPeerAfterOn; return val; }

    virtual void SetUseOpenGLRendererOn(bool isTrue=true)
    { m_useOpenGLRendererOff = !isTrue; }
    virtual bool GetUseOpenGLRendererOn() const
    { bool val=!m_useOpenGLRendererOff; return val; }

    virtual void UseOpenGLRenderer()
    { 
        SetUseOpenGLRendererOn(); 
        if ((renderer_))
            renderer_->use();
    }
    virtual void DontUseOpenGLRenderer()
    { 
        SetUseOpenGLRendererOn(false); 
        if ((renderer_))
            renderer_->dontUse();
    }

    ///////////////////////////////////////////////////////////////////////
    /// Function: GenerateWebRtcClientTraceFileName
    ///
    ///   Author: $author$
    ///     Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual std::string GenerateWebRtcClientTraceFileName
    (const std::string& p_webrtcClientTraceFileEnv,
     const std::string& p_webrtcClientTraceFileDir,
     const std::string& p_webrtcClientTraceFileName) const
    {
        std::string webrtcClientTraceFileDir(p_webrtcClientTraceFileDir);
        bool isAbsoluteDir = false;
        char dirSeparatorChar = '/';
        const char* separator = 0;
        const char* chars = 0;
        size_t length;

        if (0 < ( p_webrtcClientTraceFileEnv.length()))
        if ((chars =  p_webrtcClientTraceFileEnv.c_str()))
        if ((isAbsoluteDir = (chars = getenv(chars))))
        {
            webrtcClientTraceFileDir.assign(chars);
            if (0 < (p_webrtcClientTraceFileDir.length()))
            if (0 < (length = webrtcClientTraceFileDir.length()))
            if ((chars = webrtcClientTraceFileDir.c_str()))
            {
                if ('/' != (chars[length-1]))
                if ('\\' != (chars[length-1]))
                    webrtcClientTraceFileDir.append(&dirSeparatorChar, 1);
                webrtcClientTraceFileDir.append(p_webrtcClientTraceFileDir);
            }
        }
        return GenerateWebRtcClientTraceFileName
        (webrtcClientTraceFileDir, p_webrtcClientTraceFileName, isAbsoluteDir);
    }
    ///////////////////////////////////////////////////////////////////////
    /// Function: GenerateWebRtcClientTraceFileName
    ///
    ///   Author: $author$
    ///     Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual std::string GenerateWebRtcClientTraceFileName
    (const std::string& p_webrtcClientTraceFileDir,
     const std::string& p_webrtcClientTraceFileName,
     bool isAbsoluteDir=false) const
    {
        std::string webrtcClientTraceFileName(p_webrtcClientTraceFileName);
        char dirSeparatorChar = 0;
        const char* separator = 0;
        const char* chars = 0;
        size_t length;

        if (0 < (length = p_webrtcClientTraceFileDir.length()))
        if ((chars = p_webrtcClientTraceFileDir.c_str()))
        if ('/' != (chars[length-1]))
        if ('\\' != (chars[length-1]))
            dirSeparatorChar = '/';
 
        if ((isAbsoluteDir))
        {
            if (0 < (p_webrtcClientTraceFileDir.length()))
            {
                webrtcClientTraceFileName.assign(p_webrtcClientTraceFileDir);
                if ((dirSeparatorChar))
                    webrtcClientTraceFileName.append(&dirSeparatorChar, 1);
                webrtcClientTraceFileName.append(p_webrtcClientTraceFileName);
            }
        }
        else
        {
            //
            // Make path relative to module file name
            //
            std::string webrtcClientTraceModuleFileName(GetThisModuleFileName());

            if ((chars = webrtcClientTraceModuleFileName.c_str()))
            {
                if (!(separator = strrchr(chars, '/')))
                    separator = strrchr(chars, '\\');
            }
            if ((separator))
            {
                webrtcClientTraceFileName.assign(chars, (separator-chars+1));
                if (0 < (p_webrtcClientTraceFileDir.length()))
                {
                    webrtcClientTraceFileName.append(p_webrtcClientTraceFileDir);
                    if ((dirSeparatorChar))
                        webrtcClientTraceFileName.append(separator, 1);
                }
                webrtcClientTraceFileName.append(p_webrtcClientTraceFileName);
            }
        }
        return webrtcClientTraceFileName;
    }
    ///////////////////////////////////////////////////////////////////////
    /// Function: GetThisModuleFileName
    ///
    ///   Author: $author$
    ///     Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual std::string GetThisModuleFileName() const
    {
        XosString moduleFileName;
        return moduleFileName;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: AttachWindowPeer
    ///
    ///    Author: $author$
    ///      Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientBaseWindowPeerImplement* AttachWindowPeer
    (XosWebRtcClientBaseWindowPeerImplement* detached)
    {
        XosWebRtcClientBaseWindowPeerImplement* attached = 0;
        attached = (m_attachedWindowPeer = detached);
        return attached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: DetachWindowPeer
    ///
    ///    Author: $author$
    ///      Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientBaseWindowPeerImplement* DetachWindowPeer()
    {
        XosWebRtcClientBaseWindowPeerImplement* detached = 0;
        detached = (m_attachedWindowPeer);
        m_attachedWindowPeer = 0;
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: AttachedWindowPeer
    ///
    ///    Author: $author$
    ///      Date: 4/2/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientBaseWindowPeerImplement* AttachedWindowPeer() const
    {
        XosWebRtcClientBaseWindowPeerImplement* attached = 0;
        attached = (m_attachedWindowPeer);
        return attached;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTBASEWINDOW_HPP 
