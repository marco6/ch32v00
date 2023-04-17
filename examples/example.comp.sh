#!/bin/bash

_chv3200x_example()
{
    local cur prev

    COMPREPLY=()
    cur=${COMP_WORDS[COMP_CWORD]}
    prev=${COMP_WORDS[COMP_CWORD-1]}

    _expand || return 0

    case "$prev" in
    -o)
        _filedir
        return 0
        ;;
    esac

    case "$cur" in
    -*)
        COMPREPLY=( $( compgen -W '-c -o -h --help' -- "$cur" ))
        ;;
    *)  
        COMPREPLY=( $( compgen -W 'pwr/standby_mode pwr/sleep_mode ch32v003 wwdg \
            iwdg flash gpio iap/v00x_app i2c/pec i2c/eeprom i2c/7bit_mode i2c/10bit_mode \
            i2c/dma spi/full-duplex-hard-nss spi/crc spi/half-duplex spi/full-duplex \
            spi/dma systick_interrupt tim/synchro_ext_trigger tim/input_capture \
            tim/synchro_timer tim/pwm tim/output_compare_mode tim/complementary_output_dead_time \
            tim/clock_select tim/one_pulse tim/dma tim/ext_trigger_start_two_timers \
            usart/interrupt usart/hardware_flow_control usart/multi_processor usart/printf \
            usart/synchronous_mode usart/half-duplex usart/polling usart/dma adc/analog_watchdog \
            adc/ext_line_trigger adc/discontinuous_mode adc/auto_injection adc/dma opa exti \
            rcc/get_clk rcc/mco dma' -- "$cur" ))
        ;;
    esac

    return 0
} &&
complete -F _chv3200x_example $nospace $filenames chv3200x.example
