#ifndef _PRMarketBatchBuy_H_
#define _PRMarketBatchBuy_H_

#include <weedong/core/seq/seq.h>
#include <proto/common/SMsgHead.h>
#include <proto/common/S3UInt32.h>

class PRMarketBatchBuy : public SMsgHead
{
public:
    uint32 result;    //0 为购买成功, 非 0 为对应错误码
    std::vector< S3UInt32 > coins;    //批量购买列表
    uint32 value;    //预扣除货币值
    uint32 path;

    PRMarketBatchBuy() : result(0), value(0), path(0)
    {
        msg_cmd = 1792916194;
    }

    virtual ~PRMarketBatchBuy()
    {
    }

    virtual wd::CSeq* clone(void)
    {
        return ( new PRMarketBatchBuy(*this) );
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
            && TFVarTypeProcess( result, eType, stream, uiSize )
            && TFVarTypeProcess( coins, eType, stream, uiSize )
            && TFVarTypeProcess( value, eType, stream, uiSize )
            && TFVarTypeProcess( path, eType, stream, uiSize )
            && loopend( stream, eType, uiSize );
    }
    operator const char* ()
    {
        return "PRMarketBatchBuy";
    }
};

#endif
