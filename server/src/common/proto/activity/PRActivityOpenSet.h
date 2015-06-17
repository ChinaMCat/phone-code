#ifndef _PRActivityOpenSet_H_
#define _PRActivityOpenSet_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/activity/SActivityOpen.h>

/*服务器用    share - game*/
class PRActivityOpenSet : public SMsgHead
{
public:
    uint32 type;    //kObjectAdd
    SActivityOpen open;

    PRActivityOpenSet() : type(0)
    {
        msg_cmd = 1378801592;
    }

    virtual ~PRActivityOpenSet()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRActivityOpenSet(*this) );
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
            && TFVarTypeProcess( type, eType, stream, uiSize )
            && TFVarTypeProcess( open, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRActivityOpenSet";
    }
};

#endif
