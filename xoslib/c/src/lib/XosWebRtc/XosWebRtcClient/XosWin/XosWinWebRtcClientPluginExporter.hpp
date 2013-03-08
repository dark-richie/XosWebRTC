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
///   File: XosWinWebRtcClientPluginExporter.hpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTPLUGINEXPORTER_HPP
#define _XOSWINWEBRTCCLIENTPLUGINEXPORTER_HPP

#include "XosWinWebRtcClientPluginInterface.hpp"
#include "XosExportBase.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginExporterImplement
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosInterfaceBase
XosWinWebRtcClientPluginExporterImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientPluginExporterExtend
///
///  Author: $author$
///    Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
typedef XosExportBase
XosWinWebRtcClientPluginExporterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginExporter
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientPluginExporter
: virtual public XosWinWebRtcClientPluginExporterImplement,
  public XosWinWebRtcClientPluginExporterExtend
{
public:
    typedef XosWinWebRtcClientPluginExporterImplement Implements;
    typedef XosWinWebRtcClientPluginExporterExtend Extends;

    XosWinWebRtcClientPluginExporter* m_oldExporter;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientPluginExporter
    ///
    ///       Author: $author$
    ///         Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientPluginExporter()
    : m_oldExporter(GetExporter())
    {
        GetExporter() = (this);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientPluginExporter
    ///
    ///      Author: $author$
    ///        Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientPluginExporter()
    {
        if (GetExporter() == (this))
            GetExporter() = m_oldExporter;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: Init
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Init()
    {
        XosError error = XOS_ERROR_NONE;
        return error;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: Finish
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError Finish()
    {
        XosError error = XOS_ERROR_NONE;
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: AcquirePlugin
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWinWebRtcClientPluginInterface* AcquirePlugin
    (XosError& error)
    {
        XosWinWebRtcClientPluginInterface* plugin = 0;
        error = XOS_ERROR_FAILED;
        plugin = XosWinWebRtcClientPluginInterface::AcquireTheInstance(error);
        return plugin;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: ReleasePlugin
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosError ReleasePlugin
    (XosWinWebRtcClientPluginInterface* plugin)
    {
        XosError error = XOS_ERROR_FAILED;
        error = XosWinWebRtcClientPluginInterface::ReleaseTheInstance(plugin);
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetExporter
    ///
    ///    Author: $author$
    ///      Date: 12/10/2012
    ///////////////////////////////////////////////////////////////////////
    static XosWinWebRtcClientPluginExporter*& GetExporter()
    {
        static XosWinWebRtcClientPluginExporter* exporter = 0;
        return exporter;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTPLUGINEXPORTER_HPP 
        

