#ifndef _PRTrialRewardGet_H_
#define _PRTrialRewardGet_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

class PRTrialRewardGet : public SMsgHead
{
public:
    uint32 id;    //试炼ID
    uint32 index;    //奖励index

    PRTrialRewardGet() : id(0), index(0)
    {
        msg_cmd = 1462254479;
    }

    virtual ~PRTrialRewardGet()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRTrialRewardGet(*this) );
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
            && TFVarTypeProcess( id, eType, stream, uiSize )
            && TFVarTypeProcess( index, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRTrialRewardGet";
    }
};

#endif
