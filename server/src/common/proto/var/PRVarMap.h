#ifndef _PRVarMap_H_
#define _PRVarMap_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/var/SUserVar.h>

class PRVarMap : public SMsgHead
{
public:
    std::map< std::string, SUserVar > var_map;

    PRVarMap()
    {
        msg_cmd = 1399214952;
    }

    virtual ~PRVarMap()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRVarMap(*this) );
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
            && TFVarTypeProcess( var_map, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRVarMap";
    }
};

#endif
