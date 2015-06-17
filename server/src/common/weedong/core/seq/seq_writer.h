#ifndef _WEEDONG_CORE_SEQ_WRITER_H_
#define _WEEDONG_CORE_SEQ_WRITER_H_

#include <weedong/core/seq/seq_parser.h>

#include <map>
#include <string>
#include <sstream>

namespace wd
{
    
class CSeqWriter
{
public:
    /*************************************************
    Description:     �����л���¼����C++���ļ�
    Input:           log ��Ҫ���ɵ����¼�ļ�
    Return:          ���¼�ַ���
    *************************************************/
    static std::string transformCPP( CSeqLog &log );

    /*************************************************
    Description:     �����л���¼����AS���ļ�
    Input:           log ��Ҫ���ɵ����¼�ļ�
    Return:          ���¼�ַ���
    *************************************************/
    static std::string transformAS( CSeqLog &log );
    static std::string transformAS( CSeqLog &log, const char* packetPath, std::list<std::string> &import, std::map< std::string, std::string > &classDir );

    /*************************************************
    Description:     �����л���¼����Seq��¼��Ϣ�ļ�
    Input:           log ��Ҫ���ɵ����¼�ļ�
    Return:          ���¼�ַ���
    *************************************************/
    static std::string transformSEQ( CSeqLog &log );

    /*************************************************
    Description:     �������л���¼�����������������б�
    Input:           log ��Ҫ���������б�ļ�¼�ļ�
    Return:          ���������б�
    *************************************************/
    static std::list<std::string> filtrateClass( CSeqLog &log );
};

}

#endif

