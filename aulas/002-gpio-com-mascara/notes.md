# notas

## problema de utilizar apenas atribuição ao registrador

O codigo abaixo altera o valor desejado, mas modifica os valores referente à outros pinos.

```java
PORT = 0b00001000;
```

Para resolver isso, utilizamos máscaras em conjunto com operadores lógicos (OR `|`, AND `&`).

### Acionando uma porta

O acionamento deve ser feito da seguinte forma:

```c
PORTC = PORTC | 0b00010000;
```

### Desligar uma porta

O desligamento deve ser feito através do operador AND, com o inverso da máscara

```c
PORTC = PORTC & ~(0b00010000);
```

