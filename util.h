#define SET(p, v) p ## _PORT = (p ## _PORT & ~(1 << p ## _BIT)) | (v << p ## _BIT)
#define OUTPUT(p) p ## _DDR |= (1 << p ## _BIT)
#define INPUT(p) p ## _DDR &= ~(1 << p ## _BIT)
#define VALUE(p) (p ## _PIN & (1 << p ## _BIT))
