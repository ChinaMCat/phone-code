#ifndef _PQItemAdd_H_
#define _PQItemAdd_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*@@添加一个物品*/
class PQItemAdd : public SMsgHead
{
public:
    uint32 id;    //添加物品的id
    uint32 count;    //添加物品的数量

    PQItemAdd() : id(0), count(0)
    {
        msg_cmd = 731904243;
    }

    virtual ~PQItemAdd()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQItemAdd(*this) );
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
            && TFVarTypeProcess( count, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQItemAdd";
    }
};

#endif
