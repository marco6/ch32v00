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
        COMPREPLY=( $( compgen -W 'OPA RCC/MCO RCC/Get_CLK ADC/Auto_Injection ADC/DMA ADC/AnalogWatchdog ADC/Discontinuous_mode ADC/ExtLines_Trigger USART/Polling USART/Printf USART/DMA USART/Interrupt USART/HalfDuplex USART/SynchronousMode USART/MultiProcessorCommunication USART/HardwareFlowControl DMA TIM/Synchro_ExtTrigger TIM/Synchro_Timer TIM/DMA TIM/ComplementaryOutput_DeadTime TIM/Output_Compare_Mode TIM/Input_Capture TIM/ExtTrigger_Start_Two_Timer TIM/One_Pulse TIM/PWM_Output TIM/Clock_Select EXTI GPIO IWDG SYSTICK_Interrupt CH32V003 SPI/FullDuplex_HardNSS SPI/2Lines_FullDuplex SPI/DMA SPI/CRC SPI/1Lines_half-duplex I2C/DMA I2C/7bit_Mode I2C/EEPROM I2C/10bit_Mode I2C/PEC IAP/V00x_APP FLASH WWDG PWR/Sleep_Mode PWR/Standby_Mode' -- "$cur" ))
        ;;
    esac

    return 0
} &&
complete -F _chv3200x_example $nospace $filenames chv3200x.example
