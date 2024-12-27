.globl tss_flush
.text
tss_flush:
	movw $0x2b, %ax
	ltr %ax
	ret
