.globl __stack_top
.globl __stack_bottom

.section .bss
.align 16

__stack_bottom:
.fill 1024 * 16
__stack_top:
