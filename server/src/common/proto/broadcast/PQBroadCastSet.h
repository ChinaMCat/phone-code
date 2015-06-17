#ifndef _PQBroadCastSet_H_
#define _PQBroadCastSet_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*@@设置频道监听, SUserChannel 的所有成员已包含在父类协议中*/
class PQBroadCastSet : public SMsgHead
{
public:
    uint8 set_type;    //kObjectAdd, kObjectDel

    PQBroadCastSet() : set_type(0)
    {
        msg_cmd = 884232017;
    }

    virtual ~PQBroadCastSet()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQBroadCastSet(*this) );
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
            && TFVarTypeProcess( set_type, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQBroadCastSet";
    }
};

#endif
