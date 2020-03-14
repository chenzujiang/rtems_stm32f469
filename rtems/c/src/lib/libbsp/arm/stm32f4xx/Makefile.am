ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

################################################################################
# Data                                                                         #
################################################################################

noinst_LIBRARIES = libbspstart.a

libbspstart_a_SOURCES = ../shared/start/start.S

project_lib_DATA =
project_lib_DATA += start.$(OBJEXT)
project_lib_DATA += startup/linkcmds

EXTRA_DIST = startup/linkcmds.stm32f4xx

################################################################################
# Header                                                                       #
################################################################################

include_HEADERS =
include_HEADERS += include/bsp.h
include_HEADERS += ../../shared/include/tm27.h

nodist_include_HEADERS =
nodist_include_HEADERS += ../../shared/include/coverhd.h
nodist_include_HEADERS += include/bspopts.h

nodist_include_bsp_HEADERS =
nodist_include_bsp_HEADERS += ../../shared/include/bootcard.h

include_bsp_HEADERS =
include_bsp_HEADERS += ../../shared/include/utility.h
include_bsp_HEADERS += ../../shared/include/irq-generic.h
include_bsp_HEADERS += ../../shared/include/irq-info.h
include_bsp_HEADERS += ../../shared/include/stackalloc.h
include_bsp_HEADERS += ../shared/include/start.h
include_bsp_HEADERS += ../shared/armv7m/include/armv7m-irq.h
include_bsp_HEADERS += include/irq.h
include_bsp_HEADERS += include/uart.h
include_bsp_HEADERS += include/io.h
include_bsp_HEADERS += include/gpio.h
include_bsp_HEADERS += include/i2c.h

include_bsp_HEADERS += include/bsp_i2c_ee.h
#keyboard
include_bsp_HEADERS += include/keyboard.h
include_bsp_HEADERS += include/hal_exti.h
#spi
include_bsp_HEADERS += include/spi.h
include_bsp_HEADERS += include/hal_spi.h
include_bsp_HEADERS += include/bsp_spi_flash.h

################################################################################
# LibBSP                                                                       #
################################################################################

noinst_LIBRARIES += libbsp.a

libbsp_a_SOURCES =
libbsp_a_CPPFLAGS =
libbsp_a_LIBADD =

# Shared
libbsp_a_SOURCES += ../../shared/bootcard.c
libbsp_a_SOURCES += ../../shared/bspclean.c
libbsp_a_SOURCES += ../../shared/bspgetworkarea.c
libbsp_a_SOURCES += ../../shared/bsplibc.c
libbsp_a_SOURCES += ../../shared/bsppost.c
libbsp_a_SOURCES += ../../shared/bsppredriverhook.c
libbsp_a_SOURCES += ../../shared/bsppretaskinghook.c
libbsp_a_SOURCES += ../../shared/cpucounterread.c
libbsp_a_SOURCES += ../../shared/cpucounterdiff.c
libbsp_a_SOURCES += ../../shared/gnatinstallhandler.c
libbsp_a_SOURCES += ../../shared/sbrk.c
libbsp_a_SOURCES += ../../shared/src/stackalloc.c

# Startup
libbsp_a_SOURCES += ../shared/startup/bsp-start-memcpy.S
libbsp_a_SOURCES += startup/bspstart.c
libbsp_a_SOURCES += startup/bspstarthook.c
libbsp_a_SOURCES += startup/bspreset.c
libbsp_a_SOURCES += startup/io.c
libbsp_a_SOURCES += startup/start-config-mpu.c

# IRQ
libbsp_a_SOURCES += ../../shared/src/irq-default-handler.c
libbsp_a_SOURCES += ../../shared/src/irq-generic.c
libbsp_a_SOURCES += ../../shared/src/irq-info.c
libbsp_a_SOURCES += ../../shared/src/irq-legacy.c
libbsp_a_SOURCES += ../../shared/src/irq-server.c
libbsp_a_SOURCES += ../../shared/src/irq-shell.c
libbsp_a_SOURCES += ../shared/armv7m/irq/armv7m-irq.c
libbsp_a_SOURCES += ../shared/armv7m/irq/armv7m-irq-dispatch.c

# Console
libbsp_a_SOURCES += ../../shared/console.c
libbsp_a_SOURCES += ../../shared/console_control.c
libbsp_a_SOURCES += ../../shared/console_read.c
libbsp_a_SOURCES += ../../shared/console_select.c
libbsp_a_SOURCES += ../../shared/console_write.c
libbsp_a_SOURCES += console/console-config.c
libbsp_a_SOURCES += console/uart.c

# Clock
libbsp_a_SOURCES += ../../shared/clockdrv_shell.h
libbsp_a_SOURCES += ../shared/armv7m/clock/armv7m-clock-config.c

# Timer
libbsp_a_SOURCES += ../../shared/timerstub.c

# gpio
libbsp_a_SOURCES += ../../shared/led-drv.c
libbsp_a_SOURCES += gpio/gpio-config.c
libbsp_a_SOURCES += gpio/gpio.c
# stm32f4xx i2c
libbsp_a_SOURCES += ../../shared/i2c-drv.c
libbsp_a_SOURCES += i2c/i2c-config.c
libbsp_a_SOURCES += i2c/stm32f4xx-i2c.c
libbsp_a_SOURCES += i2c/bsp_i2c_ee.c
# stm32f4xx exti
libbsp_a_SOURCES += keyboard/exti-config.c
libbsp_a_SOURCES += keyboard/keyboard.c
libbsp_a_SOURCES += keyboard/stm32f4xx-exti.c
# stm32f4xx spi
libbsp_a_SOURCES += spi/spi-config.c
libbsp_a_SOURCES += spi/spi.c
libbsp_a_SOURCES += spi/stm32f4xx-spi.c
libbsp_a_SOURCES += spi/bsp_spi_flash.c

# Cache
libbsp_a_SOURCES += ../../../libcpu/shared/src/cache_manager.c
libbsp_a_SOURCES += ../../../libcpu/arm/shared/cache/cache_.h
libbsp_a_CPPFLAGS += -I$(srcdir)/../../../libcpu/arm/shared/include

# BSP Special
libbsp_a_CPPFLAGS += -I$(srcdir)/library/CMSIS/Include
libbsp_a_CPPFLAGS += -I$(srcdir)/library/STM32F4xx_StdPeriph_Driver/inc
libbsp_a_CPPFLAGS += -I$(srcdir)/library/Board_Special
libbsp_a_CPPFLAGS += -I$(srcdir)/library/QSPI
libbsp_a_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/inc
libbsp_a_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/user_driver/inc
libbsp_a_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/Common/inc

# littlevGL
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/I2C
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lv_examples/lv_tests/lv_test_theme
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lv_examples/lv_apps/demo
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lv-app
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-core
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-draw
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-hal
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-misc
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv_fonts
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-objx
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-themes
libbsp_a_CPPFLAGS += -I$(srcdir)/littlevGL/tim
################################################################################
# LibSTM32F4XX && littlevGL                                                            #
################################################################################

noinst_PROGRAMS = stm32f4xx.rel
noinst_PROGRAMS += stm32f4xxgui.rel

include_stm32f4xxdir = $(include_bspdir)/library
include_stm32f4xxguidir = $(include_bspdir)/littlevGL

stm32f4xx_rel_CPPFLAGS =
stm32f4xx_rel_LDFLAGS =
include_stm32f4xx_HEADERS =

stm32f4xxgui_rel_CPPFLAGS =
stm32f4xxgui_rel_LDFLAGS =
include_stm32f4xxgui_HEADERS =

# CMSIS
include_stm32f4xx_HEADERS += library/CMSIS/Include/core_cm4.h
include_stm32f4xx_HEADERS += library/CMSIS/Include/core_cmFunc.h
include_stm32f4xx_HEADERS += library/CMSIS/Include/core_cmInstr.h
include_stm32f4xx_HEADERS += library/CMSIS/Include/core_cmSimd.h
# CMSIS Device
include_stm32f4xx_HEADERS += library/CMSIS/Include/stm32f4xx.h

# STM32F4xx_StdPeriph_Driver - Common
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/misc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h

stm32f4xx_rel_SOURCES = library/STM32F4xx_StdPeriph_Driver/src/misc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

# STM32F4xx_StdPeriph_Driver - STM32F429_439xx
if STM32F4XX_FAMILY_STM32F429_439xx
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma2d.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fmc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_ltdc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sai.h

stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
endif
# STM32F4xx_StdPeriph_Driver - STM32F469_479xx
if STM32F4XX_FAMILY_STM32F469_479xx
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma2d.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fmc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_ltdc.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sai.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_qspi.h
include_stm32f4xx_HEADERS += library/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dsi.h

stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
stm32f4xx_rel_SOURCES += library/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c
endif
#tim
include_stm32f4xxgui_HEADERS += littlevGL/tim/bsp_general_tim.h
stm32f4xxgui_rel_SOURCES  = littlevGL/tim/bsp_general_tim.c
#lv_examples
include_stm32f4xxgui_HEADERS += littlevGL/lv_examples/lv_tests/lv_test_theme/lv_test_theme.h
include_stm32f4xxgui_HEADERS += littlevGL/lv_examples/lv_apps/demo/demo.h

stm32f4xxgui_rel_SOURCES  += littlevGL/lv_examples/lv_tests/lv_test_theme/lv_test_theme.c
stm32f4xxgui_rel_SOURCES  += littlevGL/lv_examples/lv_apps/demo/demo.c
stm32f4xxgui_rel_SOURCES  += littlevGL/lv_examples/lv_apps/demo/img_bubble_pattern.c
#lv-app
include_stm32f4xxgui_HEADERS += littlevGL/lv-app/lv_tft.h
include_stm32f4xxgui_HEADERS += littlevGL/lv-app/lv_touchpad.h
stm32f4xxgui_rel_SOURCES  += littlevGL/lv-app/lv_tft.c
stm32f4xxgui_rel_SOURCES  += littlevGL/lv-app/lv_touchpad.c
#######
include_stm32f4xxgui_HEADERS += littlevGL/lv_conf.h
include_stm32f4xxgui_HEADERS += littlevGL/lv_ex_conf.h
#lvgl-5.1
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lvgl.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_conf_templ.h
#lvgl-5.1/lv_core
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_group.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_indev.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_obj.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_refr.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_style.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_core/lv_vdb.h
#lvgl-5.1/lv_draw
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_draw/lv_draw_rbasic.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_draw/lv_draw_vbasic.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_draw/lv_draw.h
#lvgl-5.1/lv_hal
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_hal/lv_hal_disp.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_hal/lv_hal_indev.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_hal/lv_hal_tick.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_hal/lv_hal.h
#lvgl-5.1/lv_misc
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_anim.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_area.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_circ.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_color.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_font.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_fs.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_ll.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_math.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_mem.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_task.c
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_templ.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_trigo.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_txt.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_ufs.h
#lvgl-5.1/lv_misc/lv_fonts
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_symbol_def.h
#lvgl-5.1/lv_objx
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_bar.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_btn.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_btnm.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_cb.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_chart.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_cont.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_ddlist.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_gauge.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_img.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_kb.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_label.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_led.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_line.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_list.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_lmeter.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_mbox.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_objx_templ.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_page.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_roller.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_slider.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_sw.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_ta.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_tabview.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_objx/lv_win.h
#lvgl-5.1/lv_themes
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_alien.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_default.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_material.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_mono.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_night.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_templ.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme_zen.h
include_stm32f4xxgui_HEADERS += littlevGL/lvgl-5.1/lv_themes/lv_theme.h
#lvgl-5.1/lv_core
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_group.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_indev.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_obj.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_refr.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_style.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_core/lv_vdb.c
#lvgl-5.1/lv_draw
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_draw/lv_draw_rbasic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_draw/lv_draw_vbasic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_draw/lv_draw.c
#lvgl-5.1/lv_hal
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_hal/lv_hal_disp.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_hal/lv_hal_indev.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_hal/lv_hal_tick.c
#lvgl-5.1/lv_misc
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_anim.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_area.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_circ.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_color.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_font.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fs.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_ll.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_math.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_mem.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_task.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_templ.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_trigo.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_txt.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_ufs.c
#lvgl-5.1/lv_misc/lv_fonts
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_10_cyrillic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_10_latin_sup.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_10.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_20_cyrillic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_20_latin_sup.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_20.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_30_cyrillic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_30_latin_sup.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_30.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_40_cyrillic.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_40_latin_sup.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_dejavu_40.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_symbol_10.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_symbol_20.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_symbol_30.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_misc/lv_fonts/lv_font_symbol_40.c
#lvgl-5.1/lv_objx
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_bar.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_btn.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_btnm.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_cb.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_chart.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_cont.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_ddlist.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_gauge.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_img.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_kb.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_label.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_led.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_line.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_list.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_lmeter.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_mbox.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_objx_templ.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_page.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_roller.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_slider.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_sw.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_ta.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_tabview.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_objx/lv_win.c
#lvgl-5.1/lv_themes
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_alien.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_default.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_material.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_mono.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_night.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_templ.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme_zen.c
stm32f4xxgui_rel_SOURCES += littlevGL/lvgl-5.1/lv_themes/lv_theme.c
#I2C
include_stm32f4xxgui_HEADERS += littlevGL/I2C/BSP_FT6206.h
include_stm32f4xxgui_HEADERS += littlevGL/I2C/BSP_I2C.h
stm32f4xxgui_rel_SOURCES += littlevGL/I2C/BSP_FT6206.c
stm32f4xxgui_rel_SOURCES += littlevGL/I2C/BSP_I2C.c

# Board Special
include_stm32f4xx_HEADERS += library/Board_Special/stm32f4xx_conf.h
include_stm32f4xx_HEADERS += library/Board_Special/stm32f4xx_driver_conf.h
include_stm32f4xx_HEADERS += library/Board_Special/stm32f4xx_it.h
include_stm32f4xx_HEADERS += library/Board_Special/system_stm32f4xx.h
stm32f4xx_rel_SOURCES += library/Board_Special/system_stm32f4xx_default.c
stm32f4xx_rel_SOURCES += library/Board_Special/stm32f4xx_it.c

#STM324x9I_EVAL
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm324x9i_eval_fmc_sdram.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm324x9i_eval_sdio_sd.h
#include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm324x9i_eval.h

include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm324x9i_eval_ioe8.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm324x9i_eval_lcd.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/otm8009a.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/ft6x06.h

#include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm32469i_discovery.h
#include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/inc/stm32469i_discovery_ts.h

stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm324x9i_eval_fmc_sdram.c
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm324x9i_eval_sdio_sd.c
#stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm324x9i_eval.c

stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm324x9i_eval_ioe8.c
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm324x9i_eval_lcd.c
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/otm8009a.c
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/ft6x06.c
#stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm32469i_discovery.c
#stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/src/stm32469i_discovery_ts.c

# sdcard
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/user_driver/inc/bsp_sdcard.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/user_driver/inc/main.h
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/user_driver/src/bsp_sdcard.c
#common
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/Common/inc/ts.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/Common/inc/stm32_eval_legacy.h
include_stm32f4xx_HEADERS += library/STM324x9I_EVAL/Common/inc/fonts.h
stm32f4xx_rel_SOURCES += library/STM324x9I_EVAL/Common/src/fonts.c
#QSPI
stm32f4xx_rel_SOURCES += library/QSPI/qspi_readwrite_conf.c
include_stm32f4xx_HEADERS += library/QSPI/qspi_readwrite_conf.h

stm32f4xx_rel_CPPFLAGS += $(AM_CPPFLAGS)
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/CMSIS/Include
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/STM32F4xx_StdPeriph_Driver/inc
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/Board_Special
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/QSPI
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/inc
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/user_driver/inc
stm32f4xx_rel_CPPFLAGS += -I$(srcdir)/library/STM324x9I_EVAL/Common/inc
# littlevGL
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/I2C
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lv_examples/lv_tests/lv_test_theme
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lv_examples/lv_apps/demo
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lv-app
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-core
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-draw
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-hal
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-misc
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv_fonts
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-objx
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/lvgl-5.1/lv-themes
stm32f4xxgui_rel_CPPFLAGS += -I$(srcdir)/littlevGL/tim

stm32f4xx_rel_LDFLAGS += $(RTEMS_RELLDFLAGS)
stm32f4xxgui_rel_LDFLAGS += $(RTEMS_RELLDFLAGS)

libbsp_a_LIBADD += stm32f4xx.rel
libbsp_a_LIBADD += stm32f4xxgui.rel
################################################################################
# Special Rules                                                                #
################################################################################

DISTCLEANFILES = include/bspopts.h

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
