#ifndef _PRGuildPost_H_
#define _PRGuildPost_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

class PRGuildPost : public SMsgHead
{
public:
    std::string content;

    PRGuildPost()
    {
        msg_cmd = 1300943509;
    }

    virtual ~PRGuildPost()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRGuildPost(*this) );
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
            && TFVarTypeProcess( content, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRGuildPost";
    }
};

#endif
