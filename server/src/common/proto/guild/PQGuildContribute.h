#ifndef _PQGuildContribute_H_
#define _PQGuildContribute_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*贡献*/
class PQGuildContribute : public SMsgHead
{
public:
    uint32 id;

    PQGuildContribute() : id(0)
    {
        msg_cmd = 886345701;
    }

    virtual ~PQGuildContribute()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQGuildContribute(*this) );
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
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQGuildContribute";
    }
};

#endif
