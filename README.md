# cipher
A self-designed symmetric cipher class

This cipher makes use of a secret state which consists of two parts:
1. A permutation of all 256 possible bytes(S).
2. Two 8-bit index-points(i, j).

for i from 0 to 255
    s[i] = i
endfor
j = 0
fo i from 0 to 255
    j = (j + s[i] + key[i mod keylength]) mod 256
    swap values of s[i] and s[j]

endfor

i = 0
j = 0
while generatingOutput:
    i = (i+1) mod 256
    j = (j + s[i]) mod 256
    swap values of s[i] and s[j]
    k = s[(s[i])+s[j] mod 256]
    output k(the keystream)
endwhile

OUTPUT:

out = in ^ keystream
