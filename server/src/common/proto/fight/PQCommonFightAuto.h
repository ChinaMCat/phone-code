#ifndef _PQCommonFightAuto_H_
#define _PQCommonFightAuto_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*触发假人战斗*/
class PQCommonFightAuto : public SMsgHead
{
public:
    uint32 target_id;    //目标的怪物id

    PQCommonFightAuto() : target_id(0)
    {
        msg_cmd = 403257916;
    }

    virtual ~PQCommonFightAuto()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQCommonFightAuto(*this) );
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
            && TFVarTypeProcess( target_id, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQCommonFightAuto";
    }
};

#endif
