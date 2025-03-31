# Notas

## Portas

### DDRx: (Direção do portal; IN/OUT)

Modelo:
`DDRD = 0b--------;`
*: no portal D, as portas '1' serão de saida.

Ex:
`DDRD = 0b10000010;`
as portas (bits do portal) 7 e 1 serão de saida.


### PORTx: (ON/OFF)
Ligar ou desligar o pino de saida.

Ex: 
`PORTD = 0b00000010;`
o pino 1 foi ligado.


### PINx
Ler um valor de uma porta

Ex:
`int leitura = PIND & 0b00001000;`
Ler o valor do portal D no pino 3.

## Resistor Pullup e Pulldown
#TODO: resumir conteudo


