/*************************************************
  Model:            // ���л��ṹ
  Class:            // �з�����
  Name:             // ������
  Date:             // 2011-11-21
  Descript:
    ʹ�� <ģ��> ��ʽʵ�ֵ����л��๦��

  ֧�ֵĻ�������������:
  int8 uint8 int16 uint16 int32 uint32 float

  ֧�ֵĶ�����������:
  string : ͨ�� std::string ��Ϊ string ���͵�ʵ�ַ�ʽ
  object : ֻ֧����Ϊ CSeq ��������

  ֧�ֵ���������������:
  array : ͨ�� std::vector ��Ϊ array ���͵�ʵ�ַ�ʽ
  map : ͨ�� std::map ��Ϊ map ���͵�ʵ�ַ�ʽ, key ͳһΪ std::string

  ������Ԫ�����ͽ��ܷ�Ϊ��: [ ���л�������, ���ж������� ]
*************************************************/

#ifndef _WEEDONG_CORE_SEQ_SEQ_H_
#define _WEEDONG_CORE_SEQ_SEQ_H_

#include <vector>
#include <string>
#include <map>

#include <sstream>
#include <algorithm>
#include <assert.h>

#include <weedong/core/bstream/bstream.h>

namespace wd
{

/*************************************************
  Description:    // ���л����ݻ���
  Other:          // ���е����л��ṹ����̳б�����
*************************************************/
class CSeq
{
public:
    /*************************************************
      Description:    // ���л���������ģʽ
    *************************************************/
    enum ELoopType
    {
        eUnknow = 0,    //������
        eRead = 1,      //���������ж�ȡ����
        eWrite = 2,     //������ע����������
    };

    /*************************************************
      Description:      // ���л����๹�캯��
    *************************************************/
    CSeq();

    /*************************************************
      Description:      // ���л���������������, �����̳�
    *************************************************/
    virtual ~CSeq();

    virtual CSeq* clone(void);
    virtual bool write( wd::CStream &stream );
    virtual bool read( wd::CStream &stream );
    /*************************************************
      Description:      // ���л�����ѭ������ģʽ
      Param:            // stream : �����ö�������
                        // eType : ����ʽ
    *************************************************/
    bool loop( wd::CStream &stream, CSeq::ELoopType eType, uint32& uiSize );
    virtual bool loopend( wd::CStream &stream, CSeq::ELoopType eType, uint32& uiSize );
    
    /*************************************************
      Description:      // ���л�Ԫ���߼�����ģ��
      Param:            // value : Ԫ��ֵ
                        // type : ������ģʽ
                        // stream : ���������ݴ�����
                        // pszVarName : ��������
                        // pszVarDescript : ��������
                        // pszVarType : ����������
    *************************************************/
    template<typename T> static bool TFVarTypeProcess(T& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize)
    {
        uint32 _uiSize = 0;
        uint32 _pos_i = 0;
        uint32 _pos_j = 0;
        bool b_loop = false;
        switch ( type )
        {
        case CSeq::eRead:
            if ( uiSize < sizeof(_uiSize) )
                return false;
            _pos_i = stream.position();
            b_loop = value.loop( stream, type, _uiSize );
            _pos_j = stream.position();
            if ( uiSize > _pos_j - _pos_i)
                uiSize -= _pos_j - _pos_i;
            else
                uiSize = 0;
            return b_loop;
        case CSeq::eWrite:
            _pos_i = stream.position();
            b_loop = value.loop( stream, type, _uiSize );
            _pos_j = stream.position();
            uiSize += _pos_j - _pos_i;
            return b_loop;
        default:
            assert(false);
        }
        return false;
    }
    /*************************************************
      Description:      // ͬ��
      Other:            // �Ի���Ԫ�صĺ�������ʵ��
    *************************************************/
    static bool TFVarTypeProcess(int8& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(uint8& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(int16& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(uint16& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(int32& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(uint32& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(float& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(double& value, CSeq::ELoopType type, wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(std::string& value, CSeq::ELoopType type,wd::CStream &stream, uint32 &uiSize);
    static bool TFVarTypeProcess(wd::CStream& value, CSeq::ELoopType type,wd::CStream &stream, uint32 &uiSize);
    /*************************************************
      Description:      // ͬ��
      Other:            // �� array �ĺ���ģ��ʵ��
    *************************************************/
	struct vector_type_process
	{
		CSeq::ELoopType Type;
		wd::CStream &Stream;
        bool &result;
        uint32 &uiSize;
		vector_type_process( CSeq::ELoopType type, wd::CStream &stream, bool& r, uint32 &s ) : Type(type), Stream(stream), result(r), uiSize(s) {}

		template<typename T> void operator()( T &value )
		{
            if ( result )
			    result = TFVarTypeProcess( value, Type, Stream, uiSize );
		}
	};
    template<typename T> static bool TFVarTypeProcess(std::vector<T>& value, CSeq::ELoopType type,wd::CStream &stream, uint32& uiSize)
    {
        bool result = true;
        uint16 uiLength = 0;
        switch ( type )
        {
        case CSeq::eRead:
            {
                stream >> uiLength;
                if ( uiSize < sizeof( uiLength ) )
                    return false;
                uiSize -= sizeof( uiLength );

                value.clear();
                if ( uiLength > 0 )
                {
                    value.resize( uiLength );

                    vector_type_process process( type, stream, result, uiSize );
					std::for_each( value.begin(), value.end(), process );
                }
            }
            break;
        case CSeq::eWrite:
            {
                uiLength = (uint16)value.size();
                stream << uiLength;
                uiSize += sizeof( uiLength );

                if ( uiLength > 0 )
                {
                    vector_type_process process( type, stream, result, uiSize );
					std::for_each( value.begin(), value.end(), process );
                }
            }
            break;
        default:
            assert(false);
        }

        return result;
    }
    /*************************************************
      Description:      // ͬ��
      Other:            // �� map �ĺ���ģ��ʵ��
    *************************************************/
	struct map_type_process
	{
		CSeq::ELoopType Type;
		wd::CStream &Stream;
        bool &result;
        uint32 &uiSize;

		map_type_process( CSeq::ELoopType type, wd::CStream &stream, bool& r, uint32 &s ) : Type(type), Stream(stream), result(r), uiSize(s){}

		template<typename T> void operator()( T& value )
		{
            if ( result )
            {
			    uint16 uiStrLength = (uint16)value.first.length();
                Stream << uiStrLength;
			    Stream << value.first;
                uiSize += sizeof( uiStrLength ) + uiStrLength;

                result = TFVarTypeProcess( value.second, Type, Stream, uiSize );
            }
		}
	};
    template<typename T> static bool TFVarTypeProcess(std::map<std::string, T>& value, CSeq::ELoopType type,wd::CStream &stream, uint32& uiSize)
    {
        bool result = true;

        std::string strKey;
        uint16 uiMapLength = 0;
        uint16 uiStrLength = 0;

        switch ( type )
        {
        case CSeq::eRead:
            {
                stream >> uiMapLength;
                if ( uiSize < sizeof( uiMapLength ) )
                    return false;
                uiSize -= sizeof( uiMapLength );

                value.clear();
                for ( int i=0; i<uiMapLength; ++i )
                {
                    stream >> uiStrLength;
                    stream.read( strKey, uiStrLength );
                    if ( uiSize < sizeof(uiStrLength) + uiStrLength )
                        return false;
                    uiSize -= sizeof(uiStrLength) + uiStrLength;
                    if ( !TFVarTypeProcess( value[ strKey.c_str() ], type, stream, uiSize ) )
                        return false;
                }
            }
            break;
        case CSeq::eWrite:
            {
                uiMapLength = (uint16)value.size();
                stream << uiMapLength;
                uiSize += sizeof(uiMapLength);

                if ( uiMapLength > 0 )
                {
                    map_type_process process( type, stream, result, uiSize );
					std::for_each( value.begin(), value.end(), process );
                }
            }
            break;
        default:
            assert(false);
        }
        return result;
    }
    /*************************************************
      Description:      // ͬ��
      Other:            // �� indices �ĺ���ģ��ʵ��
    *************************************************/
	struct indices_type_process
	{
		CSeq::ELoopType Type;
		wd::CStream &Stream;
        bool &result;
        uint32 &uiSize;

	    indices_type_process( CSeq::ELoopType type, wd::CStream &stream, bool& r, uint32& s ) : Type(type), Stream(stream), result(r), uiSize(s){}

		template<typename T> void operator()( T &value )
		{
            if ( result )
            {
			    Stream << value.first;
                uiSize += sizeof( value.first );

                result = TFVarTypeProcess( value.second, Type, Stream, uiSize );
            }
		}
	};
    template<typename T> static bool TFVarTypeProcess(std::map<uint32, T>& value, CSeq::ELoopType type,wd::CStream &stream, uint32& uiSize )
    {
        bool result = true;

        uint16 uiIndicesLength = 0;
        uint32 uiIndicesKey = 0;

        switch ( type )
        {
        case CSeq::eRead:
            {
                stream >> uiIndicesLength;
                if ( uiSize < sizeof( uiIndicesLength ) )
                    return false;
                uiSize -= sizeof( uiIndicesLength );

                value.clear();
                for ( int i=0; i<uiIndicesLength; ++i )
                {
                    stream >> uiIndicesKey;
                    if ( uiSize < sizeof( uiIndicesKey ) )
                        return false;
                        uiSize -= sizeof( uiIndicesKey );
                    if ( !TFVarTypeProcess( value[ uiIndicesKey ], type, stream, uiSize ) )
                        return false;
                }
            }
            break;
        case CSeq::eWrite:
            {
                uiIndicesLength = (uint16)value.size();
                stream << uiIndicesLength;
                uiSize += sizeof( uiIndicesLength );

                if ( uiIndicesLength > 0 )
                {
                    indices_type_process process( type, stream, result, uiSize );
                    std::for_each( value.begin(), value.end(), process );
                }
            }
            break;
        default:
            assert(false);
        }
        return result;
    }
    /*************************************************
      Description:      // ͬ��
      Other:            // �� indices �ĺ���ģ��ʵ��
    *************************************************/
	struct indices_type_process_p
	{
		CSeq::ELoopType Type;
		wd::CStream &Stream;
        bool &result;
        uint32 &uiSize;

	    indices_type_process_p( CSeq::ELoopType type, wd::CStream &stream, bool& r, uint32& s ) : Type(type), Stream(stream), result(r), uiSize(s){}

		template<typename T> void operator()( T &value )
		{
            if ( result )
            {
			    Stream << value.first;
                uiSize += sizeof( value.first );

                result = TFVarTypeProcess( *(value.second), Type, Stream, uiSize );
            }
		}
	};
    template<typename T> static bool TFVarTypeProcess(std::map<uint32, T*>& value, CSeq::ELoopType type,wd::CStream &stream, uint32& uiSize )
    {
        bool result = true;

        uint16 uiIndicesLength = 0;
        uint32 uiIndicesKey = 0;

        switch ( type )
        {
        case CSeq::eRead:
            {
                stream >> uiIndicesLength;
                if ( uiSize < sizeof( uiIndicesLength ) )
                    return false;
                uiSize -= sizeof( uiIndicesLength );

                value.clear();
                for ( int i=0; i<uiIndicesLength; ++i )
                {
                    stream >> uiIndicesKey;
                    if ( uiSize < sizeof( uiIndicesKey ) )
                        return false;
                        uiSize -= sizeof( uiIndicesKey );
                    T *pt = new T();
                    value[ uiIndicesKey ] = pt;
                    if ( !TFVarTypeProcess( *pt, type, stream, uiSize ) )
                        return false;
                }
            }
            break;
        case CSeq::eWrite:
            {
                uiIndicesLength = (uint16)value.size();
                stream << uiIndicesLength;
                uiSize += sizeof( uiIndicesLength );

                if ( uiIndicesLength > 0 )
                {
                    indices_type_process_p process( type, stream, result, uiSize );
                    std::for_each( value.begin(), value.end(), process );
                }
            }
            break;
        default:
            assert(false);
        }
        return result;
    }
};

}

#endif

