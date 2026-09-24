ENTRY(main)

SECTIONS {
    .sc (0x0) : {
        *(.text.main)
        *(.text .text.*)
        *(.rodata .rodata.*)
        *(.data .data.*)
        *(.bss .bss.*)
    }

    /DISCARD/ : {
        *(.eh_frame*)
        *(.comment)
        *(.note*)
        *(.init_array*)
    }
}
