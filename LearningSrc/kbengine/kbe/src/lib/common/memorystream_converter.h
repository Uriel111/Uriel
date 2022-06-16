// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

/*
	�ֽ��򽻻�����ģ�飺
		 ��������ͨ��һ�����BIG�ֽ���\Ҳ���������ֽ���.
		 ����ʹ�õ�PC������Ƕ��ʽϵͳ����ʹ��BIG�ֽ���Ҳ����ʹ��LITTEN(С�ֽ���)
		 �������Ǳ����ڴ�֮����һ���ֽ����ת����
*/
#ifndef KBE_MEMORYSTREAMCONVERTER_H
#define KBE_MEMORYSTREAMCONVERTER_H

#include "common/common.h"

namespace KBEngine
{
	//  扭转字节序的工具   为了网络传输使用
	namespace MemoryStreamConverter
	{
		template <size_t T>
		inline void convert(char *val)
		{
			std::swap(*val, *(val + T - 1));
			convert<T - 2>(val + 1);
		}

		template <>
		inline void convert<0>(char *) {}
		template <>
		inline void convert<1>(char *) {} // ignore central byte

		template <typename T>
		inline void apply(T *val)
		{
			convert<sizeof(T)>((char *)(val));
		}

		inline void convert(char *val, size_t size)
		{
			if (size < 2)
				return;

			std::swap(*val, *(val + size - 1));
			convert(val + 1, size - 2);
		}
	}

#if KBENGINE_ENDIAN == KBENGINE_BIG_ENDIAN // ����ʹ��sys.isPlatformLittleEndian() ���в���
	template <typename T>
	inline void EndianConvert(T &val)
	{
		MemoryStreamConverter::apply<T>(&val);
	}
	template <typename T>
	inline void EndianConvertReverse(T &) {}
#else
	template <typename T>
	inline void EndianConvert(T &)
	{
	}
	template <typename T>
	inline void EndianConvertReverse(T &val) { MemoryStreamConverter::apply<T>(&val); }
#endif

	template <typename T>
	void EndianConvert(T *); // will generate link error
	template <typename T>
	void EndianConvertReverse(T *); // will generate link error

	inline void EndianConvert(uint8 &) {}
	inline void EndianConvert(int8 &) {}
	inline void EndianConvertReverse(uint8 &) {}
	inline void EndianConvertReverse(int8 &) {}

}
#endif
