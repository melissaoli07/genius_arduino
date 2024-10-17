# Jogo Genius com Arduino

 Melissa de Oliveira Pecoraro RM:98698  
 Roberto Menezes dos Santos RM:552520      

Projeto do 4º semestre da faculdade FIAP.  

Este projeto implementa o clássico jogo Genius utilizando a plataforma Arduino.

O objetivo do jogo é testar a memória do jogador, que deve repetir uma sequência de cores e sons que aumentam em dificuldade a cada rodada.

## Funcionalidades
- Sequência de LEDs coloridos e sons correspondentes
- Níveis de dificuldade que aumentam a cada rodada
- Jogabilidade simples e interativa

## Componentes Utilizados
- Arduino Uno
- LEDs coloridos (Vermelho, Verde, Azul, Amarelo)
- Botões para interação
- Buzzer para gerar sons
- Resistores e fios

# Regras de funcionamento do jogo:

Um jogador inicia o jogo no modo fácil (easy) e no nível_1

O jogo sempre inicia no modo `idle()`

## Idle

O jogo estará esperando alguma entrada do jogador

Os LEDs ficaram piscando em padrões

Quando o jogador apertar algum botão, o modo será alterado para "running" e os padrões irão parar

## Running

O jogo irá gerar aleatoriamente as cores

Exibirá as cores para o jogador através dos LEDs

O jogador terá que pressionar o botão de acordo com a sequencia mostrada, ele terá 200ms para entrar cada tecla, ou input no terminal

Caso ele entre com a sequencia errada o jogo irá para o game over

Caso ele entre com a sequencia certa o jogo reiniciará e será gerada outra sequencia

### Atualização de níveis

Os níveis irão aumentar de um em um

### Incrementar a dificuldade

A dificuldade começará no easy e irá até o very hard ao decorrer do tempo jogado

A dificuldade irá aumentar a cada 5 níveis

A dificuldade também irá aumentar o tamanho da sequencia das cores, a cada 3 níveis o tamanho irá aumentar sempre em 1

#### Tabela aumento junto com níveis

| Dificuldade | Aumento no tamanho | Níveis para aumento de tamanho |
| ----------- | ------------------ | ------------------------------ |
| EASY        | 1                  | 3                              |
| MEDIUM      | 2                  | 4                              |
| HARD        | 3                  | 5                              |
| VERY HARD   | 3                  | 5                              |

## Game Over

Quando o jogo acabar o recorde do jogador será guardado

O será tocada uma musica de erro

Trocará o estado para **Restarting**

## Restarting

Deixará o jogo em um esta de inicio, reiniciando as variáveis e o recorde (agora salvo)

Colocará o estado em Idle

