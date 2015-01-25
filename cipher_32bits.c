#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cipher_32bits.h"

static __inline void
swap_bytes(u_char *a, u_char *b) {
    u_char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void
_init(struct cipher_state *const state, const u_char* key, int keylen) {

    u_char j;
    int i;
    for (i = 0; i < 256; i++) {
        state->perm[i] = (u_char) i;
    }
    state->index1 = 0;
    state->index2 = 0;
    //randomize
    for (j = i = 0; i < 256; i++) {
        j += state->perm[i] + key[i % keylen];
        swap_bytes (&state->perm[i], &state->perm[j]);
    }
}

void
_crypt(struct cipher_state *const state, u_char *inbuf, u_char *outbuf, int buflen) {

    int i;
    u_char j;
    for (i = 0; i < buflen; i++) {
        state->index1 ++;
        state->index2 += state->perm[state->index1];
        swap_bytes (&state->perm[state->index1], &state->perm[state->index2]);
        j = state->perm[state->index1] + state->perm[state->index2];
        outbuf[i] = inbuf[i] ^ state->perm[j];
        printf("%c %c\n", inbuf[i], outbuf[i]);
    }
}

int main(int argc, char** argv) {

    FILE *fp = fopen("in.txt", "r");
    FILE *fp_o = fopen("out.txt", "w");
    int n = 0;
    u_char *in = (u_char*)malloc(10000 * sizeof(u_char));
    char *c_in = (char*)malloc(10000 * sizeof(char));
    while (fscanf(fp, "%c", c_in + n) != EOF)
        n ++;
    strncpy((char*) in, c_in, n);
    struct cipher_state *cs = (struct cipher_state *)malloc(sizeof(struct cipher_state));
    const u_char key[4] = {0x1F, 0xFC, 0xB2, 0x30};
    _init(cs, key, 4);
    u_char* out = (u_char*)malloc(n * sizeof(u_char));
    _crypt(cs, in, out, n);
//    fprintf(fp_o, "%s", out);
    //printf("%s", in);
    _crypt(cs, out, in, n);
    int i = 0;
  //  for (i = 0; i < n; i++)
    //    printf("%c", *out+i);

    ////////////////////
    free(cs);
    free(out);
    free(in);
    free(c_in);
    fclose(fp);
    fclose(fp_o);
    //////////////////
    return 0;

}
