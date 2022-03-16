#include "bpf_load.h"
// #include <bpf/bpf.h>
// #include <bpf/bpf_load.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (load_bpf_file("bpf_program.o") != 0) {
    printf("The kernel didn't load the BPF program\n");
    return -1;
  }

  read_trace_pipe();

  return 0;
}
