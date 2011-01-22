#include <rsx/buffer.h>
#include <assert.h>

s32 rsxContextCallback(gcmContextData* context, u32 count)
{
	opd32* callback = (opd32*)(u64)context->callback;
	volatile opd64 opd = {
		(void*)(u64)callback->func,
		(void*)(u64)callback->rtoc,
		0
	};
	return ((s32(*)())&opd)();
}

void commandBufferPut(gcmContextData* context, uint32_t value) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = value;
	context->current = (uint32_t)(uint64_t) buffer;
}

