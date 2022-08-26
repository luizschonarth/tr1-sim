#include <iostream>
#include <unistd.h>
#include "../include/Common.hpp"

/* Recebe string e, para cada caracter (byte), insere bits
 * correspondentes no vetor de bits de retorno na ordem
 * big-endian -> little-endian. */
std::vector<bit> utils::string_para_bits(const std::string &str) {
    std::vector<bit> bits;

    for (auto &c : str) {
        for(int i = 0; i < TAM_BYTE; i++) {
            /* Para cada caractere da string, insere os bits do byte do caracter
             * na ordem big-endian -> little-endian. */
            bits.push_back(((c << i) & 0x80));
        }
    }
    return bits;
} // fim da função string_para_bits

/* Recebe iterador do vetor de bits e percorre TAM_BYTE
 * vezes e armazena os 8 bits que compõem o byte no byte
 * de retorno na ordem big-endian -> little-endian. */
byte utils::get_byte(std::vector<bit>::iterator it) {
    byte c = 0;

    for (int k = 0; k < TAM_BYTE; k++) {
        /* Usa operações bitwise para deslocar o bit armazenado 
         * em it no bit correto dentro do byte. */
        c |= *it << (TAM_BYTE - (k+1));
        it++; // Vai para o próximo bit
    }
    return c;
} // fim da função get_byte

/* Recebe vetor de bits e posição inicial para ler o byte.
 * Percorre TAM_BYTE vezes o vetor e armazena os 8 bits no
 * byte de retorno na ordem big-endian -> little-endian. */
byte utils::get_byte(std::vector<bit> &trem_de_bits, unsigned int pos) {
    byte c = 0;

    for (int k = 0; k < TAM_BYTE; k++) {
        /* Usa operações bitwise para deslocar o bit armazenado 
         * em it no bit correto dentro do byte. */
        c |= trem_de_bits[pos + k] << (TAM_BYTE - (k+1));
    }
    return c;
} // fim da função get_byte

/* Recebe vetor de bits e retorna vetor de bytes contidos no
 * trem de bits. */
std::vector<byte> utils::get_bytes(std::vector<bit> &trem_de_bits) {
    std::vector<byte> bytes;

    // Itera pelo trem de bits usando vector::iterator
    for (auto it = trem_de_bits.begin(); it != trem_de_bits.end(); std::advance(it, TAM_BYTE)) {
        bytes.push_back(utils::get_byte(it));
    }
    return bytes;
} // fim da função get_bytes

/* Recebe vetor de bytes e retorna string codificada pelos bytes. */
std::string utils::bytes_para_string(std::vector<byte> &bytes) {
    return std::string(bytes.begin(), bytes.end());
} // fim da função bytes_para_string

/* Recebe vetor de bits e retorna string codificada pelos bits. */
std::string utils::bits_para_string(std::vector<bit> &trem_de_bits) {
    std::vector<byte> bytes = utils::get_bytes(trem_de_bits);
    return utils::bytes_para_string(bytes);
} // fim da função get_string

void utils::print_bits(std::vector<bit> &trem_de_bits) {
    for (int i = 0; i < trem_de_bits.size(); i += TAM_BYTE) {
        for (int j = 0; j < TAM_BYTE; j++) {
            std::cout << trem_de_bits[i+j];
        }
        std::cout << " ";
    }
    std::cout << "\n";
} // fim da função print_bits
