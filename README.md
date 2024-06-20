# Development Board Arduino Blue Pill STM32
micro STM32F103C8T6


Before begin check microcontroller selection and configuration
------------------------------------------------------------

* work area size y flash image
>stm32f1_flash.cfg

* work area size y flash image
>stm32f1_flash_lock.cfg

* work area size
>stm32f1_gdb.cfg

* work area size
>stm32f1_reset.cfg

* end of ram; stack size; memory lenght
>./startup_src/stm32_flash.ld

* pick clock (xtal o rc)
>./src/hard.h

* pick processor, defines on line 66 stm32f1xx.h -> modif on Makefile
>./src/stm32f1xx.h
>.Makefile

