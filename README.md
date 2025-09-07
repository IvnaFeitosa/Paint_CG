# 🎨 Paint OpenGL  

Esse sistema consiste em um **Editor Gráfico em C++ com OpenGL/GLUT**, baseado em algoritmos de seleção.  

---

## 🚀 Funcionalidades  

### 🔹 Objetos Primitivos  
- **Pontos** → criados com clique simples  
- **Linhas** → definidas por dois pontos  
- **Polígonos** → lista circular de vértices com fechamento automático  

### 🔹 Transformação de poligono côncado em convexo
- Utilização do algorítmo de **Divisão e conquista** para transformar qualquer poligono côncavo desenhado em convexo, após selecionado e acinodo o comando (Tecla c).

### 🔹 Transformações Geométricas (Matrizes 3x3)  
- **Translação** → movimento em X/Y  
- **Rotação** → em torno do centro (linhas/polígonos) ou origem (pontos)  
- **Escala** → redimensionamento proporcional  
- **Reflexão** → espelhamento em eixos X/Y  
- **Cisalhamento** → deformação controlada  

Todas as transformações utilizam **matrizes homogêneas 3x3** com composição matemática.  

---

## ⚙️ Como Executar  


### 🔹 Dependências  

Certifique-se de ter instalado:  
- `g++` (compilador C++)  
- `OpenGL` (`libgl1-mesa-dev`)  
- `GLUT` (`freeglut3-dev`)  

No Ubuntu/Debian:  
```bash
sudo apt update
sudo apt install g++ freeglut3-dev libglew-dev libglm-dev
```

### 📥 Clone o Projeto  

Clone o projeto com o seguinte comando em seu terminal:  
```bash
git clone https://github.com/IvnaFeitosa/Paint_CG.git
```

Após abrir o projeto certifique-se de estar dentro da pasta:
```bash
cd Paint_CG
```

Crie um executável do paint no diretório `/bin`:
No Linux:
```bash
g++ -std=c++17 src/*.cpp -Iinclude -o bin/paint -lGL -lGLU -lglut
```
No Windows:
```bash
g++ -std=c++17 src/*.cpp -Iinclude -o bin/paint -lfreeglut -lopengl32 -lglu32
```
▶️ Para executar o projeto:
```bash
./bin/paint
```
## 💾 Persistência de Dados

- Salvar/Carregar objetos em formato texto
- Validação robusta de arquivos
- Tratamento de erros e corrupção
- Limpeza automática ao carregar

## 🎬 Animação

- Animação baseada no **Pac-Man**
- Objeto Pac-Man desloca-se horizontalmente de uma extremidade a outra
- Coleta todas as pastilhas **(pontos amarelos)**

## 🎮 Controles  

### 🔹 Criação de Objetos  
| Tecla   | Função         |
|---------|----------------|
| `1`     | Modo Ponto     |
| `2`     | Modo Linha     |
| `3`     | Modo Polígono  |
| `Enter` | Fechar Polígono |

---

### 🔹 Seleção e Transformação  
| Tecla / Ação              | Função                  |
|----------------------------|-------------------------|
| Clique Esq. (mouse)        | Modo Seleção            |
| `r`                        | Rotação +1°           |
| `t`                        | Rotação -1°           |
| `f`                        | Escala (1.1x)          |
| `g`                        | Escala (0.9x)          |
| `z`                        | Reflexão (eixo X)      |
| `x`                        | Reflexão (eixo Y)      |
| `y`                        | Cisalhamento (X, 0.5)  |
| `u`                        | Cisalhamento (X, -0.5) |
| `h`                        | Cisalhamento (Y, 0.5)  |
| `j`                        | Cisalhamento (Y, -0.5) |
| `c`                        | Convex hull - Poligono covexo|
| Clique + Arraste (mouse)   | Transladar objeto      |

---

### 🔹 Arquivo  
| Tecla | Função            |
|-------|-------------------|
| `s`   | Salvar objetos    |
| `l`   | Carregar objetos  |
| `a`   | Iniciar animação  |


## 📜 Licença
Este projeto foi desenvolvido para fins educacionais na disciplina de Computação Gráfica.  
