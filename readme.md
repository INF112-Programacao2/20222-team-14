# Jogo de Xadrez

Projeto final da disciplina de Programação II (INF112) do semestre letivo 2022/2 da Universidade Federal de Viçosa (UFV) no Curso Bacharelado em Ciência da Computação.

## Desenvolvimento

<table>
  <tr>
    <td align="center">
        <a href="https://github.com/xPedrol" target="_blank">
            <img src="https://avatars.githubusercontent.com/u/46272186?s=96&v=4" width="80px" ><br>
            Pedro L.
        </a>
    </td>
 <td align="center">
        <a href="https://github.com/RafaSS" target="_blank">
            <img src="https://avatars.githubusercontent.com/u/77814194?v=4" width="80px" ><br>
            Rafael S.
        </a>
    </td>
   </td>
  </tr>

</table>

## Documentação

### Configuração
- [Instalação Cmake](https://cmake.org/install/)


### Regras de negócio
- [tabuleirodexadrez.com.br](https://www.tabuleirodexadrez.com.br/regras-do-xadrez.html)
- [en.wikipedia.org/wiki/Rules_of_chess](https://en.wikipedia.org/wiki/Rules_of_chess)
- [chess.com/learn-how-to-play-chess](https://www.chess.com/learn-how-to-play-chess)



### Gerando build

```bash
cmake -S . -B Build -G "MinGW Makefiles"
```

### Executando a build
  Para executar a build gerada no passo anterior, basta executar o comando abaixo dentro do dirétorio "build" gerado na raiz do projeto.

     cmake --build .

