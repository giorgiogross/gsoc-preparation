#ifdef _exchangeclass // defined by exchange.h
extern "C" {
#endif

void pass(void* exchanger, char* data); // called from c code

#ifdef _exchangeclass
}
#endif