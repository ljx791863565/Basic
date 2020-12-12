#ifndef MUDUO_ENDIAN_H
#define MUDUO_ENDIAN_H

#include <stdint.h>
#include <endian.h>

namespace nuduo {
namespace net {
namespace sockets {
	
#pragma GCC diagnostic push
// GCC编译器禁用警告
#pragma GCC diagnostic ignored "-Wconversion"
// retain cycle 避免循环引用 
// A和B两个对象，A持有B，B同时也持有A，A只有B释放之后才有可能释放
// 同样B只有A释放后才可能释放，当双方都在等待对方释放的时候
// retain cycle就形成了，结果是，两个对象都永远不会被释放，最终内存泄露。
#pragma GCC diagnostic ignored "-Warc-retain-cycles"	

inline uint64_t hostToNetwork64(uint64_t host64)
{
	return htobe64(host64);
}

inline uint32_t hostToNetwork32(uint32_t host32)
{
	return htobe32(host32);
}

inline uint16_t hostToNetwork16(uint16_t host16)
{
	return htobe16(host16);
}

inline uint64_t networkToHost64(uint64_t net64)
{
	return be64toh(net64);
}

inline uint32_t networkToHost32(uint64_t net32)
{
	return be32toh(net32);
}

inline uint16_t networkToHost16(uint16_t net16)
{
	return be16toh(net16);
}
#pragma GCC diagnostic pop
} /* namespace sockets */
} /* namespace net */
} /* namespace nuduo */
#endif /* end of :MUDUO_ENDIAN_H */
