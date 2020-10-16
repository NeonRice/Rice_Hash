# 🍙 rice::hash 🍙
A well cooked hash, just like good rice should be!

## <i>📰 Instructions 📰</i>

1. Download the source code
2. Compile the source code with your preferred compiler.
3. Run the file in the terminal of our choice.

## <i>🧪 Test running instructions 💉</i>
<font size="2">
If you want to run the tests provided with the source, <br>compile test.cpp instead of main.cpp

Then run the program like you would any other.
</font>
## <i>♨️ Main idea ♨️</i>
<font size="2">
Hash is made by splitting bits into chunks and words, generating additional words, doing some bit manipulation magic and then putting it all back together.</font>
<br><br><font size="1"><i>This is actually an un-optimized SHA-1 ported to fit 256-bit hash constrains</i> 🤫</font>

## Hashing Pseudocode 👩‍🔬

```
1. Get input
2. Break input into characters
3. Convert characters to ASCII
4. Convert ASCII values to binary
5. Append 0's to the end of binary string
6. Append original message length in binary
7. Split message into chunks of 512-bits
8. Break the chunks into words of 32-bits
9. Expand, we need 80 words for each chunk
10. Transform words of each chunk and store in digest of 32-bit length passing it to another chunk
11. Put everything back together
```

## 🍡 Tests 🍡

### <i>Collision test</i>

<font size="2">No practical collisions were found during the execution of the following test case.

Tests were done on 1250 randomly generated string pairs of different lengths.

The pairs differed by 1 character each.
</font>

### <i>Avalanche effect 💨</i>

| Input | Hash  (output)                   |
| ------------------ | ------------------------------------------------------------ |
| rice_hash           | 2727cd6b36030d48896dc0b233f97456f151fee8f18ff7b3eb1bc5f9801c1dc4 |
| rice_Hash           | 618d724c5afd81ce8f9d3bb1993fff78c7d37ae97b7e31b7660c000881606dd9 |
| rice_Hash!          | 35055fd720c874a7c8c4c14ac24ba86b3a08e0dff952b172f2dfd087ba47d61d |

### </br><i>Hash difference on a bit/hex level 👾</i>
<font size="2">
The following tests were done with different length strings in range of 10 to 1000 characters

<br>Average Hash difference on Binary level: **75%**

Average Hash difference on Hexadecimal level: **96%**
</font>

### <i>🏁 Speed test 🏁</i>
<font size="2">
<i>konstitucija.txt</i> test file hashes in 0.12 s

2500 strings of 1000 characters took 3.1 s to hash
</font>
## <i>Final words ✔️</i>
<font size="2">
Rice is best made with some good salt. 🧂 Salt your rice friends.
</font>

 ## <i>Releases</i>
 
[**[v0.2]**](https://github.com/NeonRice/Rice_Hash/releases/tag/0.2) 
 
[**[v0.1]**](https://github.com/NeonRice/Rice_Hash/releases/tag/0.1) 
  