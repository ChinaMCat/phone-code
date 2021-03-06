#ifndef _PREquipSelectSuits_H_
#define _PREquipSelectSuits_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>

/*套装选择列表更新*/
class PREquipSelectSuits : public SMsgHead
{
public:
    std::vector< uint32 > select_suits;

    PREquipSelectSuits()
    {
        msg_cmd = 1083849332;
    }

    virtual ~PREquipSelectSuits()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PREquipSelectSuits(*this) );
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
            && TFVarTypeProcess( select_suits, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PREquipSelectSuits";
    }
};

#endif
