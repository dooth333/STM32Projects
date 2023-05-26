#ifndef _DMA_H
#define _DMA_H

// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define DMA_CHANNEL DMA1_Channel6
#define DMA_CLOCK RCC_AHBPeriph_DMA1

// 传输完成标志
#define DMA_FLAG_TC DMA1_FLAG_TC6

// 要发送的数据大小
#define BUFFER_SIZE 32

/* 定义 aSRC_Const_Buffer 数组作为 DMA 传输数据源
* const 关键字将 aSRC_Const_Buffer 数组变量定义为常量类型
* 表示数据存储在内部的 FLASH 中
*/

extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
/* 定义 aSRC_Const_Buffer 数组作为 DMA 传输数据源
 * const 关键字将 aSRC_Const_Buffer 数组变量定义为常量类型
 * 表示数据存储在内部的 FLASH 中
 */
extern uint32_t aDST_Buffer[BUFFER_SIZE];

void DMA_Config(void);
 

#endif
