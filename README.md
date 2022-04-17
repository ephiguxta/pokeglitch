### pokeglitch

Fazendo algumas modificações do *save* do Pokémon Red.
No momento a ferramenta pode modificar o nome do *player*.
Para fazer essa modificação, você precisa seguir os passos abaixo:

```bash
$ cd src/
$ gcc -Wall *.c -o main
```

Agora você precisa passar o caminho do *save* para a aplicação:

```bash
$ # if u r using mgba, the cmd below will works
$ main ../rom/pokemon_red.sav
```

Se você não mudou a linha 25 do arquivo `main.c`, o novo do *player* será:
`testing`.

### TODO

- [ ] usar o getopts (unistd.h) para "parsear" os parâmetros no CLI.

- [ ] mudar o dinheiro do *player*.

- [ ] ...
