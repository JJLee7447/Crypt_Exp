## 1. initial S table

Step1:对S表进行线性填充，一般为256个字节;

```cpp
for (size_t i = 0; i < 256; i++)
{
    S_table.push_back(i);
}
```
Step2:用种子密钥填充另一个256字节的K表;

```cpp
    for (size_t i = 0; i < 256; i++)
    {
        K_table.push_back(Key[i % Key.size()]);
    }
```
Step3:用K表对S表进行初始置换。

```cpp
    int j = 0;
    for (size_t i = 0; i < 256; i++)
    {
        j = (j + S_table[i] + K_table[i]) % 256;
        std::swap(S_table[i], S_table[j]);
    }
```

## 2. create Key stream

```cpp
    int i = 0, j = 0, t = 0;
    for (size_t r = 0; r < PlainText_size; r++)
    {
        i = (i + 1) % 256;
        j = (j + _S_table[i]) % 256;
        std::swap(S_table[i], S_table[j]);
        t = (S_table[i] + S_table[j]) % 256;
        KeyStream.push_back(S_table[t]);
    }
```

## 3. Encrypt

```cpp
    for (size_t i = 0; i < PlainText_size; i++)
    {
        CipherText.push_back(PlainText[i] ^ KeyStream[i]);
    }
```
