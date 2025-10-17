# trabalho-MD2

- feito por:
  - Gabriel Mota Oliveira - 241011081
  - Matheus Pinheiro - 241025336

# Respostas da questão 4:

- saida:

```
insira H: 7
insira G: 3
insira Zn: 11
insira x: 10
insira n1: 13

Algoritmo de euclides: 3 mod 11 = 3
Algoritmo de euclides: 11 mod 3 = 2
Algoritmo de euclides: 3 mod 2 = 1
Algoritmo de euclides: 2 mod 1 = 0

Substituindo, temos que o inverso de 3 em 11 e 4.

Fazendo a multiplica├º├úo modular: 7 * 4 mod = 11
Sendo 4 o inverso de 3.
Valor final da congruencia: 4

```

- (v) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
- (f) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
- (v) A operação (H \* inverso) % Zn representa a divisão modular de H por G.
- (v) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
- (f) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
- (v) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
- (v) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.
