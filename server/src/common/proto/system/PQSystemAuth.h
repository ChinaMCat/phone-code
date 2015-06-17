#ifndef _PQSystemAuth_H_
#define _PQSystemAuth_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*帐号验证*/
class PQSystemAuth : public SMsgHead
{
public:
    int32 outside_sock;    //外部连接号

    PQSystemAuth() : outside_sock(0)
    {
        msg_cmd = 143043716;
    }

    virtual ~PQSystemAuth()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQSystemAuth(*this) );
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
            && TFVarTypeProcess( outside_sock, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQSystemAuth";
    }
};

#endif
