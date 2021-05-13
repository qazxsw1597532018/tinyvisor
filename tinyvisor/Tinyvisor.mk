TINYVISOR_C_SRCS := $(shell find tinyvisor/src/ -name '*.c')
TINYVISOR_C_OBJS := $(patsubst tinyvisor/src/%, obj/tinyvisor/%.o, $(TINYVISOR_C_SRCS))

TINYVISOR_S_SRCS := $(shell find tinyvisor/src/ -name '*.S')
TINYVISOR_S_OBJS := $(patsubst tinyvisor/src/%, obj/tinyvisor/%.o, $(TINYVISOR_S_SRCS))

TINYVISOR_OBJS := $(TINYVISOR_C_OBJS) $(TINYVISOR_S_OBJS)
