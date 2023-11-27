## 1. initial S table

Step1:对S表进行线性填充，一般为256个字节;
Step2:用种子密钥填充另一个256字节的K表;
Step3:用K表对S表进行初始置换。

## 2. create Key stream

