#ifndef _PRBroadCastList_H_
#define _PRBroadCastList_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/broadcast/SUserChannel.h>

class PRBroadCastList : public SMsgHead
{
public:
    std::vector< SUserChannel > channel_list;

    PRBroadCastList()
    {
        msg_cmd = 1558437242;
    }

    virtual ~PRBroadCastList()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRBroadCastList(*this) );
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
            && TFVarTypeProcess( channel_list, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRBroadCastList";
    }
};

#endif
