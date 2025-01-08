/*
	Permission to use, copy, modify, and/or distribute this software for
	any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
	FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
	DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
	AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
	OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
	AUTHOR: gimura2022 <gimura0001@gmail.com>
	FILE  : sys/faluts.c

	processor errors realisation
*/

#include <vnix/faluts.h>
#include <vnix/halt.h>
#include <vnix/vga.h>
#include <vnix/panic.h>
#include <vnix/interrput.h>

static void critical_falut_handler(const char* messange);

#define pub_falut(func, msg) \
	void falut_##func##_falut(struct isr_data* regs) { critical_falut_handler( \
			"Kernel recived " msg " falut!\n"); }

#define falut(func, msg) static pub_falut(func, msg)

pub_falut(double             , "double");
pub_falut(general_protection , "general protection");

falut(division_by_zero              , "division by zero");
falut(debug                         , "debug");
falut(non_mascable_interrput        , "non mascable interrput");
falut(breakpoint                    , "breakpoint");
falut(owerflow                      , "owerflow");
falut(bound_range                   , "bound range");
falut(invalid_opcode                , "invalid opcode");
falut(coprocessor_segment_ovwrrun   , "coprocessor segment ovwrrun");
falut(device_not_avalidable         , "device not avalidable");
falut(invalid_tss                   , "invalid tss");
falut(segment_not_present           , "segment not present");
falut(stack_segment_falut           , "stack segment");
falut(page_falut                    , "page");
falut(x87_floating_point_exeption   , "x87 floating point exeption");
falut(alignment_check               , "alignment check");
falut(machine_check                 , "machine check");
falut(simd_floating_point_exeption  , "SIMD floating point exeption");
falut(virtualization_exeption       , "virtualization exeption");
falut(constrol_protection_exeption  , "constrol protection exeption");
falut(hupervisor_injection_exeption , "hupervisor injection exeption");
falut(vmm_communication_exeption    , "vmm communication exeption");
falut(security_exeption             , "security exeption");

falut(reserved, "reserved");

#undef falut

void falut_setup_faluts(void)
{
#	define falut(num, func) interrput_set(num, falut_##func##_falut)
	
	falut(0, division_by_zero);
	falut(1, debug);
	falut(2, non_mascable_interrput);
	falut(3, breakpoint);
	falut(4, owerflow);
	falut(5, bound_range);
	falut(6, invalid_opcode);
	falut(7, device_not_avalidable);
	falut(9, coprocessor_segment_ovwrrun);
	falut(10, invalid_tss);
	falut(11, segment_not_present);
	falut(12, stack_segment_falut);
	falut(14, page_falut);

	falut(15, reserved);

	falut(16, x87_floating_point_exeption);
	falut(17, alignment_check);
	falut(18, machine_check);
	falut(19, simd_floating_point_exeption);
	falut(20, virtualization_exeption);
	falut(21, constrol_protection_exeption);

	falut(22, reserved);
	falut(23, reserved);
	falut(24, reserved);
	falut(25, reserved);
	falut(26, reserved);
	falut(27, reserved);

	falut(28, hupervisor_injection_exeption);
	falut(29, vmm_communication_exeption);
	falut(30, security_exeption);

	falut(31, reserved);

#	undef falut
}

static void critical_falut_handler(const char* messange)
{
	interrput_disable();
	panic(messange);
}
