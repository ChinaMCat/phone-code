#ifndef _PQGuildCreate_H_
#define _PQGuildCreate_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*创建公会*/
class PQGuildCreate : public SMsgHead
{
public:
    std::string name;    //公会名称

    PQGuildCreate()
    {
        msg_cmd = 217782399;
    }

    virtual ~PQGuildCreate()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQGuildCreate(*this) );
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
            && TFVarTypeProcess( name, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQGuildCreate";
    }
};

#endif
