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
///   File: XosWebRtcClientUIMessageQueue.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTUIMESSAGEQUEUE_HPP
#define _XOSWEBRTCCLIENTUIMESSAGEQUEUE_HPP

#include <deque>

#include "XosMutex.hpp"
#include "XosSemaphore.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientUIMessageQueueImplement
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosInterfaceBase
XosWebRtcClientUIMessageQueueImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientUIMessageQueueExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosWebRtcClientUIMessageQueueExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientUIMessageQueue
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientUIMessageQueue
: virtual public XosWebRtcClientUIMessageQueueImplement,
  public XosWebRtcClientUIMessageQueueExtend
{
public:
    typedef XosWebRtcClientUIMessageQueueImplement Implements;
    typedef XosWebRtcClientUIMessageQueueExtend Extends;

protected:
    class UIMessage
    {
    friend class XosWebRtcClientUIMessageQueue;
    protected:
        int m_msg_id; int m_msg; void* m_data;
    public:
        UIMessage
        (int msg_id, int msg, void* data)
        : m_msg_id(msg_id), m_msg(msg), m_data(data) 
        {}
        UIMessage
        (const UIMessage& copy)
        : m_msg_id(copy.m_msg_id), m_msg(copy.m_msg), m_data(copy.m_data) 
        {}
    };

    XosMutex m_mtx;
    XosSemaphore m_sem;
    std::deque<UIMessage> m_q;

public:
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientUIMessageQueue
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientUIMessageQueue()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientUIMessageQueue
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientUIMessageQueue()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///
    /// Must be called before message thread is started!
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init()
    {
        bool isSuccess = false;
        if ((isSuccess = (m_mtx.Create())))
        {
            if (!(isSuccess = (m_sem.Create())))
                m_mtx.Destroy();
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///
    /// Must be called after message thread has stopped!
    ///////////////////////////////////////////////////////////////////////
    virtual bool Finish()
    {
        bool isSuccess = false;
        
        if (!(m_q.empty()))
            XOS_DBE(("() m_q not empty\n"));

        isSuccess = m_sem.Destroy();

        if (!(m_mtx.Destroy()))
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: PostUIMessage
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool PostUIMessage
    (int msg_id, int msg, void* data)
    {
        UIMessage uiMsg(msg_id, msg, data);
        bool isSuccess = false;
        XosError error;
        if ((isSuccess = !(error = m_mtx.Lock())))
        {
            m_q.push_back(uiMsg);
            m_sem.Release();
            m_mtx.Unlock();
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetUIMessage
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetUIMessage
    (int& msg_id, int& msg, void*& data)
    {
        bool isSuccess = false;
        bool qIsEmpty;
        XosError error;
        if (!(error = m_mtx.Lock()))
        {
            do
            {
                if (!(qIsEmpty = m_q.empty()))
                {
                    UIMessage& uiMsg = m_q.front();
                    msg_id = uiMsg.m_msg_id;
                    msg = uiMsg.m_msg;
                    data = uiMsg.m_data;
                    m_q.pop_front();
                }
                m_mtx.Unlock();
                if (!(isSuccess = !(qIsEmpty)))
                {
                    XOS_DBT(("() waiting for message...\n"));
                    if (!(error = m_sem.Acquire()))
                    if (!(error = m_mtx.Lock()))
                    {
                        XOS_DBT(("() ...received message\n"));
                        continue;
                    }
                    return false;
                }
            }
            while((qIsEmpty));
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: PeekUIMessage
    ///
    ///    Author: $author$
    ///      Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool PeekUIMessage
    (int& msg_id, int& msg, void*& data,
     bool dontRemove=false)
    {
        bool isSuccess = false;
        bool qIsEmpty;
        XosError error;
        if (!(error = m_mtx.Lock()))
        {
            //XOS_DBT(("() checking for message...\n"));
            if ((isSuccess = !(qIsEmpty = m_q.empty())))
            {
                UIMessage& uiMsg = m_q.front();
                msg_id = uiMsg.m_msg_id;
                msg = uiMsg.m_msg;
                data = uiMsg.m_data;
                XOS_DBI(("() ...received message\n"));
                if (!(dontRemove))
                    m_q.pop_front();
            }
            m_mtx.Unlock();
        }
        return isSuccess;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTUIMESSAGEQUEUE_HPP 
        

