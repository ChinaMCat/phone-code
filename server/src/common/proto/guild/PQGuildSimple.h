#ifndef _PQGuildSimple_H_
#define _PQGuildSimple_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*公会基本数据请求*/
class PQGuildSimple : public SMsgHead
{
public:
    uint32 target_id;

    PQGuildSimple() : target_id(0)
    {
        msg_cmd = 285286939;
    }

    virtual ~PQGuildSimple()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQGuildSimple(*this) );
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
            && TFVarTypeProcess( target_id, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQGuildSimple";
    }
};

#endif
