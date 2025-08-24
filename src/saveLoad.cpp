#include "saveLoad.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#include "line.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "object.hpp"
#include "obj_container.hpp"

extern ObjContainer obj_container; 

void salvarObjetos2D(){

    std::string nomeArquivo;
    std::cout << "digite o nome do arquivo: ";
    std::cin >> nomeArquivo;

    //adicionando extensão .txt ao arquivo em caso de não informado pelo user
    if (nomeArquivo.find(".txt") == std::string::npos){
        nomeArquivo += ".txt";
    }

    //definindo local de salvamento do arquivo
    std::string pastaDestino = "saves/";
    std::string caminho = pastaDestino + nomeArquivo;
    
    //criando arquivo
    std::ofstream arquivoSave(caminho);

    if(!arquivoSave.is_open()){
        std::cerr << "Erro: não foi possível criar o arquivo " << caminho << "\n";
    }

    //iterando por todos os objetos POINT criados durante a execução atual do programa
    for (auto &p : obj_container.get_points()) {
        arquivoSave << "PONTO:" << p.getX() << "," << p.getY() << "\n";
    }

    //iterando por todos os objetos LINE criados durante a execução atual do programa
    for(auto &linha: obj_container.get_lines()){
        arquivoSave << "LINHA:" << linha.getp1().getX() << "," << linha.getp1().getY() << ";" << linha.getp2().getX() << "," << linha.getp2().getY() << "\n";
    }

    //itreando por todos os objetos POLYGON criados durante a atual execução do programa
    for (auto &poly : obj_container.get_polygons()){

        arquivoSave << "POLIGONO:";

        for(auto &vertice : poly.get_verticies()){
            arquivoSave << vertice.getX() << "," << vertice.getY() << ";";
        }

        arquivoSave << "\n";
    }

    arquivoSave.close();
    std::cout << nomeArquivo << " salvo com sucesso!\n";
}

void carregarObjetos2D(){

    //escolha do usuário do arquivo de carregamento
    std::string arquivoEscolhido = "";
    std::string pastaDestino = "saves/";
    std::vector <std::string> arquivosDisponiveis;


    if(arquivosDisponiveis.empty()){
        std::cout << "nenhum arquivo de carregamento disponível\n";
    }else{
        
        //exibindo todos os arquivos de carregamento disponíveos
        std::cout << "lista de arquivos disponiveis: \n";
        for(int i=0; i<arquivosDisponiveis.size(); i++){
            std::cout << i+1 << "." << arquivosDisponiveis[i] << "\n"; 
        }

        int escolha = 0;
        std::cout << "escolha o numero referente ao arquivo que deseja carregar: ";
        std::cin >> escolha;

        if(escolha > arquivosDisponiveis.size() || escolha == 0){
            std::cout << "escolha invalida\n";
        }else{
            arquivoEscolhido = pastaDestino + arquivosDisponiveis[escolha - 1];
        }

        //iniciando carregamento das coordenadas do arquivo
        if(arquivoEscolhido==""){
            std::cout << "carregamento interrompido \n";
        }else{

            //abrindo arquivo escolhido pelo usuário
            std::ifstream arquivo(arquivoEscolhido);
            
            std::string linha;
            while (std::getline(arquivo, linha)) {
                
                std::stringstream conteudo(linha);
                std::string tipo;

                //pegando primeira metade da linha antes do : (linha, ponto, poligono)
                std::getline(conteudo, tipo, ':');

                if(tipo == "PONTO"){

                    //pegando a segunda metade da linha após o :
                    std::string coordenadas;
                    std::getline(conteudo, coordenadas);

                    float coordenadaX;
                    float coordenadaY;

                    //obtendo valores
                    sscanf(coordenadas.c_str(), "%f,%f", &coordenadaX, &coordenadaY);

                    //remontando e armazenando objeto PONTO com base nas coordenadas obtidas
                    obj_container.addPoint(Point(coordenadaX, coordenadaY));

                }else if(tipo == "LINHA"){

                    std::string p1;
                    std::string p2;

                    //pegando segunda metade da linha após : que contém coord do ponto 1
                    std::getline(conteudo, p1, ';');

                    //pegando terceira metade da linha após ; que contém coord do ponto 2
                    std::getline(conteudo, p2, ';');

                    float p1x;
                    float p1y;
                    float p2x;
                    float p2y;

                    //obtendo valores
                    sscanf(p1.c_str(), "%f,%f", &p1x, &p1y);
                    sscanf(p2.c_str(), "%f,%f", &p2x, &p2y);

                    //remontando e armazenando objeto LINHA com base nas coordenadas obtidas
                    Point ponto1(p1x, p1y);
                    Point ponto2(p2x, p2y);
                    Line linhaObtida(ponto1, ponto2);
                    obj_container.addLine(linhaObtida);

                }else if(tipo == "POLIGONO"){
                    
                    //string que conterá trecho da linhas entre separadores
                    std::string vertices;

                    //vetor de tipo Point para armazenada coordenada tratada
                    std::list<Point> verticesLoad;

                    //enquanto houver conjunto de coordenadas separadas por ;
                    while(std::getline(conteudo, vertices, ';')){

                        float coordenadax;
                        float coordenaday;

                        sscanf(vertices.c_str(), "%f,%f", &coordenadax, &coordenaday);
                        verticesLoad.push_back(Point(coordenadax, coordenaday));

                    }

                    //remontando objeto Polygon após obter todos os seus pontos
                    obj_container.addPoly(Poly(verticesLoad));

                }
            }

            std::cout << "carregamento de: " << arquivoEscolhido << " concluido com sucesso\n";
        }
    }
}