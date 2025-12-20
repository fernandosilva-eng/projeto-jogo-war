# War Estruturado em C

Este é um simulador simplificado do clássico jogo de tabuleiro **War**, desenvolvido em linguagem C. O projeto utiliza conceitos de estruturas de dados (structs), alocação dinâmica de memória e lógica de jogos baseada em turnos.

## 🚀 Funcionalidades

- **Cadastro de Territórios:** Permite definir o nome, a cor do exército e a quantidade inicial de tropas para cada território.
- **Sistema de Missões:** Sorteia automaticamente uma missão para o jogador (ex: conquistar territórios, vencer batalhas seguidas).
- **Simulação de Batalhas:** Sistema de ataque e defesa baseado em dados aleatórios, com regras de perda e conquista de territórios.
- **Gestão de Memória:** Implementação de alocação dinâmica para gerenciar os dados do mapa e limpeza de buffer para entradas de usuário.

## 🛠️ Tecnologias Utilizadas

- Linguagem **C**
- Bibliotecas Padrão: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- Biblioteca de Sistema: `windows.h` (para funções de delay/Sleep)

## 📋 Como Executar

1. Certifique-se de ter um compilador C instalado (como GCC/MinGW).
2. Clone o repositório ou baixe o arquivo `.c`.
3. Abra o terminal na pasta do arquivo e compile:
   ```bash
   gcc war_game.c -o war_game.exe
