---
title: Primeiros Passos com ESP-IDF
summary: Este documento tem como objetivo guiá-lo na programação da Franininho DIY com AVR LIB C
authors:
    - Fábio Souza
date: 2021-04-24
some_url:
---

# Exemplos AVR Libc - Franininho DIY

O projeto Franzininho tem o objetivo de incentivar as pessoas nas área de eletrônica e programação. Através das oficinas de soldagem e programação na IDE Arduino, diversas pessoas tiveram o seu primeiro contato com essas areas. [Saiba mais sobre o projeto Franzininho]().

Esse material tem o objetivo de mostrar os primeiros passos para programação de microcontroladores usando linguagem C e com abordagem mais próxima ao hardware. Serão apresentados uma sequencia de exemplos(com explicação detalhadas sobre a Arquitetura do Attiny85) para programação da Franzininho DIY usando a AVR Libc.

É importante que você tenha o [pinout da Franzininho DIY](https://github.com/Franzininho/imagens-franzininho/blob/main/franzininho_diy/Pinagem-completa-Franzininho-DIY-V2RV2.png) para fazer as ligações conforme orientações nos exemplos.

![pinout Franzininho DIY](img/0x00/Pinagem-Franzininho-DIY-V2RV2.png)


## Ferramentas necessárias

Você não precisará de um compilador específico ou IDE para compilar os exemplos apresentados. Porém é importante que tenha as seguintes ferramentas instaladas na sua máquina:

- GCC AVR
- avr libc
- binutils-avr
- make

### Instalação das ferramentas necessárias (Linux):
```shell
sudo apt install gcc-avr
sudo apt install avr-libc
sudo apt install binutils-avr
sudo apt install make
```

A placa Franzininho deve estar com o bootloader Micronucleus( bottloader oficial para a Franzininho DIY).

### Compilação no Linux

```shell
cd ../exemplos-avr-libc/exemplos/01-hello
make all
```

### Arduino IDE

Você também poderá reproduzir todos os exemplos apresentados diretamente na IDE Arduino (sem usar o Frameworek Arduino). Isso facilitará no processo de instalação e configuração das ferramentas e também no upload.

## Repositórios e materiais de apoio

Todos os exemplos serão hospedados no [github do projeto Franzininho](https://github.com/Franzininho/exemplos-avr-libc/). É importante que você use o datasheet do Attiny85 como material de apoio, assim como a documentação da [AVR Libc](https://nongnu.org/avr-libc/)

Aproveite essa jornada.

## Saiba mais
[Franzininho – Um Arduino para todos](https://www.embarcados.com.br/franzininho/)
[Documentação Franzininho DIY](https://franzininho.gitbook.io/franzininho-docs/)
