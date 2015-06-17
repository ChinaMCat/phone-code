#ifndef _PRFightLoadRecord_H_
#define _PRFightLoadRecord_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

class PRFightLoadRecord : public SMsgHead
{
public:
    uint32 fight_record_id;

    PRFightLoadRecord() : fight_record_id(0)
    {
        msg_cmd = 3160466027;
    }

    virtual ~PRFightLoadRecord()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRFightLoadRecord(*this) );
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

    bool loop( wd::CStream &stream, wd::CSeq::ELoopType type, uint32& uiSize )
    {
        uint32 _uiSize = 0;
        return SMsgHead::loop( stream, type, _uiSize )
            && wd::CSeq::loop( stream, type, uiSize )
            && TFVarTypeProcess( fight_record_id, type, stream, uiSize )
            && loopend( stream, type, uiSize );
    }
};

#endif
