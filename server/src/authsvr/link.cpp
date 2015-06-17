#include "linkdef.h"
#include "iomgr.h"
#include "netio.h"
#include "pack.h"
#include "settings.h"
#include "local.h"
#include "proto/auth.h"

NET_SINGLE_READ( game )
{
    thePack.PushData( local::game, sock, buff, size );
}

void link_outside_accept( void* param, int32 sock )
{
    theIOMgr.AddSock( sock );
}
NET_SINGLE_CONNECT( game )
{
    static uint16 bind_sock = 0;
    if ( bind_sock == 0 )
    {
        bind_sock = theNet.Accept( settings::json()[ "outside_addr" ].asString().c_str(), link_outside_accept, NULL );
        if ( bind_sock == 0 )
        {
            LOG_ERROR( "建立监听失败[%s]", settings::json()[ "outside_addr" ].asString().c_str() );
        }
        else
        {
            LOG_INFO( "外部连接创建成功: %hu", bind_sock );
        }
    }
}

NET_SINGLE_READ( realdb )
{
    thePack.PushData( local::realdb, sock, buff, size );
}

NET_SINGLE_CONNECT( realdb )
{
    PQAuthRunTimeList req;

    local::write( local::realdb, req );
}

