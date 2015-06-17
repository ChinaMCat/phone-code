#ifndef _PQSingleArenaLogSave_H_
#define _PQSingleArenaLogSave_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/singlearena/SSingleArenaLog.h>

class PQSingleArenaLogSave : public SMsgHead
{
public:
    uint32 target_id;
    std::vector< SSingleArenaLog > list;

    PQSingleArenaLogSave() : target_id(0)
    {
        msg_cmd = 912156268;
    }

    virtual ~PQSingleArenaLogSave()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQSingleArenaLogSave(*this) );
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
            && TFVarTypeProcess( list, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQSingleArenaLogSave";
    }
};

#endif
