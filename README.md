### pokeglitch

Making some modifications in a Pokémon Red savegame.
At the moment this tool can modify the player name.
To make this change, you need to follow the steps below:

```bash
$ cd src/
$ gcc -Wall *.c -o main
```

Now you need to pass your save path to the app:

```bash
$ # if u r using mgba, the cmd below will works
$ main ../rom/pokemon_red.sav
```

If you don't change the line 25 in the main.c, the new player name will be:
`testing`.

### TODO

- [ ] use getopts (unistd.h) to parse command-line params.

- [x] change player money.

- [ ] limit name to valid chars.

- [ ] ...
