/**
  ******************************************************************************
  * @file    logging.h
  * @brief   Unified logging macros for platform abstraction
  ******************************************************************************
  */

#ifndef ARDUINO_VIDEO_LOGGING_H
#define ARDUINO_VIDEO_LOGGING_H

/* Define ANX_LOG_ENABLE to enable logging (disabled by default) */
// #define ANX_LOG_ENABLE

#if defined(ANX_LOG_ENABLE)

#if defined(__ZEPHYR__)
#include <zephyr/logging/log.h>
#include <stm32h7xx.h>
LOG_MODULE_DECLARE(sketch, LOG_LEVEL_INF);

#define ANX_LOG_ERROR(fmt, ...) LOG_ERR(fmt, ##__VA_ARGS__)
#define ANX_LOG_INFO(fmt, ...)  LOG_INF(fmt, ##__VA_ARGS__)
#define ANX_LOG_DBG(fmt, ...)   LOG_DBG(fmt, ##__VA_ARGS__)

#else /* ARDUINO_ARCH_MBED */
#include <cstdio>
#include <cstdarg>
#include <mbed.h>
#include <stm32h7xx.h>

/* Common logging function for mbed platform */
/* USART6 on PG14 (TX) / PG9 (RX) to match Zephyr console */
inline void anx_log_print(const char *prefix, const char *fmt, ...) {
    static mbed::UnbufferedSerial serial(PG_14, PG_9, 115200);
    char buf[256];
    int len = snprintf(buf, sizeof(buf) - 2, "%s", prefix);
    va_list args;
    va_start(args, fmt);
    len += vsnprintf(buf + len, sizeof(buf) - 2 - len, fmt, args);
    va_end(args);
    buf[len++] = '\r';
    buf[len++] = '\n';
    serial.write(buf, len);
}

#define ANX_LOG_ERROR(fmt, ...) anx_log_print("ANX ERR: ", fmt, ##__VA_ARGS__)
#define ANX_LOG_INFO(fmt, ...)  anx_log_print("ANX INF: ", fmt, ##__VA_ARGS__)
#define ANX_LOG_DBG(fmt, ...)   anx_log_print("ANX DBG: ", fmt, ##__VA_ARGS__)

#endif /* __ZEPHYR__ */

#else /* ANX_LOG_ENABLE not defined - disable all logging */

#define ANX_LOG_ERROR(fmt, ...) do { } while(0)
#define ANX_LOG_INFO(fmt, ...)  do { } while(0)
#define ANX_LOG_DBG(fmt, ...)   do { } while(0)

#endif /* ANX_LOG_ENABLE */

#if defined(ANX_LOG_ENABLE)
/* LTDC Layer register access macro */
#define LTDC_LAYER_REG(idx)  ((LTDC_Layer_TypeDef *)((uint32_t)LTDC + 0x84U + (0x80U * (idx))))

/**
  * @brief  Dump LTDC and DSI registers for debugging
  */
#include <stm32h7xx.h>
static inline void dsi_dump_registers(void) {
    ANX_LOG_DBG("=== LTDC Registers ===");
    ANX_LOG_DBG("LTDC->SSCR  = 0x%08lx (Sync Size)", LTDC->SSCR);
    ANX_LOG_DBG("LTDC->BPCR  = 0x%08lx (Back Porch)", LTDC->BPCR);
    ANX_LOG_DBG("LTDC->AWCR  = 0x%08lx (Active Width)", LTDC->AWCR);
    ANX_LOG_DBG("LTDC->TWCR  = 0x%08lx (Total Width)", LTDC->TWCR);
    ANX_LOG_DBG("LTDC->GCR   = 0x%08lx (Global Control)", LTDC->GCR);
    ANX_LOG_DBG("LTDC->SRCR  = 0x%08lx (Shadow Reload)", LTDC->SRCR);
    ANX_LOG_DBG("LTDC->BCCR  = 0x%08lx (Background Color)", LTDC->BCCR);
    ANX_LOG_DBG("LTDC->IER   = 0x%08lx (Interrupt Enable)", LTDC->IER);
    ANX_LOG_DBG("LTDC->ISR   = 0x%08lx (Interrupt Status)", LTDC->ISR);
    ANX_LOG_DBG("LTDC->CDSR  = 0x%08lx (Current Display Status)", LTDC->CDSR);

    ANX_LOG_DBG("=== LTDC Layer 0 ===");
    LTDC_Layer_TypeDef *layer0 = LTDC_LAYER_REG(0);
    ANX_LOG_DBG("L0->CR      = 0x%08lx (Control)", layer0->CR);
    ANX_LOG_DBG("L0->WHPCR   = 0x%08lx (Window H Pos)", layer0->WHPCR);
    ANX_LOG_DBG("L0->WVPCR   = 0x%08lx (Window V Pos)", layer0->WVPCR);
    ANX_LOG_DBG("L0->PFCR    = 0x%08lx (Pixel Format)", layer0->PFCR);
    ANX_LOG_DBG("L0->CACR    = 0x%08lx (Constant Alpha)", layer0->CACR);
    ANX_LOG_DBG("L0->BFCR    = 0x%08lx (Blending Factors)", layer0->BFCR);
    ANX_LOG_DBG("L0->CFBAR   = 0x%08lx (FB Address)", layer0->CFBAR);
    ANX_LOG_DBG("L0->CFBLR   = 0x%08lx (FB Line Length)", layer0->CFBLR);
    ANX_LOG_DBG("L0->CFBLNR  = 0x%08lx (FB Line Number)", layer0->CFBLNR);

    ANX_LOG_DBG("=== DSI Registers ===");
    ANX_LOG_DBG("DSI->VR     = 0x%08lx (Version)", DSI->VR);
    ANX_LOG_DBG("DSI->CR     = 0x%08lx (Control)", DSI->CR);
    ANX_LOG_DBG("DSI->CCR    = 0x%08lx (Clock Control)", DSI->CCR);
    ANX_LOG_DBG("DSI->LVCIDR = 0x%08lx (LTDC VCID)", DSI->LVCIDR);
    ANX_LOG_DBG("DSI->LCOLCR = 0x%08lx (LTDC Color Coding)", DSI->LCOLCR);
    ANX_LOG_DBG("DSI->LPCR   = 0x%08lx (LTDC Polarity)", DSI->LPCR);
    ANX_LOG_DBG("DSI->LPMCR  = 0x%08lx (LTDC LP Mode)", DSI->LPMCR);
    ANX_LOG_DBG("DSI->PCR    = 0x%08lx (Protocol Config)", DSI->PCR);
    ANX_LOG_DBG("DSI->VMCR   = 0x%08lx (Video Mode Config)", DSI->VMCR);
    ANX_LOG_DBG("DSI->VPCR   = 0x%08lx (Video Packet Config)", DSI->VPCR);
    ANX_LOG_DBG("DSI->VCCR   = 0x%08lx (Video Chunks Config)", DSI->VCCR);
    ANX_LOG_DBG("DSI->VNPCR  = 0x%08lx (Video Null Packet)", DSI->VNPCR);
    ANX_LOG_DBG("DSI->VHSACR = 0x%08lx (Video HSA Config)", DSI->VHSACR);
    ANX_LOG_DBG("DSI->VHBPCR = 0x%08lx (Video HBP Config)", DSI->VHBPCR);
    ANX_LOG_DBG("DSI->VLCR   = 0x%08lx (Video Line Config)", DSI->VLCR);
    ANX_LOG_DBG("DSI->VVSACR = 0x%08lx (Video VSA Config)", DSI->VVSACR);
    ANX_LOG_DBG("DSI->VVBPCR = 0x%08lx (Video VBP Config)", DSI->VVBPCR);
    ANX_LOG_DBG("DSI->VVFPCR = 0x%08lx (Video VFP Config)", DSI->VVFPCR);
    ANX_LOG_DBG("DSI->VVACR  = 0x%08lx (Video VA Config)", DSI->VVACR);
    ANX_LOG_DBG("DSI->LCCR   = 0x%08lx (LP Command Config)", DSI->LCCR);
    ANX_LOG_DBG("DSI->CMCR   = 0x%08lx (Command Mode Config)", DSI->CMCR);
    ANX_LOG_DBG("DSI->GHCR   = 0x%08lx (Generic Header Config)", DSI->GHCR);
    ANX_LOG_DBG("DSI->GPDR   = 0x%08lx (Generic Payload Data)", DSI->GPDR);
    ANX_LOG_DBG("DSI->GPSR   = 0x%08lx (Generic Packet Status)", DSI->GPSR);
    ANX_LOG_DBG("DSI->TCCR0  = 0x%08lx (Timeout Counter 0)", DSI->TCCR[0]);
    ANX_LOG_DBG("DSI->CLCR   = 0x%08lx (Clock Lane Config)", DSI->CLCR);
    ANX_LOG_DBG("DSI->CLTCR  = 0x%08lx (Clock Lane Timer)", DSI->CLTCR);
    ANX_LOG_DBG("DSI->DLTCR  = 0x%08lx (Data Lane Timer)", DSI->DLTCR);
    ANX_LOG_DBG("DSI->PCTLR  = 0x%08lx (PHY Control)", DSI->PCTLR);
    ANX_LOG_DBG("DSI->PCONFR = 0x%08lx (PHY Config)", DSI->PCONFR);
    ANX_LOG_DBG("DSI->PUCR   = 0x%08lx (PHY ULPS Control)", DSI->PUCR);
    ANX_LOG_DBG("DSI->PTTCR  = 0x%08lx (PHY TX Triggers)", DSI->PTTCR);
    ANX_LOG_DBG("DSI->PSR    = 0x%08lx (PHY Status)", DSI->PSR);
    ANX_LOG_DBG("DSI->WRPCR  = 0x%08lx (Wrapper PLL Control)", DSI->WRPCR);
    ANX_LOG_DBG("DSI->WCR    = 0x%08lx (Wrapper Control)", DSI->WCR);
    ANX_LOG_DBG("DSI->WIER   = 0x%08lx (Wrapper Int Enable)", DSI->WIER);
    ANX_LOG_DBG("DSI->WISR   = 0x%08lx (Wrapper Int Status)", DSI->WISR);
    ANX_LOG_DBG("=== End Register Dump ===");
}
#endif /* ANX_LOG_ENABLE */

#endif /* ARDUINO_VIDEO_LOGGING_H */
