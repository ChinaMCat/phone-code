#ifndef _PRMailSystemTake_H_
#define _PRMailSystemTake_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/mail/SUserMail.h>

class PRMailSystemTake : public SMsgHead
{
public:
    std::map< uint32, SUserMail > data;

    PRMailSystemTake()
    {
        msg_cmd = 1976428632;
    }

    virtual ~PRMailSystemTake()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRMailSystemTake(*this) );
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
            && TFVarTypeProcess( data, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRMailSystemTake";
    }
};

#endif
