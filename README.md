# eExemplos AVR LIB C - Franzininho DIY

Exemplos em linguagem C baixo nível

## IMPORTANTE
- Por enquanto apenas para Franzininho DIY
- Só está funcionando no Linux
- Necessario as ferramentas abaixo
- A placa deve estar com o bootloader Micronucleus


## Ferramentas no Linux
```bash
sudo apt install gcc-avr
sudo apt install avr-libc
sudo apt install binutils-avr
sudo apt install make
```


## Usando
```bash
cd ../exemplos-avr-libc/exemplos/01-hello
make all
```

## Contribuindo

- Incluir exemplos em uma pasta dentro de exemplos

## Todo list

| Exemplos                       | Status | Nota                                    |
|--------------------------------|:------:|-----------------------------------------|
| Primeiros Passos               |    🟢   |                                         |
| Hello, World!                  |    🟢   |                                         |
| Saída Digital                  |    🟢   |                                         |
| Entrada Digital                |    🟢   |                                         |
| Timer 0                        |    🟢   |                                         |
| Timer 0 - Interrupção          |    🟢   |
| Contador de pulsos externos    |    🟢   |                                         |
| Instrumento musical com Buzzer |    🟢   |                                         |
| Interrupção externa            |    🔴   |                                         |
| Timer0 CTC                     |    🔴   |                                         |
| Timer0 PWM                     |    🔴   |                                         |
| Timer 1                        |    🔴   |                                         |
| Timer 2 Interrupção            |    🔴   |                                         |
| Timer 1 PWM                    |    🔴   |                                         |
| Conversor AD                   |    🔴   |                                         |
| I2C                            |    🔴   |                                         |
| SPI                            |    🔴   |                                         |
| EEPROM                         |    🔴   |                                         |
| Configuração de Clock          |    🔴   |                                         |
| Sleep                          |    🔴   |                                         |
| Fuse bits                      |    🔴   |                                         |

Legenda:  
- 🟢 Feito
- 🟡 Em progresso
- 🔴 Ainda não implementado
