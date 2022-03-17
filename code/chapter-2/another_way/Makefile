CLANG = clang

EXECABLE = monitor-exec

BPFCODE = bpf_program

BPFTOOLS = /usr/src/linux-5.4.100/samples/bpf
BPFLOADER = $(BPFTOOLS)/bpf_load.c

CCINCLUDE += -I/usr/src/linux-5.4.100/tools/testing/selftests/bpf

LOADINCLUDE += -I/usr/src/linux-5.4.100/tools/lib/bpf
LOADINCLUDE += -I/usr/src/linux-5.4.100/tools/lib
LOADINCLUDE += -I/usr/src/linux-5.4.100/tools/perf
LOADINCLUDE += -I/usr/src/linux-5.4.100/tools/include
LOADINCLUDE += -I/usr/src/linux-5.4.100/samples/bpf
LIBRARY_PATH = -L/usr/local/lib64
BPFSO = -lbpf

# Setting -DHAVE_ATTR_TEST=0 for the kernel containing below patch:
# 06f84d1989b7 perf tools: Make usage of test_attr__* optional for perf-sys.h
#
# The patch was included in Linus's tree starting v5.5-rc1, but was also included
# in stable kernel branch linux-5.4.y. So it's hard to determine whether a kernel
# is affected based on the kernel version alone:
# - for a v5.4 kernel from Linus's tree, no;
# - for a v5.4 kernel from the stable tree (used by many distros), yes.
#
# So let's look at the actual kernel source code to decide.
#
# See more context at:
# https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=06f84d1989b7e58d56fa2e448664585749d41221
# https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=fce9501aec6bdda45ef3a5e365a5e0de7de7fe2d
CFLAGS += $(shell grep -q "define HAVE_ATTR_TEST 1" /usr/src/linux-5.4.100/tools/perf/perf-sys.h \
                  && echo "-DHAVE_ATTR_TEST=0")

.PHONY: clean $(CLANG) bpfload build

clean:
	rm -f *.o *.so $(EXECABLE)

build: ${BPFCODE.c} ${BPFLOADER}
#	$(CLANG) -I/usr/include/x86_64-linux-gnu -I/usr/src/linux-5.4.100/include -O2 -target bpf -c $(BPFCODE:=.c) $(CCINCLUDE) -o ${BPFCODE:=.o}
	$(CLANG)  -I/usr/src/linux-5.4.100/include -O2 -target bpf -c $(BPFCODE:=.c) $(CCINCLUDE) -o ${BPFCODE:=.o}

KERNEL_SRCTREE=/usr/src/linux-5.4.100
LIBBPF=${KERNEL_SRCTREE}/tools/lib/bpf/libbpf.a

bpfload: build
	# clang -o monitor-exec -I${KERNEL_SRCTREE}/tools/lib/bpf/ \
	# -I${KERNEL_SRCTREE}/tools/lib -I${KERNEL_SRCTREE}/tools/include \
	# -I${KERNEL_SRCTREE}/tools/perf -I${KERNEL_SRCTREE}/samples \
	# ${KERNEL_SRCTREE}/samples/bpf/bpf_load.c \
	# loader.c "${LIBBPF}" -lelf -DHAVE_ATTR_TEST=0
	clang $(CFLAGS) -o $(EXECABLE) -lelf $(LOADINCLUDE) $(LIBRARY_PATH) $(BPFSO) \
       $(BPFLOADER) loader.c

$(EXECABLE): bpfload

.DEFAULT_GOAL := $(EXECABLE)
