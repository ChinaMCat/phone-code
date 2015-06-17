#ifndef _PQMarketSellTimeout_H_
#define _PQMarketSellTimeout_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

class PQMarketSellTimeout : public SMsgHead
{
public:
    uint32 sid;    //服务器id 

    PQMarketSellTimeout() : sid(0)
    {
        msg_cmd = 262770350;
    }

    virtual ~PQMarketSellTimeout()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQMarketSellTimeout(*this) );
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
            && TFVarTypeProcess( sid, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQMarketSellTimeout";
    }
};

#endif
