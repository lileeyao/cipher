# cipher
* Basic facts
This cipher generates a randomized key block. This block can be used for encryption by combining it with the plaintext using bitwise exclusive-or (XOR); decryption is performed the same way (since exclusive-or with any given data is an involution). Steps of performing this cipher are described below. The algorithm is inherited from the stream cipher RC4, with changes on the block generation and key length.
* Generating the block
This block is a permutation of all possible 256 bytes, denoted ‘S’ in the pseudocode. Keylength is defined as the number of bytes in the key and can be in the range of [1, 256], in this case, we say it is 32 bits.
<pre>
func gen_block(key):
for i from 0 to 255     
	S[i] := i 
endfor 
j := 0 
for i from 0 to 255     
	j := (j + S[i] + key[i mod keylength]) mod 256     
	swap values of S[i] and S[j] 
endfor 
return S
</pre>
* Encryption & Decryption
Assume we have an input of plaintext (denoted as input below, length = n), to encrypt the plaintext, we use the previously generated block S.
<pre>
func encrypt_decrypt(S, input):
for i from 0 to n:
	i = (i + 1) mod 256
	j = (j + S[i]) mod 256
	swap values of S[i] and S[j]
	k = S[(S[i]+S[j]) mod 256]	
	output = input xor k
endfor
return output
</pre>
Decryption can be performed as the same way according to xor’s involution.
* Weakness & Crack
The 32-bit key is actually too short to support this cipher’s security. The cipher block has only 232 different cases, which can be easily enumerated by a super computer. Moreover, if we use a word dictionary to crack, the time cost will be even less. The brute force crack approach is described below. However, without knowing the key, it could be basically impossible to crack. In order to improve the security level, one can increase the length of key. Since the cipher is symmetric, a leak of the key will instantly cause the cipher comprosmised.
<pre>
func brute_crack(dict, input):
for key in dict:
	S = gen_block(key)
	Output = encrypt_decrypt(S, input)
endfor
</pre>
