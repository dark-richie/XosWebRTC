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
///   File: XosWebRtcClientImageInterface.hpp
///
/// Author: $author$
///   Date: 12/31/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTIMAGEINTERFACE_HPP
#define _XOSWEBRTCCLIENTIMAGEINTERFACE_HPP

#include "XosInterfaceBase.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientImageObserverInterface
///
/// Author: $author$
///   Date: 12/31/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientImageObserverInterface
{
public:
    virtual bool InvalidateWindow
    (bool eraseBackground = true) 
    { 
        return true; 
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientImageInterface
///
/// Author: $author$
///   Date: 12/31/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientImageInterface
{
public:
    typedef int Format;
    enum {
        FORMAT_NONE = 0,
        FORMAT_GL_BGRA,
        FORMAY_GL_RGBA
    };

    virtual uint8_t* AcquireRemoteImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireRemoteImage(width, height, format);
        return image;
    }
    virtual bool ReleaseRemoteImage
    (uint8_t* image)
    {
        bool success = false;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseRemoteImage(image);
        return success;
    }

    virtual uint8_t* AcquireLocalImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireLocalImage(width, height, format);
        return image;
    }
    virtual bool ReleaseLocalImage
    (uint8_t* image)
    {
        bool success = false;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseLocalImage(image);
        return success;
    }

    virtual uint8_t* GetRemoteImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->GetRemoteImage(width, height, format);
        return image;
    }
    virtual uint8_t* GetLocalImage(int& width, int& height, Format& format)
    {
        uint8_t* image = 0;
        //XOS_DBI(("() in.."));
        XosWebRtcClientImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->GetLocalImage(width, height, format);
        return image;
    }

    virtual void RegisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        XosWebRtcClientImageInterface* imageInterface;
        //XOS_DBI(("() in.."));
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->RegisterImageObserver(imageObserver);
    }
    virtual void UnregisterImageObserver
    (XosWebRtcClientImageObserverInterface* imageObserver)
    {
        XosWebRtcClientImageInterface* imageInterface;
        //XOS_DBI(("() in.."));
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->UnregisterImageObserver(imageObserver);
    }

    virtual XosWebRtcClientImageInterface* ImageInterfaceDelegated() const 
    {
        return 0;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTIMAGEINTERFACE_HPP 
        

