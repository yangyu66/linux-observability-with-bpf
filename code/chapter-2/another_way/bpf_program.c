// #include <linux/bpf.h>
#include <uapi/linux/bpf.h>
#include "prototype-kernel/kernel/samples/bpf/bpf_helpers.h"
#define SEC(NAME) __attribute__((section(NAME), used))

// see https://blog.raymond.burkholder.net/index.php?/archives/1000-eBPF-Basics.html
// clang  -I/usr/src/linux-5.4.100/include -O2 -target bpf -c bpf_program.c -I/usr/src/linux-5.4.100/tools/testing/selftests/bpf -o bpf_program.o

// static int (*bpf_trace_printk)(const char *fmt, int fmt_size,
//                                ...) = (void *)BPF_FUNC_trace_printk;

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  char msg[] = "Hello, BPF World!";
  bpf_trace_printk(msg, sizeof(msg));
  return 0;
}

char _license[] SEC("license") = "GPL";
