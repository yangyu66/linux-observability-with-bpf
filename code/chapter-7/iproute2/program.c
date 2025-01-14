#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#include <linux/ip.h>


#define SEC(NAME) __attribute__((section(NAME), used))

SEC("mysection")
int myprogram(struct xdp_md *ctx) {
  // https://duo.com/labs/tech-notes/writing-an-xdp-network-filter-with-ebpf
  
  int ethsize = 0;
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;
  struct ethhdr *eth = data;
  // struct iphdr *ip;

  ethsize = sizeof(*eth);
  struct iphdr *ip = data + ethsize;
  ethsize += sizeof(struct iphdr);
  if (data + ethsize > data_end) {
    return XDP_DROP;
  }

  if (ip->protocol == IPPROTO_ICMP) {
    return XDP_DROP;
  }

  return XDP_PASS;
}
