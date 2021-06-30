---
title: Primeiros Passos com ESP-IDF
summary: Este documento tem como objetivo guiá-lo na programação da Franininho DIY com AVR LIB C
authors:
    - Fábio Souza
date: 2021-04-24
some_url:
---

# Exemplos AVR Libc - Franininho DIY

O projeto Franzininho tem o objetivo de incentivar as pessoas nas área de eletrônica e programação. Através das oficinas de soldagem e programação na IDE Arduino, diversas pessoas tiveram o seu primeiro contato com essas áreas. [Saiba mais sobre o projeto Franzininho](https://franzininho.com.br/).

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

A placa Franzininho deve estar com o bootloader Micronucleus( bootloader oficial para a Franzininho DIY).

### Compilação no Linux

```shell
cd ../exemplos-avr-libc/exemplos/01-hello
make all
```

### Arduino IDE

Você também poderá reproduzir todos os exemplos apresentados diretamente na IDE Arduino (sem usar o framework Arduino). Isso facilitará no processo de instalação e configuração das ferramentas e também no upload.


### Wokwi

Você também pode usar o simulador Wokwi para reproduzir os projetos apresentados nessa série. Aproveite o template de projeto abaixo:

<iframe src="https://wokwi.com/arduino/new?template=franzininho" style="border: 0;" width="100%" height="458px" frameborder="0"></iframe>


## Repositórios e materiais de apoio

Todos os exemplos serão hospedados no [github do projeto Franzininho](https://github.com/Franzininho/exemplos-avr-libc/). É importante que você use o datasheet do Attiny85 como material de apoio, assim como a documentação da [AVR Libc](https://nongnu.org/avr-libc/)

Aproveite essa jornada.

## Saiba mais
[Franzininho – Um Arduino para todos](https://www.embarcados.com.br/franzininho/)

[Documentação Franzininho DIY](https://franzininho.gitbook.io/franzininho-docs/)

[Exemplos AVR LIB C - Franzininho DIY](https://franzininho.github.io/exemplos-avr-libc/)


| Autor | [Fábio Souza](https://github.com/FBSeletronica) |
|-------|-------------|
| Data: | 24/04/2021  |
