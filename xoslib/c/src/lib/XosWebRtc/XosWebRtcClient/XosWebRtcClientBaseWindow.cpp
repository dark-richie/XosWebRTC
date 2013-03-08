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
///   File: XosWebRtcClientBaseWindow.cpp
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
#include <math.h>

#include "talk/base/common.h"
#include "talk/base/logging.h"
#include "talk/base/stringutils.h"

#include "XosWebRtcClientBaseWindow.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/2/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientBaseWindow::XosWebRtcClientBaseWindow
///
///       Author: $author$
///         Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientBaseWindow::XosWebRtcClientBaseWindow
(const char* serverName, int serverPort,
 bool showConnectionState, bool handleButtonEvents)
: m_showConnectionState(showConnectionState),
  m_handleButtonEvents(handleButtonEvents),
  m_postButtonEventUIMessages(false),
  m_postInvalidateWindowUIMessages(false),
  m_peerMessageHeader(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_MESSAGE_HEADER),
  m_serverName(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_NAME),
  m_serverPort(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_SERVER_PORT),
  m_peerName(""),
  m_peerId(-1),
  m_connectToPeerName(""),
  m_connectToPeerId(-1),

  m_autoConnectToPeer(false),
  m_autoConnectToPeerOn
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON),
  m_autoConnectToPeerAfter(false),
  m_autoConnectToPeerAfterOn
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON),

  m_useOpenGLRendererOff(false),
  m_useOpenGLRenderer(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_USE_OPENGL_RENDERER),
  m_useCallbackInAPI(false),
  m_useUIMessageQueue(XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE),

  ui_(CONNECT_TO_SERVER), 
  ui_thread_id_(0),
  callback_(0),
  renderer_(0),

  m_connectToServerStateName
  (XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_CONNECT_TO_SERVER_NAME),
  m_listPeersStateName
  (XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_LIST_PEERS_NAME),
  m_streamingStateName
  (XOSWEBRTCCLIENTUSERINTERFACE_DEFAULT_STATE_STREAMING_NAME),

  m_ConnectToServerBefore
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BEFORE),
  m_ConnectToServerAfter
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_AFTER),
  m_ConnectToPeerBefore
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BEFORE),
  m_ConnectToPeerAfter
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_AFTER),
  m_PeerBefore
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_BEFORE),
  m_PeerAfter
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_PEER_AFTER),
  m_Connecting
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECTING),
  m_NoVideoStreams
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_NO_VIDEO_STREAMS),
  m_NoIncomingVideoStream
  (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_NO_INCOMMING_VIDEO_STREAM),

  m_attachedWindowPeer(0)
{
    if ((serverName)) m_serverName = serverName;
    if (0 < (serverPort)) m_serverPort = serverPort;
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientBaseWindow::~XosWebRtcClientBaseWindow
///
///       Author: $author$
///         Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientBaseWindow::~XosWebRtcClientBaseWindow()
{
    XosWebRtcClientVideoRenderer* renderer;
    if ((renderer = remote_video_.release())) ReleaseVideoRenderer(renderer);
    if ((renderer = local_video_.release())) ReleaseVideoRenderer(renderer);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::UpdateWindow
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::UpdateWindow()
{
    bool isSuccess = true;
    if ((renderer_))
    if (!(renderer_->getDontUse()))
        isSuccess = renderer_->swapBuffers();
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::InitUIMessageQueue
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::InitUIMessageQueue()
{
    bool isSuccess = true;
    XOS_DBI(("() ...\n"));
    isSuccess = ui_message_queue_.Init();
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::FinishUIMessageQueue
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::FinishUIMessageQueue()
{
    bool isSuccess = true;
    XOS_DBI(("() ...\n"));
    isSuccess = ui_message_queue_.Finish();
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::InitUIMessageThread
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::InitUIMessageThread()
{
    bool isSuccess = true;
    XOS_DBI(("() ...\n"));
    if ((m_useUIMessageQueue))
        isSuccess = InitUIMessageQueue();
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::FinishUIMessageThread
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::FinishUIMessageThread()
{
    bool isSuccess = true;
    XOS_DBI(("() ...\n"));
    if ((m_useUIMessageQueue))
        isSuccess = FinishUIMessageQueue();
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::CreateUIMessageThread
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::CreateUIMessageThread()
{
    bool isSuccess = true;
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::DestroyUIMessageThread
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::DestroyUIMessageThread()
{
    bool isSuccess = true;
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::PostUIThreadMessage
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::PostUIThreadMessage
(UIMessageThreadId tid, int msg_id, int id, void* data)
{
    if ((m_useUIMessageQueue))
        PostUIQueueMessage(ui_message_queue_, msg_id, id, data);
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::GetUIMessageThreadId
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientBaseWindow::UIMessageThreadId 
XosWebRtcClientBaseWindow::GetUIMessageThreadId()
{
    UIMessageThreadId tid = 0;
    return tid;
}

bool XosWebRtcClientBaseWindow::PostUIQueueMessage
(XosWebRtcClientUIMessageQueue& msg_q, int msg_id, int id, void* data)
{ 
    return msg_q.PostUIMessage(msg_id, id, data);
}
bool XosWebRtcClientBaseWindow::GetUIQueueMessage
(XosWebRtcClientUIMessageQueue& msg_q, int& msg_id, int& id, void*& data)
{ 
    return msg_q.GetUIMessage(msg_id, id, data);
}
bool XosWebRtcClientBaseWindow::PeekUIQueueMessage
(XosWebRtcClientUIMessageQueue& msg_q, int& msg_id, int& id, void*& data, bool dontRemove)
{ 
    return msg_q.PeekUIMessage(msg_id, id, data, dontRemove);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
cricket::VideoRenderer* XosWebRtcClientBaseWindow::local_renderer() 
{
    XosWebRtcClientVideoRenderer* renderer;
    if (!(local_video_.get()))
    if ((renderer = AcquireVideoRenderer(1, 1, false)))
        local_video_.reset(renderer);
    return local_video_.get();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
cricket::VideoRenderer* XosWebRtcClientBaseWindow::remote_renderer() 
{
    XosWebRtcClientVideoRenderer* renderer;
    if (!(remote_video_.get()))
    if ((renderer = AcquireVideoRenderer(1, 1, true)))
        remote_video_.reset(renderer);
    return remote_video_.get();
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::SwitchToConnectUI() 
{
    switch(ui_)
    {
    case STREAMING:
        if ((callback_))
            callback_->DisconnectFromServer(true);
        break;

    case LIST_PEERS:
        if ((callback_))
            callback_->DisconnectFromServer(true);
        break;
    }

    m_connectToPeerId = -1;
    m_connectToPeerName = "";

    m_peerId = -1;
    m_peerName = "";

    UI ui = ui_;
    OnChangeUI(ui, ui_ = CONNECT_TO_SERVER);
    OnChangeStateToConnectToServer();
    InvalidateWindow();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::SwitchToPeerList(const Peers& peers) 
{
    XosWebRtcClientVideoRenderer* renderer;
    Peers::const_iterator i;
    std::string peerName;
    int peerId;

    if ((renderer = remote_video_.release())) ReleaseVideoRenderer(renderer);
    if ((renderer = local_video_.release())) ReleaseVideoRenderer(renderer);

    m_connectToPeerId = -1;
    m_connectToPeerName = "";

    m_peerId = -1;
    m_peerName = "";
    m_peerList.clear();

    for (i = peers.begin(); i != peers.end(); ++i)
    {
        peerName = i->second;
        peerId = i->first;

        if (0 < (peerName.length()))
        if (0 <= (peerId))
        {
            XosWebRtcClientPeerItem peerItem(peerName, peerId);
            m_peerList.push_back(peerItem);
        }
    }

    for (i = peers.begin(); i != peers.end(); ++i)
    {
        peerName = i->second;
        peerId = i->first;

        if ((token_.CheckIsValid(peerName)))
        {
            m_connectToPeerName = peerName;
            m_connectToPeerId = peerId;
            if ((m_autoConnectToPeer))
            {
                m_autoConnectToPeer = m_autoConnectToPeerAfter;
                m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
                if (!(m_useCallbackInAPI) || !(callback_))
                    PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_PEER, 0,0);
                else
                {
                    m_peerName = m_connectToPeerName;
                    m_peerId = m_connectToPeerId;
                    callback_->ConnectToPeer(m_peerId);
                }
            }
            break;
        }
    }

    UI ui = ui_;
    OnChangeUI(ui, ui_ = LIST_PEERS);
    OnChangeStateToListPeers();
    InvalidateWindow();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::SwitchToStreamingUI() 
{
    UI ui = ui_;
    OnChangeUI(ui, ui_ = STREAMING);
    OnChangeStateToStreaming();
    ReshapeOpenGLRenderer(renderer_);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::MessageBox
(const char* caption, const char* text, bool is_error) 
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::QueueUIThreadCallback(int msg_id, void* data) 
{
    XOS_DBT(("() in...\n"));
    PostUIThreadMessage
    (ui_thread_id_, UI_THREAD_CALLBACK, (msg_id), (data));
    XOS_DBT(("() ...out\n"));
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
const std::string XosWebRtcClientBaseWindow::GetThisPeerName()
{
    std::string name;
    token_.Make(name);
    return name;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::SetThisPeerName(const std::string& name)
{
    token_.SetPeerName(name.c_str());
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::
SendMessageToPeer(const std::string& message)
{
    bool handled = false;
    if ((callback_))
    {
        std::string messageEnvelope = m_peerMessageHeader;
        messageEnvelope += message;
        handled = callback_->SendMessageToPeer(messageEnvelope);
    }
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::
OnReceiveMessageFromPeer(int peer_id, const std::string& message)
{
    XOS_DBT(("()...\n"));
    bool handled = Implements::OnReceiveMessageFromPeer(peer_id, message);
    return handled;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::
OnMessageFromPeer(int peer_id, const std::string& messageEnvelope)
{
    bool handled = false;
    size_t messageHeaderCharsLength;
    const char* messageHeaderChars;
    const char* messageEnvelopeChars;
    const char* messageChars;

    XOS_DBT(("()...\n"));
    if ((messageEnvelopeChars = messageEnvelope.c_str()))
    if ((messageHeaderChars = m_peerMessageHeader.c_str()))
    if (0 < (messageHeaderCharsLength = m_peerMessageHeader.length()))
    if ((messageChars = strstr(messageEnvelopeChars, messageHeaderChars)))
    {
        std::string message(messageChars+messageHeaderCharsLength);
        OnReceiveMessageFromPeer(peer_id, message);
        handled = true;
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::
OnFailedToConnectToServer(const std::string& server)
{ XOS_DBI(("()...\n")); Implements::OnFailedToConnectToServer(server); }

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnChangeStateToConnectToServer()
{ XOS_DBI(("()...\n")); OnChangeState(m_connectToServerStateName); }
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnChangeStateToListPeers()
{ XOS_DBI(("()...\n")); OnChangeState(m_listPeersStateName); }
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnChangeStateToStreaming()
{ XOS_DBI(("()...\n")); OnChangeState(m_streamingStateName); }
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnChangeState(const std::string& toState)
{ XOS_DBI(("(\"%s\")...\n", toState.c_str())); Implements::OnChangeState(toState); }

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::OnDefaultAction
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnDefaultAction
(int msg_id, int id, void* data)
{
    if ((callback_))
    switch(msg_id)
    {
    case UI_THREAD_CALLBACK:
        callback_->UIThreadCallback((id), (data));
        break;

    case UI_CONNECT_TO_SERVER:
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            callback_->StartLogin(m_serverName, m_serverPort);
            break;
        }
        break;

    case UI_DISCONNECT_SERVER:
        switch(ui_)
        {
        case STREAMING:
            callback_->DisconnectFromServer();
            break;

        case LIST_PEERS:
            callback_->DisconnectFromServer();
            break;
        }
        break;

    case UI_CONNECT_TO_PEER:
        switch(ui_)
        {
        case LIST_PEERS:
            if (0 > (m_peerId))
            {
                m_peerId = m_connectToPeerId;
                m_peerName = m_connectToPeerName;
                callback_->ConnectToPeer(m_peerId);
            }
            break;
        }
        break;

    case UI_DISCONNECT_PEER:
        switch(ui_)
        {
        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromCurrentPeer();
            break;
        }
        break;

    case UI_LBUTTON_UP:
        if ((m_handleButtonEvents))
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            m_autoConnectToPeer = m_autoConnectToPeerOn;
            m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
            callback_->StartLogin(m_serverName, m_serverPort);
            break;

        case LIST_PEERS:
            if (0 <= (m_connectToPeerId))
            {
                m_peerId = m_connectToPeerId;
                m_peerName = m_connectToPeerName;
                callback_->ConnectToPeer(m_peerId);
            }
            else
            callback_->DisconnectFromServer();
            break;

        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromCurrentPeer();
            break;
        }
        break;

    case UI_RBUTTON_UP:
        if ((m_handleButtonEvents))
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            m_autoConnectToPeer = m_autoConnectToPeerOn;
            m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
            callback_->StartLogin(m_serverName, m_serverPort);
            break;

        case LIST_PEERS:
            callback_->DisconnectFromServer();
            break;

        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromServer();
            break;
        }
        break;

    case UI_INVALIDATE_WINDOW:
        InvalidateWindow(id != 0);
        break;

    case UI_VALIDATE_WINDOW:
        ValidateWindow();
        break;
    }
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::OnOpen
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnOpen()
{
    if ((m_useOpenGLRenderer))
    if ((renderer_ = AcquireOpenGLRenderer()))
    if ((GetUseOpenGLRendererOn()))
        renderer_->use();
    else
    renderer_->dontUse();
    ui_thread_id_ = GetUIMessageThreadId();
    SwitchToConnectUI();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::OnClose
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnClose()
{
      if (callback_)
        callback_->Close();
      if ((renderer_))
      {
          ReleaseOpenGLRenderer(renderer_);
          renderer_ = 0;
      }
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnSize() 
{
    //if ((ui_ == STREAMING))
    if ((renderer_))
        ReshapeOpenGLRenderer(renderer_);
    //InvalidateWindow();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientBaseWindow::OnPaint() 
{
    if ((ui_ == STREAMING) 
        && (remote_video_.get()) 
        && (local_video_.get()))
    {
        AutoLock<XosWebRtcClientVideoRenderer> local_lock(local_video_.get());
        AutoLock<XosWebRtcClientVideoRenderer> remote_lock(remote_video_.get());
        const uint8* local_image;
        const uint8* remote_image;

        // if we have a remote stream
        if ((remote_image = remote_video_->image()))  
        {
            //Get dimensions
            int remote_width  = remote_video_->image_width();
            int remote_height = remote_video_->image_height();

            // if we have a local stream
            if ((local_image = local_video_->image()))
            {
                //Get dimensions
                int local_width  = local_video_->image_width();
                int local_height = local_video_->image_height();

                if ((OnPaintImage
                    (remote_image, remote_width, remote_height,
                     local_image, local_width, local_height)))
                    return;
            }
            else
            if ((OnPaintImage
                (remote_image, remote_width, remote_height, false)))
                return;
        }
        else
        // if we have a local stream
        if ((local_image = local_video_->image()))  
        {
            //Get dimensions
            int local_width  = local_video_->image_width();
            int local_height = local_video_->image_height();

            if ((OnPaintImage
                (local_image, local_width, local_height, true)))
                return;
        }
    }
    OnPaintBlank();
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::OnPaintImage
(const uint8* remote_image, int remote_width, int remote_height,
 const uint8* local_image, int local_width, int local_height) 
{
    if ((renderer_))
    if (!(renderer_->getDontUse()))
    {
        ValidateWindow();
        renderer_->render
        (remote_image, remote_width, remote_height,
         local_image, local_width, local_height);
        UpdateWindow();
        return true;
    }
    if ((OnRenderImage
        (remote_image, remote_width, remote_height,
         local_image, local_width, local_height)))
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::OnPaintImage
(const uint8* image, int width, int height, bool is_local) 
{
    if ((renderer_))
    if (!(renderer_->getDontUse()))
    {
        ValidateWindow();
        renderer_->render(image, width, height);
        UpdateWindow();
        return true;
    }
    if ((OnRenderImage(image, width, height, 0,0,0, is_local)))
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientBaseWindow::
///
///    Author: $author$
///      Date: 4/2/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientBaseWindow::OnPaintBlank() 
{
    return false;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
