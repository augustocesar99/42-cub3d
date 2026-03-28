# cub3D - Motor de Raycasting 3D

Um motor de raycasting 3D desenvolvido em C, inspirado no clássico jogo Wolfenstein 3D. Este projeto implementa um motor gráfico capaz de renderizar ambientes 3D em tempo real usando técnicas de raycasting.

## 📋 Sobre o Projeto

**cub3D** é um projeto educacional que explora conceitos fundamentais de computação gráfica, incluindo:

- **Raycasting**: Técnica de renderização que lança raios da câmera para determinar o que é visível
- **Renderização de Texturas**: Mapeamento de texturas 2D em paredes 3D
- **Mapa 2D**: Navegação em ambientes baseados em grelhas
- **Física Básica**: Sistema de movimento e colisão com paredes
- **Interface Gráfica**: Minimap em tempo real

## 🎮 Funcionalidades

- ✅ Renderização 3D com texturas em 4 direções (Norte, Sul, Leste, Oeste)
- ✅ Sistema de cores customizável (piso e teto)
- ✅ Controles fluidos de movimento e câmera
- ✅ Minimap interativo
- ✅ Parser robusto de arquivos de configuração (.cub)
- ✅ Sistema de detecção de erros com mensagens claras
- ✅ Gerenciamento automático de memória

## 🚀 Como Compilar

### Pré-requisitos

- GCC ou Clang
- Make
- X11/XLib (para Linux)

### Compilação

```bash
# Clonar o repositório
git clone <repo-url>
cd 42-cub3d

# Compilar o projeto
make

# Para recompilar do zero
make re

# Para limpar arquivos objeto
make clean

# Para remover todos os arquivos compilados
make fclean
```

## 🎯 Como Usar

### Executar o Programa

```bash
./cub3D <caminho/para/arquivo.cub>
```

**Exemplo:**
```bash
./cub3D maps/valid/first.cub
```

### Controles do Jogo

| Tecla | Ação |
|-------|------|
| **W** | Mover para frente |
| **A** | Mover para esquerda (strafe) |
| **S** | Mover para trás |
| **D** | Mover para direita (strafe) |
| **← / →** | Girar câmera |
| **ESC** | Sair do jogo |

## 📝 Formato do Arquivo de Configuração (.cub)

Os arquivos `.cub` definem o ambiente do jogo. O formato é:

```
NO ./caminho/para/textura_norte.xpm
SO ./caminho/para/textura_sul.xpm
WE ./caminho/para/textura_oeste.xpm
EA ./caminho/para/textura_leste.xpm

F 220,100,0
C 225,30,0

111111111111111111111111111111111
100100000000000000000000000000001
101010010010100100001000010000101
1111111111111111111111111111111111
```

### Componentes Obrigatórios

1. **Texturas** (4 linhas):
   - `NO`: Textura parede Norte
   - `SO`: Textura parede Sul
   - `WE`: Textura parede Oeste
   - `EA`: Textura parede Leste

2. **Cores**:
   - `F`: Cor do chão (RGB 0-255)
   - `C`: Cor do teto (RGB 0-255)

3. **Mapa**:
   - `1`: Parede
   - `0`: Espaço vazio
   - `N/S/E/W`: Posição inicial do jogador (direção)

## 🔧 Principais Módulos

### Parser (`parser/`)
Lê e valida arquivos `.cub`, extraindo:
- Caminhos de texturas
- Configuração de cores
- Disposição do mapa

### Raycasting & Renderização (`render.c`, `dda.c`)
- Implementa o algoritmo DDA para detecção de colisão de raios
- Renderiza cada coluna vertical da tela

### Sistema de Movimento (`move.c`)
- Controla movimento da câmera e detecção de colisão
- Implementa controles suaves

### Minimap (`minimap.c`)
- Renderiza visão 2D do mapa em tempo real
- Mostra posição e direção do jogador

## 🐛 Validação de Mapas

O programa valida automaticamente:
- ✅ Formato correto do arquivo
- ✅ Presença de todas as texturas
- ✅ Cores válidas (RGB 0-255)
- ✅ Mapa bem formado sem buracos
- ✅ Apenas uma posição inicial de jogador
- ✅ Posição inicial dentro do mapa válido

**Aproveite a experiência de um motor 3D clássicos! 🎮**
