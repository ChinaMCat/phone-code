#ifndef _PQServerNotify_H_
#define _PQServerNotify_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*服务器变量修改通知*/
class PQServerNotify : public SMsgHead
{
public:
    std::string key;
    std::string value;

    PQServerNotify()
    {
        msg_cmd = 311682074;
    }

    virtual ~PQServerNotify()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQServerNotify(*this) );
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
            && TFVarTypeProcess( key, eType, stream, uiSize )
            && TFVarTypeProcess( value, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQServerNotify";
    }
};

#endif
