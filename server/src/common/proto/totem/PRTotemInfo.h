#ifndef _PRTotemInfo_H_
#define _PRTotemInfo_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/totem/STotemInfo.h>

class PRTotemInfo : public SMsgHead
{
public:
    STotemInfo info;

    PRTotemInfo()
    {
        msg_cmd = 2008807582;
    }

    virtual ~PRTotemInfo()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRTotemInfo(*this) );
    }

    virtual bool write( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, wd::CSeq::eWrite, uiSize );
    }
    virtual bool read( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, wd::CSeq::eRead, uiSize );
    }

    bool loop( wd::CStream &stream, wd::CSeq::ELoopType eType, uint32& uiSize )
    {
        uint32 _uiSize = 0;
        return SMsgHead::loop( stream, eType, _uiSize )
            && wd::CSeq::loop( stream, eType, uiSize )
            && TFVarTypeProcess( info, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRTotemInfo";
    }
};

#endif
