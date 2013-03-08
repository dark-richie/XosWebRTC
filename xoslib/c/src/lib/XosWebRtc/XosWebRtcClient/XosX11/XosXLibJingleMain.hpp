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
///   File: XosXLibJingleMain.hpp
///
/// Author: $author$
///   Date: 6/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSXLIBJINGLEMAIN_HPP
#define _XOSXLIBJINGLEMAIN_HPP

#include "XosXWindowMain.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosXWindowMainImplement XosXLibJingleMainImplement;
typedef XosXWindowMain XosXLibJingleMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosXLibJingleMain
///
/// Author: $author$
///   Date: 6/10/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosXLibJingleMain
: virtual public XosXLibJingleMainImplement,
  public XosXLibJingleMainExtend
{
public:
    typedef XosXLibJingleMainImplement Implements;
    typedef XosXLibJingleMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosXLibJingleMain
    ///
    ///       Author: $author$
    ///         Date: 6/10/2012
    ///////////////////////////////////////////////////////////////////////
    XosXLibJingleMain()
    {
    }
    virtual ~XosXLibJingleMain()
    {
    }

    virtual int ProcessXEvents
    (int argc, char** argv, char** env)
    {
        int err = 0;
        err = Extends::ProcessXEvents(argc, argv, env);
        return err;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSXLIBJINGLEMAIN_HPP 
