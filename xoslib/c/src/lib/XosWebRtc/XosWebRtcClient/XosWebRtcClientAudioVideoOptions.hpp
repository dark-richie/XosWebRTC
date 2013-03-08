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
///   File: XosWebRtcClientAudioVideoOptions.hpp
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTAUDIOVIDEOOPTIONS_HPP
#define _XOSWEBRTCCLIENTAUDIOVIDEOOPTIONS_HPP

#include "XosWebRtcClientAudioVideoOptionsInterface.hpp"
#include "XosWebRtcClientAudioOptionsInterface.hpp"
#include "XosWebRtcClientVideoOptionsInterface.hpp"
#include "XosExportBase.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientAudioVideoOptionsImplement
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientAudioVideoOptionsInterface
XosWebRtcClientAudioVideoOptionsImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientAudioVideoOptionsExtend
///
///  Author: $author$
///    Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosWebRtcClientAudioVideoOptionsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientAudioVideoOptions
///
/// Author: $author$
///   Date: 4/5/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientAudioVideoOptions
: virtual public XosWebRtcClientAudioVideoOptionsImplement,
  public XosWebRtcClientAudioVideoOptionsExtend
{
public:
    typedef XosWebRtcClientAudioVideoOptionsImplement Implements;
    typedef XosWebRtcClientAudioVideoOptionsExtend Extends;

    XosWebRtcClientAudioVideoOptionsInterface* m_delegated;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientAudioVideoOptions
    ///
    ///       Author: $author$
    ///         Date: 4/5/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientAudioVideoOptions
    (XosWebRtcClientAudioVideoOptionsInterface* delegated=0)
    : m_delegated(delegated)
    {
    }

    virtual void SetVideoCaptureDevice(const std::string& val)
    {
        if ((m_delegated))
            m_delegated->SetVideoCaptureDevice(val);
    }
    virtual std::string GetVideoCaptureDevice() const
    {
        std::string val;
        if ((m_delegated))
            val = m_delegated->GetVideoCaptureDevice();
        return val;
    }

    virtual void SetVideoCodecModeName(const std::string& toModeName)
    {
        if ((m_delegated))
            m_delegated->SetVideoCodecModeName(toModeName);
    }
    virtual std::string GetVideoCodecModeName() const
    {
        std::string val;
        if ((m_delegated))
            val = m_delegated->GetVideoCodecModeName();
        return val;
    }

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight, int frameRate, int minBitrate)
    {
        if ((m_delegated))
            m_delegated->SetVideoCodecOptions
            (codecWidth, codecHeight, frameRate, minBitrate);
    }
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const
    {
        if ((m_delegated))
            m_delegated->GetVideoCodecOptions
            (codecWidth, codecHeight, frameRate, minBitrate);
    }

    virtual void SetAudioDeviceOptions
    (bool echoCancellation, bool noiseSupression, bool autoGainControl)
    {
        if ((m_delegated))
            m_delegated->SetAudioDeviceOptions
            (echoCancellation, noiseSupression, autoGainControl);
    }
    virtual void GetAudioDeviceOptions
    (bool& echoCancellation, bool& noiseSupression, bool& autoGainControl) const
    {
        if ((m_delegated))
            m_delegated->GetAudioDeviceOptions
            (echoCancellation, noiseSupression, autoGainControl);
    }

    virtual XosWebRtcClientAudioVideoOptionsInterface* Delegate
    (XosWebRtcClientAudioVideoOptionsInterface* delegateTo)
    {
        m_delegated = delegateTo;
        return m_delegated;
    }
    virtual XosWebRtcClientAudioVideoOptionsInterface* Delegated() const
    {
        return m_delegated;
    }
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTAUDIOVIDEOOPTIONS_HPP 
        

