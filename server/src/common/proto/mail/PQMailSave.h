#ifndef _PQMailSave_H_
#define _PQMailSave_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/mail/SUserMail.h>

class PQMailSave : public SMsgHead
{
public:
    SUserMail data;

    PQMailSave()
    {
        msg_cmd = 435304958;
    }

    virtual ~PQMailSave()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PQMailSave(*this) );
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
            && TFVarTypeProcess( data, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PQMailSave";
    }
};

#endif
