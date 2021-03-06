#ifndef _PQPlayerFightQuit_H_
#define _PQPlayerFightQuit_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*战斗退出*/
class PQPlayerFightQuit : public SMsgHead
{
public:
    uint32 fight_id;    //战斗id

    PQPlayerFightQuit() : fight_id(0)
    {
        msg_cmd = 761774693;
    }

    virtual ~PQPlayerFightQuit()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQPlayerFightQuit(*this) );
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
            && TFVarTypeProcess( fight_id, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQPlayerFightQuit";
    }
};

#endif
