#ifndef _SEffectData_H_
#define _SEffectData_H_

#include <weedong/core/seq/seq.h>
#include <proto/client/SEffect.h>

class SEffectData : public wd::CSeq
{
public:
    std::vector< SEffect > DataList;

    SEffectData()
    {
    }

    virtual ~SEffectData()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new SEffectData(*this) );
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
        return wd::CSeq::loop( stream, eType, uiSize )
            && TFVarTypeProcess( DataList, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "SEffectData";
    }
};

#endif
