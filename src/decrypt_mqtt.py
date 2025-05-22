#!/usr/bin/env python3
import subprocess
from Crypto.Cipher import AES

# Chave de 16 bytes (128 bits)
AES_KEY = b"minha_chave_1234"  # precisa ter 16, 24 ou 32 bytes
BLOCK_SIZE = 16


def aes_decrypt(data: bytes, key: bytes) -> bytes:
    cipher = AES.new(key, AES.MODE_ECB)
    return cipher.decrypt(data)


cmd = [
    "mosquitto_sub",
    "-t",
    "test/topic/aes",
    "-u",
    "user1",
    "-P",
    "trt567",
    "-h",
    "localhost",
    "-p",
    "1883",
]

print("Aguardando mensagens AES criptografadas...")

with subprocess.Popen(cmd, stdout=subprocess.PIPE) as proc:
    for line in proc.stdout:
        try:
            line = line.strip(b"\n")
            if not line:
                continue

            # Garante que o tamanho seja múltiplo de 16 para AES-ECB
            if len(line) % BLOCK_SIZE != 0:
                print(f"[!] Tamanho inválido para AES (recebido {len(line)} bytes).")
                continue

            decrypted = aes_decrypt(line, AES_KEY)
            # Remove padding nulo (se aplicável)
            clean = decrypted.rstrip(b"\x00")

            print("Mensagem descriptografada:", clean.decode("utf-8", errors="replace"))

        except Exception as e:
            print("Erro:", e)
