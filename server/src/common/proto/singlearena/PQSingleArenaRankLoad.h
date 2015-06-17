#ifndef _PQSingleArenaRankLoad_H_
#define _PQSingleArenaRankLoad_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*加载排行榜数据*/
class PQSingleArenaRankLoad : public SMsgHead
{
public:

    PQSingleArenaRankLoad()
    {
        msg_cmd = 351363324;
    }

    virtual ~PQSingleArenaRankLoad()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQSingleArenaRankLoad(*this) );
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
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQSingleArenaRankLoad";
    }
};

#endif
