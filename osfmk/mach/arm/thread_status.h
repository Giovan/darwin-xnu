/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * FILE_ID: thread_status.h
 */


#ifndef _ARM_THREAD_STATUS_H_
#define _ARM_THREAD_STATUS_H_

#include <mach/machine/_structs.h>
#include <mach/message.h>
#include <mach/arm/thread_state.h>

/*
 *    Support for determining the state of a thread
 */


/*
 *  Flavors
 */

#define ARM_THREAD_STATE		1
#define ARM_UNIFIED_THREAD_STATE ARM_THREAD_STATE
#define ARM_VFP_STATE			2
#define ARM_EXCEPTION_STATE		3
#define ARM_DEBUG_STATE			4 /* pre-armv8 */
#define THREAD_STATE_NONE		5
#define ARM_THREAD_STATE64		6
#define ARM_EXCEPTION_STATE64	7
// ARM_THREAD_STATE_LAST (legacy) 8
#define ARM_THREAD_STATE32		9

/* API */
#define ARM_DEBUG_STATE32		14
#define ARM_DEBUG_STATE64		15
#define ARM_NEON_STATE			16
#define ARM_NEON_STATE64		17
#define ARM_CPMU_STATE64		18

#ifdef XNU_KERNEL_PRIVATE
/* For kernel use */
#define ARM_SAVED_STATE32		20
#define ARM_SAVED_STATE64		21
#define ARM_NEON_SAVED_STATE32	22
#define ARM_NEON_SAVED_STATE64	23
#endif /* XNU_KERNEL_PRIVATE */

#define VALID_THREAD_STATE_FLAVOR(x)\
((x == ARM_THREAD_STATE) 		||	\
 (x == ARM_VFP_STATE) 			||	\
 (x == ARM_EXCEPTION_STATE) 	||	\
 (x == ARM_DEBUG_STATE) 		||	\
 (x == THREAD_STATE_NONE)		||  \
 (x == ARM_THREAD_STATE32)		||	\
 (x == ARM_THREAD_STATE64)		||	\
 (x == ARM_EXCEPTION_STATE64)	||	\
 (x == ARM_NEON_STATE)		||	\
 (x == ARM_NEON_STATE64)		||	\
 (x == ARM_DEBUG_STATE32) 		||	\
 (x == ARM_DEBUG_STATE64))

struct arm_state_hdr {
    uint32_t flavor;
    uint32_t count;
};
typedef struct arm_state_hdr arm_state_hdr_t;

typedef _STRUCT_ARM_THREAD_STATE		arm_thread_state_t;
typedef _STRUCT_ARM_THREAD_STATE		arm_thread_state32_t;
typedef _STRUCT_ARM_THREAD_STATE64		arm_thread_state64_t;

#if !defined(KERNEL)
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL && defined(__arm64__)
#define arm_thread_state64_get_pc(ts) \
		__darwin_arm_thread_state64_get_pc(ts)
#define arm_thread_state64_get_pc_fptr(ts) \
		__darwin_arm_thread_state64_get_pc_fptr(ts)
#define arm_thread_state64_set_pc_fptr(ts, fptr) \
		__darwin_arm_thread_state64_set_pc_fptr(ts, fptr)
#define arm_thread_state64_get_lr(ts) \
		__darwin_arm_thread_state64_get_lr(ts)
#define arm_thread_state64_get_lr_fptr(ts) \
		__darwin_arm_thread_state64_get_lr_fptr(ts)
#define arm_thread_state64_set_lr_fptr(ts, fptr) \
		__darwin_arm_thread_state64_set_lr_fptr(ts, fptr)
#define arm_thread_state64_get_sp(ts) \
		__darwin_arm_thread_state64_get_sp(ts)
#define arm_thread_state64_set_sp(ts, ptr) \
		__darwin_arm_thread_state64_set_sp(ts, ptr)
#define arm_thread_state64_get_fp(ts) \
		__darwin_arm_thread_state64_get_fp(ts)
#define arm_thread_state64_set_fp(ts, ptr) \
		__darwin_arm_thread_state64_set_fp(ts, ptr)
#endif /* __DARWIN_C_LEVEL >= __DARWIN_C_FULL && defined(__arm64__) */
#endif /* !defined(KERNEL) */

struct arm_unified_thread_state {
	arm_state_hdr_t ash;
	union {
		arm_thread_state32_t ts_32;
		arm_thread_state64_t ts_64;
	} uts;
};
#define	ts_32	uts.ts_32
#define	ts_64	uts.ts_64
typedef struct arm_unified_thread_state arm_unified_thread_state_t;

#define ARM_THREAD_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_thread_state_t)/sizeof(uint32_t)))
#define ARM_THREAD_STATE32_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_thread_state32_t)/sizeof(uint32_t)))
#define ARM_THREAD_STATE64_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_thread_state64_t)/sizeof(uint32_t)))
#define ARM_UNIFIED_THREAD_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_unified_thread_state_t)/sizeof(uint32_t)))


typedef _STRUCT_ARM_VFP_STATE			arm_vfp_state_t;
typedef _STRUCT_ARM_NEON_STATE			arm_neon_state_t;
typedef _STRUCT_ARM_NEON_STATE			arm_neon_state32_t;
typedef _STRUCT_ARM_NEON_STATE64		arm_neon_state64_t;

typedef _STRUCT_ARM_EXCEPTION_STATE		arm_exception_state_t;
typedef _STRUCT_ARM_EXCEPTION_STATE		arm_exception_state32_t;
typedef _STRUCT_ARM_EXCEPTION_STATE64	arm_exception_state64_t;

typedef _STRUCT_ARM_DEBUG_STATE32		arm_debug_state32_t;
typedef _STRUCT_ARM_DEBUG_STATE64		arm_debug_state64_t;

#if defined(XNU_KERNEL_PRIVATE) && defined(__arm64__)
/* See below for ARM64 kernel structure definition for arm_debug_state. */
#else
/*
 * Otherwise not ARM64 kernel and we must preserve legacy ARM definitions of
 * arm_debug_state for binary compatability of userland consumers of this file.
 */
#if defined(__arm__)
typedef _STRUCT_ARM_DEBUG_STATE			arm_debug_state_t;
#elif defined(__arm64__)
typedef _STRUCT_ARM_LEGACY_DEBUG_STATE		arm_debug_state_t;
#else
#error Undefined architecture
#endif
#endif

#define ARM_VFP_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_vfp_state_t)/sizeof(uint32_t)))

#define ARM_EXCEPTION_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_exception_state_t)/sizeof(uint32_t)))

#define ARM_EXCEPTION_STATE64_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_exception_state64_t)/sizeof(uint32_t)))

#define ARM_DEBUG_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_debug_state_t)/sizeof(uint32_t)))

#define ARM_DEBUG_STATE32_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_debug_state32_t)/sizeof(uint32_t)))

#define ARM_DEBUG_STATE64_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_debug_state64_t)/sizeof(uint32_t)))

#define ARM_NEON_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_neon_state_t)/sizeof(uint32_t)))

#define ARM_NEON_STATE64_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_neon_state64_t)/sizeof(uint32_t)))

#define MACHINE_THREAD_STATE 		ARM_THREAD_STATE
#define MACHINE_THREAD_STATE_COUNT	ARM_UNIFIED_THREAD_STATE_COUNT

/*
 * Largest state on this machine:
 */
#define THREAD_MACHINE_STATE_MAX	THREAD_STATE_MAX

#ifdef XNU_KERNEL_PRIVATE

static inline boolean_t
is_thread_state32(const arm_unified_thread_state_t *its)
{
	return (its->ash.flavor == ARM_THREAD_STATE32);
}

static inline boolean_t
is_thread_state64(const arm_unified_thread_state_t *its)
{
	return (its->ash.flavor == ARM_THREAD_STATE64);
}

static inline arm_thread_state32_t*
thread_state32(arm_unified_thread_state_t *its)
{
	return &its->ts_32;
}

static inline arm_thread_state64_t*
thread_state64(arm_unified_thread_state_t *its)
{
	return &its->ts_64;
}

static inline const arm_thread_state32_t*
const_thread_state32(const arm_unified_thread_state_t *its)
{
	return &its->ts_32;
}

static inline const arm_thread_state64_t*
const_thread_state64(const arm_unified_thread_state_t *its)
{
	return &its->ts_64;
}

#if defined(__arm__)
#include <arm/proc_reg.h>

#define ARM_SAVED_STATE			THREAD_STATE_NONE + 1

struct arm_saved_state {
    uint32_t    r[13];      /* General purpose register r0-r12 */
    uint32_t    sp;     /* Stack pointer r13 */
    uint32_t    lr;     /* Link register r14 */
    uint32_t    pc;     /* Program counter r15 */
    uint32_t    cpsr;       /* Current program status register */
    uint32_t    fsr;        /* Fault status */
    uint32_t    far;        /* Virtual Fault Address */
    uint32_t    exception;  /* exception number */
};
typedef struct arm_saved_state arm_saved_state_t;

/*
 * Just for coexistence with AArch64 code.
 */
typedef struct arm_saved_state arm_saved_state32_t;

static inline arm_saved_state32_t*
saved_state32(arm_saved_state_t *iss)
{
    return iss;
}

static inline boolean_t
is_saved_state32(const arm_saved_state_t *iss __unused)
{
    return TRUE;
}


struct arm_saved_state_tagged {
	uint32_t					tag;
	struct arm_saved_state		state;
};
typedef struct arm_saved_state_tagged arm_saved_state_tagged_t;

#define ARM_SAVED_STATE32_COUNT ((mach_msg_type_number_t) \
		(sizeof (arm_saved_state_t)/sizeof(unsigned int)))


static inline register_t
get_saved_state_pc(const arm_saved_state_t *iss)
{
	return iss->pc;
}

static inline void
set_saved_state_pc(arm_saved_state_t *iss, register_t pc)
{
	iss->pc = pc;
}

static inline register_t
get_saved_state_sp(const arm_saved_state_t *iss)
{
	return iss->sp;
}

static inline void
set_saved_state_sp(arm_saved_state_t *iss, register_t sp)
{
	iss->sp = sp;
}

static inline register_t
get_saved_state_fp(const arm_saved_state_t *iss)
{
	return iss->r[7];
}

static inline void
set_saved_state_fp(arm_saved_state_t *iss, register_t fp)
{
	iss->r[7] = fp;
}

static inline register_t
get_saved_state_lr(const arm_saved_state_t *iss)
{
	return iss->lr;
}

static inline void
set_saved_state_lr(arm_saved_state_t *iss, register_t lr)
{
	iss->lr = lr;
}

static inline register_t
get_saved_state_cpsr(const arm_saved_state_t *iss)
{
	return iss->cpsr;
}

static inline void
set_saved_state_cpsr(arm_saved_state_t *iss, register_t cpsr)
{
	iss->cpsr = cpsr;
}

static inline register_t
get_saved_state_reg(const arm_saved_state_t *iss, unsigned regno)
{
	return iss->r[regno];
}

static inline void
set_saved_state_reg(arm_saved_state_t *iss, unsigned regno, register_t val)
{
	iss->r[regno] = val;
}

#elif defined(__arm64__)

#include <kern/assert.h>
#include <arm64/proc_reg.h>
#define CAST_ASSERT_SAFE(type, val) (assert((val) == ((type)(val))), (type)(val))

/*
 * GPR context
 */

struct arm_saved_state32 {
	uint32_t	r[13];		/* General purpose register r0-r12 */
	uint32_t	sp;			/* Stack pointer r13 */
	uint32_t	lr;			/* Link register r14 */
	uint32_t	pc;			/* Program counter r15 */
	uint32_t	cpsr;		/* Current program status register */
	uint32_t	far;		/* Virtual fault address */
	uint32_t	esr;		/* Exception syndrome register */
	uint32_t	exception;	/* Exception number */
};
typedef struct arm_saved_state32 arm_saved_state32_t;

struct arm_saved_state32_tagged {
	uint32_t					tag;
	struct arm_saved_state32	state;
};
typedef struct arm_saved_state32_tagged arm_saved_state32_tagged_t;

#define ARM_SAVED_STATE32_COUNT ((mach_msg_type_number_t) \
		(sizeof (arm_saved_state32_t)/sizeof(unsigned int)))

struct arm_saved_state64 {
	uint64_t	x[29];		/* General purpose registers x0-x28 */
	uint64_t	fp;			/* Frame pointer x29 */
	uint64_t	lr;			/* Link register x30 */
	uint64_t	sp;			/* Stack pointer x31 */
	uint64_t	pc;			/* Program counter */
	uint32_t	cpsr;		/* Current program status register */
	uint32_t	reserved;	/* Reserved padding */
	uint64_t	far;		/* Virtual fault address */
	uint32_t	esr;		/* Exception syndrome register */
	uint32_t	exception;	/* Exception number */
};
typedef struct arm_saved_state64 arm_saved_state64_t;

#define ARM_SAVED_STATE64_COUNT ((mach_msg_type_number_t) \
		(sizeof (arm_saved_state64_t)/sizeof(unsigned int)))

struct arm_saved_state64_tagged {
	uint32_t					tag;
	struct arm_saved_state64	state;
};
typedef struct arm_saved_state64_tagged arm_saved_state64_tagged_t;

struct arm_saved_state {
	arm_state_hdr_t ash;
	union {
		struct arm_saved_state32 ss_32;
		struct arm_saved_state64 ss_64;
	} uss;
} __attribute__((aligned(16)));
#define	ss_32	uss.ss_32
#define	ss_64	uss.ss_64

typedef struct arm_saved_state arm_saved_state_t;


static inline boolean_t
is_saved_state32(const arm_saved_state_t *iss)
{
	return (iss->ash.flavor == ARM_SAVED_STATE32);
}

static inline boolean_t
is_saved_state64(const arm_saved_state_t *iss)
{
	return (iss->ash.flavor == ARM_SAVED_STATE64);
}

static inline arm_saved_state32_t*
saved_state32(arm_saved_state_t *iss)
{
	return &iss->ss_32;
}

static inline const arm_saved_state32_t*
const_saved_state32(const arm_saved_state_t *iss)
{
	return &iss->ss_32;
}

static inline arm_saved_state64_t*
saved_state64(arm_saved_state_t *iss)
{
	return &iss->ss_64;
}

static inline const arm_saved_state64_t*
const_saved_state64(const arm_saved_state_t *iss)
{
	return &iss->ss_64;
}

static inline register_t
get_saved_state_pc(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->pc : const_saved_state64(iss)->pc);
}

static inline void
set_saved_state_pc(arm_saved_state_t *iss, register_t pc)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->pc = CAST_ASSERT_SAFE(uint32_t, pc);
	} else {
		saved_state64(iss)->pc = pc;
	}
}

static inline register_t
get_saved_state_sp(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->sp : const_saved_state64(iss)->sp);
}

static inline void
set_saved_state_sp(arm_saved_state_t *iss, register_t sp)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->sp = CAST_ASSERT_SAFE(uint32_t, sp);
	} else {
		saved_state64(iss)->sp = sp;
	}
}

static inline register_t
get_saved_state_lr(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->lr : const_saved_state64(iss)->lr);
}

static inline void
set_saved_state_lr(arm_saved_state_t *iss, register_t lr)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->lr = CAST_ASSERT_SAFE(uint32_t, lr);
	} else {
		saved_state64(iss)->lr = lr;
	}
}

static inline register_t
get_saved_state_fp(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->r[7] : const_saved_state64(iss)->fp);
}

static inline void
set_saved_state_fp(arm_saved_state_t *iss, register_t fp)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->r[7] = CAST_ASSERT_SAFE(uint32_t, fp);
	} else {
		saved_state64(iss)->fp = fp;
	}
}

static inline int
check_saved_state_reglimit(const arm_saved_state_t *iss, unsigned reg) 
{
	return (is_saved_state32(iss) ? (reg < ARM_SAVED_STATE32_COUNT) : (reg < ARM_SAVED_STATE64_COUNT));
}

static inline register_t
get_saved_state_reg(const arm_saved_state_t *iss, unsigned reg)
{
	if (!check_saved_state_reglimit(iss, reg)) return 0;

	return (is_saved_state32(iss) ? (const_saved_state32(iss)->r[reg]) : (const_saved_state64(iss)->x[reg]));
}

static inline void
set_saved_state_reg(arm_saved_state_t *iss, unsigned reg, register_t value)
{
	if (!check_saved_state_reglimit(iss, reg)) return;

	if (is_saved_state32(iss)) {
		saved_state32(iss)->r[reg] = CAST_ASSERT_SAFE(uint32_t, value);
	} else {
		saved_state64(iss)->x[reg] = value;
	}
}

static inline uint32_t
get_saved_state_cpsr(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->cpsr : const_saved_state64(iss)->cpsr);
}

static inline void
set_saved_state_cpsr(arm_saved_state_t *iss, uint32_t cpsr)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->cpsr = cpsr;
	} else {
		saved_state64(iss)->cpsr = cpsr;
	}
}

static inline register_t
get_saved_state_far(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->far : const_saved_state64(iss)->far);
}

static inline void
set_saved_state_far(arm_saved_state_t *iss, register_t far)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->far = CAST_ASSERT_SAFE(uint32_t, far);
	} else {
		saved_state64(iss)->far = far;
	}
}

static inline uint32_t
get_saved_state_esr(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->esr : const_saved_state64(iss)->esr);
}

static inline void
set_saved_state_esr(arm_saved_state_t *iss, uint32_t esr)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->esr = esr;
	} else {
		saved_state64(iss)->esr = esr;
	}
}

static inline uint32_t
get_saved_state_exc(const arm_saved_state_t *iss)
{
	return (is_saved_state32(iss) ? const_saved_state32(iss)->exception : const_saved_state64(iss)->exception);
}

static inline void
set_saved_state_exc(arm_saved_state_t *iss, uint32_t exc)
{
	if (is_saved_state32(iss)) {
		saved_state32(iss)->exception = exc;
	} else {
		saved_state64(iss)->exception = exc;
	}
}

extern void panic_unimplemented(void);

static inline int
get_saved_state_svc_number(const arm_saved_state_t *iss) 
{
	return (is_saved_state32(iss) ? (int)const_saved_state32(iss)->r[12] : (int)const_saved_state64(iss)->x[ARM64_SYSCALL_CODE_REG_NUM]); /* Only first word counts here */
}

typedef _STRUCT_ARM_LEGACY_DEBUG_STATE		arm_legacy_debug_state_t;

struct arm_debug_aggregate_state {
    arm_state_hdr_t         dsh;
    union {
        arm_debug_state32_t ds32;
        arm_debug_state64_t ds64;
    } uds;
} __attribute__((aligned(16)));

typedef struct arm_debug_aggregate_state arm_debug_state_t;

#define ARM_LEGACY_DEBUG_STATE_COUNT ((mach_msg_type_number_t) \
   (sizeof (arm_legacy_debug_state_t)/sizeof(uint32_t)))

/*
 * NEON context
 */
typedef __uint128_t uint128_t;
typedef uint64_t uint64x2_t __attribute__((ext_vector_type(2)));
typedef uint32_t uint32x4_t __attribute__((ext_vector_type(4)));

struct arm_neon_saved_state32 {
	union {
		uint128_t	q[16];
		uint64_t	d[32];
		uint32_t	s[32];
	} v;
	uint32_t		fpsr;
	uint32_t		fpcr;
};
typedef struct arm_neon_saved_state32 arm_neon_saved_state32_t;

#define ARM_NEON_SAVED_STATE32_COUNT ((mach_msg_type_number_t) \
		(sizeof (arm_neon_saved_state32_t)/sizeof(unsigned int)))

struct arm_neon_saved_state64 {
	union {
		uint128_t		q[32];
		uint64x2_t		d[32];
		uint32x4_t		s[32];
	} v;
	uint32_t		fpsr;
	uint32_t		fpcr;
};
typedef struct arm_neon_saved_state64 arm_neon_saved_state64_t;

#define ARM_NEON_SAVED_STATE64_COUNT ((mach_msg_type_number_t) \
		(sizeof (arm_neon_saved_state64_t)/sizeof(unsigned int)))

struct arm_neon_saved_state {
	arm_state_hdr_t nsh;
	union {
		struct arm_neon_saved_state32 ns_32;
		struct arm_neon_saved_state64 ns_64;
	} uns;
};
typedef struct arm_neon_saved_state arm_neon_saved_state_t;
#define	ns_32	uns.ns_32
#define	ns_64	uns.ns_64

static inline boolean_t
is_neon_saved_state32(const arm_neon_saved_state_t *state)
{
	return (state->nsh.flavor == ARM_NEON_SAVED_STATE32);
}

static inline boolean_t
is_neon_saved_state64(const arm_neon_saved_state_t *state)
{
	return (state->nsh.flavor == ARM_NEON_SAVED_STATE64);
}

static inline arm_neon_saved_state32_t *
neon_state32(arm_neon_saved_state_t *state)
{
	return &state->ns_32;
}

static inline arm_neon_saved_state64_t *
neon_state64(arm_neon_saved_state_t *state)
{
	return &state->ns_64;
}


/*
 * Aggregated context
 */

struct arm_context {
	struct arm_saved_state ss;
	struct arm_neon_saved_state ns;
};
typedef struct arm_context arm_context_t;

extern void saved_state_to_thread_state64(const arm_saved_state_t*, arm_thread_state64_t*);
extern void thread_state64_to_saved_state(const arm_thread_state64_t*, arm_saved_state_t*);

#else
#error Unknown arch
#endif

extern void saved_state_to_thread_state32(const arm_saved_state_t*, arm_thread_state32_t*);
extern void thread_state32_to_saved_state(const arm_thread_state32_t*, arm_saved_state_t*);

#endif /* XNU_KERNEL_PRIVATE */

#endif    /* _ARM_THREAD_STATUS_H_ */
