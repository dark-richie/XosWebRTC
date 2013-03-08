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
///   File: XosWinWebRtcClientPluginDLibraryMain.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGINDLIBRARYMAIN_HPP
#define _XOSWINWEBRTCCLIENTPLUGINDLIBRARYMAIN_HPP

#include "XosWinWebRtcClientPluginExporter.hpp"
#include "XosDLibraryMain.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginDLibraryMainImplement
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosDLibraryMainImplement
XosWinWebRtcClientPluginDLibraryMainImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginDLibraryMainExtend
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosDLibraryMain
XosWinWebRtcClientPluginDLibraryMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginDLibraryMain
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPluginDLibraryMain
: virtual public XosWinWebRtcClientPluginDLibraryMainImplement,
  public XosWinWebRtcClientPluginDLibraryMainExtend
{
public:
    typedef XosWinWebRtcClientPluginDLibraryMainImplement Implements;
    typedef XosWinWebRtcClientPluginDLibraryMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPluginDLibraryMain
    ///
    ///       Author: $author$
    ///         Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPluginDLibraryMain()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPluginDLibraryMain
    ///
    ///      Author: $author$
    ///        Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPluginDLibraryMain()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init()
    {
        bool isTrue = false;
        XosError error = 0;
        XosWinWebRtcClientPluginExporter* exporter = 0;
        if ((WinInit()))
        {
            if ((exporter = XosWinWebRtcClientPluginExporter::GetExporter()))
            if (!(error = exporter->Init()))
                return true;
            WinFinish();
        }
        return isTrue;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool Finish()
    {
        bool isTrue = false;
        XosError error = 0;
        XosWinWebRtcClientPluginExporter* exporter = 0;
        if ((exporter = XosWinWebRtcClientPluginExporter::GetExporter()))
        if (!(error = exporter->Finish()))
            isTrue = true;
        if (!(WinFinish()))
            isTrue = false;
        return isTrue;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: WinInit
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool WinInit();
    ///////////////////////////////////////////////////////////////////////
    ///  Function: WinFinish
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual bool WinFinish();
};


#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGINDLIBRARYMAIN_HPP 
        

