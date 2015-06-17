#ifndef _WEEDONG_CORE_SEQ_SEQPARSER_H_
#define _WEEDONG_CORE_SEQ_SEQPARSER_H_

#include <weedong/core/seq/seq.h>

#include <string>
#include <list>
#include <fstream>

namespace wd
{

/*************************************************
  Description:      // ���л���¼��ĳ�Ա��ṹ
  Other:            // ��¼���л���ĳ�Ա������Ϣ
*************************************************/
class CSeqEle : public wd::CSeq
{
public:
    enum EVarType
    {
        eUnknow,
        eInt8,
        eUint8,
        eInt16,
        eUint16,
        eInt32,
        eUint32,
        eFloat,
        eDouble,
        eString,
        eObject,
        eArray,
        eMap,
        eIndices,
        eBytes,
    };
public:
    std::string eleType;    //��������
    std::string eleName;    //��������
    std::string eleDefault;    //����Ĭ��ֵ
    std::string eleDescript;    //����˵��
    std::vector< CSeqEle > eleObject;    //������������

    CSeqEle()
    {
    }

    bool write( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eWrite, uiSize );
    }
    bool read( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eRead, uiSize );
    }

    bool loop( wd::CStream &stream, CSeq::ELoopType type, uint32 &uiSize )
    {
        return wd::CSeq::loop( stream, type, uiSize )
            && TFVarTypeProcess( eleType, type, stream, uiSize )
            && TFVarTypeProcess( eleName, type, stream, uiSize )
            && TFVarTypeProcess( eleDefault, type, stream, uiSize )
            && TFVarTypeProcess( eleDescript, type, stream, uiSize )
            && TFVarTypeProcess( eleObject, type, stream, uiSize )
            && loopend( stream, type, uiSize );
    }

    static EVarType name2type( std::string type );
};

/*************************************************
  Description:      // ���л���¼��ĳ�ʼ���ṹ
  Other:            // ��¼���л���ĳ�ʼ��������Ϣ
*************************************************/
class CSeqInit : public wd::CSeq
{
public:
    std::string eleName;    //��������
    std::string eleDefault;    //����Ĭ��ֵ
    std::string eleDescript;    //����˵��

    CSeqInit()
    {
    }

    bool write( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eWrite, uiSize );
    }
    bool read( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eRead, uiSize );
    }

    bool loop( wd::CStream &stream, CSeq::ELoopType type, uint32 &uiSize )
    {
        return wd::CSeq::loop( stream, type, uiSize )
            && TFVarTypeProcess( eleName, type, stream, uiSize )
            && TFVarTypeProcess( eleDefault, type, stream, uiSize )
            && TFVarTypeProcess( eleDescript, type, stream, uiSize )
            && loopend( stream, type, uiSize );
    }
};

/*************************************************
  Description:      // ���л���¼�����Ϣ�ṹ
  Other:            // ��¼���л���Ļ�����Ϣ
*************************************************/
class CSeqLog : public wd::CSeq
{
public:
    std::string className;    //������
    std::string classParent;    //��������
    std::string classDescript;    //��˵��
    std::vector< CSeqEle > eleList;    //��Ա����
    std::vector< CSeqInit > initList;    //��ʼ������

    CSeqLog()
    {
    }

    bool write( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eWrite, uiSize );
    }
    bool read( wd::CStream &stream )
    {
        uint32 uiSize = 0;
        return loop( stream, CSeq::eRead, uiSize );
    }

    bool loop( wd::CStream &stream, CSeq::ELoopType type, uint32 &uiSize )
    {
        return wd::CSeq::loop( stream, type, uiSize )
            && TFVarTypeProcess( className, type, stream, uiSize )
            && TFVarTypeProcess( classParent, type, stream, uiSize )
            && TFVarTypeProcess( classDescript, type, stream, uiSize )
            && TFVarTypeProcess( eleList, type, stream, uiSize )
            && TFVarTypeProcess( initList, type, stream, uiSize )
            && loopend( stream, type, uiSize );
    }
};

class CSeqParser
{
public:
    enum EParseState
    {
        eClassDef = 1,
        eConstruct = 2,
    };
    typedef std::list< std::pair< int32, std::string > > TError;

public:
    /*************************************************
    Description:    �����л���¼������Ϣ����Ϊseqlog
    Input:          start ��Ҫ���͵Ļ�����Ϣ��ʼָ��
                    end ��Ҫ���͵Ļ�����Ϣ����ָ��
    Output:         errors ���������ִ��������
    Return:         ���¼�б�
    *************************************************/
    static std::list< CSeqLog > parse( char *start, char *end, TError& errors );

private:
    static bool parseClassDeclare( char* &start, char *end, wd::CSeqLog &log, std::list< std::pair< char*, std::string > > &error_info );
    static bool parseClassInfo( char* &start, char *end, wd::CSeqLog &log, std::list< std::pair< char*, std::string > > &error_info );
    static bool parseClassConstruct( char* &start, char *end, wd::CSeqLog &log, std::list< std::pair< char*, std::string > > &error_info );
    static bool parseElement( char* &start, char *end, CSeqEle &ele, std::list< std::pair< char*, std::string > > &error_info );
    static bool parseInit( char* &start, char *end, CSeqInit &init, std::list< std::pair< char*, std::string > > &error_info );

private:
    static void pushErrorInfo( std::list< std::pair< char*, std::string > > &error_info, char* address, const char* info );
    static int32 getLineNum( char* start, char* end );

private:
    static bool checkChar( char chr );
    static bool gotoNextChar( char* &start, char *end );
    static bool gotoNextLine( char* &start, char *end );
    static std::string takeNext( char* &start, char *end );
    static std::string takeNextRemake( char* &start, char *end );
    static std::string takeNextSyntax( char* &start, char *end );
    static std::string takeNextWord( char* &start, char *end );
};

}

#endif

