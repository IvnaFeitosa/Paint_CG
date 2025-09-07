# 🎨 Paint OpenGL  

Esse sistema consiste em um **Editor Gráfico em C++ com OpenGL/GLUT**, baseado em algoritmos de seleção.  

---

## 🚀 Funcionalidades  

### 🔹 Objetos Primitivos  
- **Pontos** → criados com clique simples  
- **Linhas** → definidas por dois pontos  
- **Polígonos** → lista circular de vértices com fechamento automático  

### 🔹 Sistema de Seleção Inteligente  
- **Pontos**: distância euclidiana com tolerância ajustável  
- **Linhas**: distância mínima ponto-segmento  
- **Polígonos**: algoritmo **Ray Casting** (suporta formas côncavas e complexas)  

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

