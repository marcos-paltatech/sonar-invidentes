#ifndef ADLER32_H_
#define ADLER32_H_

// Adler32 checksum
uint32_t adler32(uint8_t* data, uint32_t len)
{
    uint32_t a= 1;
    uint32_t b= 0;

    while(len) {
        a = (a + *data) % 65521;
        b = (b + a) % 65521;
        data++;
        len--;
    }
    return (b << 16) | a;
}

#endif /* ADLER32_H_ */
