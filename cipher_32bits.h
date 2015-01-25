#ifndef _SYS_CRYPTO_H_
#define _SYS_CRYPTO_H_

struct cipher_state {
    u_char perm[256];
    u_char index1;
    u_char index2;
};

extern void _init(struct cipher_state *state, const u_char *key, int keylen);
extern void _crypt(struct cipher_state *state, u_char *inbuf, u_char *outbuf,
            int buflen);

#endif
