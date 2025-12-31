# RAISS
Trabalho de Conclusao de Curso SENAI - Redes de Computaroes Vespertino 2016.  
![RoboticArm](https://github.com/riwersxd/RAISS/blob/master/app/img/braco.png)

> Você pode obter mais detalhes sobre o projeto lendo o arquivo [Projeto RAISS (TCC 4RV 2016).pdf](https://github.com/riwersxd/RAISS/blob/master/Projeto%20RAISS%20(TCC%204RV%202016).pdf)

## Requisitos para recriação:
- Arduino Mega 2560
- Protoboard 830 Pinos
- Módulo Wi-Fi ESP8266
- Braço Robódtico de Acrílico MeArm
- Máquina com Servidor Linux

## Entendendo a Estrutura
### **Arquivos:**
- Os arquivos `/modulo.ino` e `/servidor.c` são os programas para o arduíno.
- Os arquivos em `/php/comandos/` são arquivos de controle do braço.
- Os arquivos em `/php/inclusoes/` são arquivos de controle do sistema.
- Os arquivos em `/img/` e `/css/` são respectivamente as imagens e estilos das páginas
- Os arquivos em `/php/` são as páginas do sistema.
- O arquivo `/index.html` é a página de login do sistema.
- O arquivo `/script.sql` é o script para gerar o banco com um usuário administrados

### **Campos do Banco:**
- _id_: Número de identificação único do usuário.
- _login_: Nome utilizado para o acesso do usuário (Deve ser único).
- _senha_: Senha utilizada para o acesso do usuário (Criptografado com SHA-2).
- _nivel_: Nível de acesso do usuário (`1` para usuário _comum_, `2` para usuário _administrador_ (Padrão é "1")).
- _ativo_: Booleano para contas ativas ou inativas ("0" para _inativo_, "1" para _ativo_ (Padrão é "1")).
- _tentativas_: Número de tentativas sem sucesso de acesso usuário (Máximo de 5 tentativas).
- _cadastro_: Data de cadastro do usuário.

## Conectando o Arduíno, o Módulo e o Braço
Faça as seguintes conexões:  
![Esquema Conexões](https://github.com/riwersxd/RAISS/blob/master/app/esquema.png)

_Veja a Página Página 85 (Figura 44) do [Projeto RAISS (TCC 4RV 2016).pdf](https://github.com/riwersxd/RAISS/blob/master/Projeto%20RAISS%20(TCC%204RV%202016).pdf)_

## Configurando o Ambiente e Execução do Projeto
Build Docker
```
docker build ./app -t raiss --platform=linux/amd64
```
Run Rocker
```
docker run --platform=linux/amd64 -p 8080:80 --name raiss raiss
```

Instale o Servidor LAMP e execute-o:
```
apt-get install apache2 php7.0 libapache2-mod-php7.0 mysql-server php7.0-mysql
```
Execute o Scriptpara gerar o Banco de Dados:
```
/script.sql
```
_Veja as Páginas 86 a 101 (Figuras 45 a 76) do [Projeto RAISS (TCC 4RV 2016).pdf](https://github.com/riwersxd/RAISS/blob/master/Projeto%20RAISS%20(TCC%204RV%202016).pdf)_

---
**Este projeto foi desenvolvido por:** André Lucas Maegima, Breno Henrique Borges Santos, Bruno dos Santos Mauricio, Guilherme Rios da Cunha(Eu) e Leonardo Ribeiro dos Santos

