TINYVISOR_C_SRCS := $(shell find tinyvisor/ -name '*.c')
TINYVISOR_C_OBJS := $(patsubst tinyvisor/%, obj/tinyvisor/%.o, $(TINYVISOR_C_SRCS))

TINYVISOR_S_SRCS := $(shell find tinyvisor/ -name '*.S')
TINYVISOR_S_OBJS := $(patsubst tinyvisor/%, obj/tinyvisor/%.o, $(TINYVISOR_S_SRCS))

TINYVISOR_OBJS := $(TINYVISOR_C_OBJS) $(TINYVISOR_S_OBJS)
