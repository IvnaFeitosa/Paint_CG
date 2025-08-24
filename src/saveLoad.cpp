#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "saveLoad.hpp"
#include "line.hpp"
#include "polygon.hpp"

#define NOME_ARQUIVO "savefile.txt"
#define PASTA ""

void salvarObjetos2D(ObjContainer &obj_container) {

    std::string nomeArquivo = NOME_ARQUIVO;

    //adicionando extensão .txt ao arquivo em caso de não informado pelo user
    if (nomeArquivo.find(".txt") == std::string::npos){
        nomeArquivo += ".txt";
    }

    //definindo local de salvamento do arquivo
    std::string caminho = PASTA + nomeArquivo;
    
    //criando arquivo
    std::ofstream arquivoSave(caminho);

    if (!arquivoSave.is_open()) {
        std::cerr << "Erro: não foi possível criar o arquivo " << caminho << "\n";
    }

    //iterando por todos os objetos POINT criados durante a execução atual do programa
    float r, g, b;
    for (auto &p : obj_container.get_points()) {
        p.get_color(r, g, b);
        arquivoSave << "PONTO:" << r << "," << g << "," << b << ";" << p.getX() << "," << p.getY() << "\n";
    }

    //iterando por todos os objetos LINE criados durante a execução atual do programa
    for(auto &linha: obj_container.get_lines()){
        linha.get_color(r, g, b);
        arquivoSave << "LINHA:" 
                    << r << "," << g << "," << b << ";"
                    << linha.getp1().getX() << "," << linha.getp1().getY() << ";"
                    << linha.getp2().getX() << "," << linha.getp2().getY() << "\n";
    }

    //itreando por todos os objetos POLYGON criados durante a atual execução do programa
    for (auto &poly : obj_container.get_polygons()){
        poly.get_color(r, g, b);
        arquivoSave << "POLIGONO:";
        arquivoSave << r << "," << g << "," << b;
        for(auto &vertice : poly.get_verticies()){
            arquivoSave << ";" << vertice.getX() << "," << vertice.getY();
        }
        arquivoSave << "\n";
    }

    arquivoSave.close();
    std::cout << nomeArquivo << " salvo com sucesso!\n";
}

void carregarObjetos2D(ObjContainer &obj_container) {

    //escolha do usuário do arquivo de carregamento
    std::string arquivoEscolhido = NOME_ARQUIVO;
    std::string pastaDestino = PASTA;

    std::string arquivoSelecionado;

    //adicionando extensão .txt ao arquivo em caso de não informado pelo user
    if (arquivoSelecionado.find(".txt") == std::string::npos){
        arquivoSelecionado += ".txt";
    }

    arquivoEscolhido = pastaDestino + arquivoEscolhido;

    //abrindo arquivo escolhido pelo usuário
    std::ifstream arquivo(arquivoEscolhido);

    if (!arquivo.is_open()) {
        std::cerr << "Arquivo inexistente ou inválido" << arquivoEscolhido << "\n";
        return;
    }
    
    std::string linha;
    while (std::getline(arquivo, linha)) {
        
        std::stringstream conteudo(linha);
        std::string tipo;

        //pegando primeira metade da linha antes do : (linha, ponto, poligono)
        std::getline(conteudo, tipo, ':');

        if(tipo == "PONTO"){

            std::string dados;
            std::getline(conteudo, dados);

            float x, y, r, g, b;
            sscanf(dados.c_str(), "%f,%f,%f;%f,%f", &r, &g, &b, &x, &y);

            Point p(x, y);
            p.set_color(r, g, b);
            obj_container.addPoint(p);
        }else if(tipo == "LINHA"){

            std::string p1, p2, cor;
            std::getline(conteudo, cor, ';');
            std::getline(conteudo, p1, ';');
            std::getline(conteudo, p2);

            float p1x, p1y, p2x, p2y, r, g, b;
            sscanf(p1.c_str(), "%f,%f", &p1x, &p1y);
            sscanf(p2.c_str(), "%f,%f", &p2x, &p2y);
            sscanf(cor.c_str(), "%f,%f,%f", &r, &g, &b);

            Line l(Point(p1x, p1y), Point(p2x, p2y));
            l.set_color(r, g, b);
            obj_container.addLine(l);

        }else if(tipo == "POLIGONO"){
            
            std::string dados;
            std::getline(conteudo, dados);

            std::stringstream ss(dados);
            std::string parte;

            std::getline(ss, parte, ';');
            float r, g, b;
            sscanf(parte.c_str(), "%f,%f,%f", &r, &g, &b);

            std::list<Point> verts;
            while (std::getline(ss, parte, ';')) {
                float x, y;
                if (sscanf(parte.c_str(), "%f,%f", &x, &y) == 2) {
                    verts.push_back(Point(x, y));
                }
            }

            Poly poly(verts);
            poly.set_color(r, g, b);
            obj_container.addPoly(poly);

        }
    }

    std::cout << "carregamento de: " << arquivoEscolhido << " concluido com sucesso\n";

}