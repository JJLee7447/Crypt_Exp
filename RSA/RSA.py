# Author: JJLee7447
# Version: 1.0
# RSA.py is a class that implements the RSA algorithm

import random
def mod_inverse(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        raise ValueError("The modular inverse does not exist")
    else:
        return x % m

def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, x, y = extended_gcd(b % a, a)
        return (g, y - (b // a) * x, x)

def fast_mul(a, b, n):
    ans = 0
    while b > 0:
        if b & 1:
            ans = (ans + a) % n
        a = (a + a) % n
        b >>= 1
    return ans

def fast_mod_exp(a, b, n):
    ans, base = 1, a
    while b > 0:
        if b & 1:
            ans = fast_mul(ans, base, n) % n
        base = fast_mul(base, base, n) % n
        b >>= 1
    return ans

def MillerRabin(n, k):
    if n == 2:
        return True
    if n % 2 == 0:
        return False

    r = 0
    s = n - 1
    while s % 2 == 0:
        r += 1
        s //= 2

    for i in range(k):
        a = random.randrange(2, n - 1)
        x = fast_mod_exp(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for j in range(r - 1):
            x = fast_mod_exp(x, 2, n)
            if x == 1:
                return False
            if x == n - 1:
                break
        if x != n - 1:
            return False
    return True

def generate_prime(bits):
    while True:
        n = random.randrange(2 ** (bits - 1), 2 ** bits)
        if MillerRabin(n, 40):
            return n

def string_to_int(message):
    return int.from_bytes(message.encode(), 'big')

def int_to_string(message):
    return message.to_bytes((message.bit_length() + 7) // 8, 'big').decode()

class RSA:

    def __init__(self):
        try:
            self.p = generate_prime(100)
            self.q = generate_prime(100)
            self.n = (self.p * self.q)
            self.phi = (self.p - 1) * (self.q - 1)
            self.e = 65537
            self.d = mod_inverse(self.e, self.phi)
            
        except Exception as e:
            print(e)
            print("Error, generating new keys...")
            self.__init__()

    def encrypt(self, m):
        return fast_mod_exp(m, self.e, self.n)
    
    def decrypt(self, c):
        return fast_mod_exp(c, self.d, self.n)



if __name__ == "__main__":
    rsa = RSA()
    print("P = " + str(rsa.p))
    print("Q = " + str(rsa.q))
    print("N = " + str(rsa.n))
    print("Phi = " + str(rsa.phi))
    print("E = " + str(rsa.e))
    print("D = " + str(rsa.d))

    m = string_to_int("Hello World")
    c = rsa.encrypt(m)
    print("M = " + str(m))

    print("C = " + str(c))
    print("M = " + str(rsa.decrypt(c)))

    print("M = " + int_to_string(rsa.decrypt(c)))